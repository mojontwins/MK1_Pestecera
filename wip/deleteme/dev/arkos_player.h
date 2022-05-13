// ARKOS 1 player embedded by na_th_an
// This needs a buffer to decompress songs.
// Biggest song file must fit, so adjust if needed.
// There's also a buffer to descompress SFX, but this si managed automaticly

0xdefine ARKOS_SFX_BUFFER 	0x8600
0xdefine ARKOS_SONG_BUFFER 	0x8800

// This is `ArkosTrackerPlayer_CPC_MSX.asm` with the macros auto-expanded
// and code reformatted & resyntaxed for z88dk. There's also a small C wrapper

void arkos_init (void) {
	0xasm
		;
		xor a
		ld  (_isr_player_on), a
	0xendasm	
}

void __FASTCALL__ arkos_play_music (unsigned char m) {
	0xasm
		; Song number is in L

		ld  a, 1
		ld  (_isr_player_on), a
	0xendasm
}

void __FASTCALL__ arkos_play_sound (unsigned char s) {
	0xasm
		; Sound number is in L
	0xendasm
}

void arkos_stop_sound (void) {
	0xasm
		; 
		xor a
		ld  (_isr_player_on), a
	0xendasm
}

0xasm
	// Arkos Tracker Player V1.01 - CPC & MSX version.
	// 21/09/09

	// Code By Targhan/Arkos.
	// PSG registers sendings based on Madram/Overlander's optimisation trick.
	// Restoring interruption status snippet by Grim/Arkos.

	.arkos_player

	.PLY_Digidrum 
		defb 0

	.PLY_Play		
		xor a				
		// Reset the Digidrum flag.	
		ld (PLY_Digidrum),a		

	// Manage Speed. If Speed counter is over, we have to read the Pattern further.
	.PLY_SpeedCpt 
		ld a,1
		dec a
		jp nz,PLY_SpeedEnd

	// Moving forward in the Pattern. Test if it is not over.
	.PLY_HeightCpt 
		ld a,1
		dec a
		jr nz,PLY_HeightEnd

	// Pattern Over. We have to read the Linker.

	// Get the Transpositions, if they have changed, or detect the Song Ending !
	.PLY_Linker_PT 
		ld hl,0
		ld a,(hl)
		inc hl
		rra
		jr nc,PLY_SongNotOver
	
	// Song over ! We read the address of the Loop point.
		ld a,(hl)
		inc hl
		ld h,(hl)
		ld l,a

	// We know the Song won't restart now, so we can skip the first bit.
		ld a,(hl)			
		inc hl
		rra

	.PLY_SongNotOver
		rra
		jr nc,PLY_NoNewTransposition1
		ld de,PLY_Transposition1 + 1
		ldi
	.PLY_NoNewTransposition1
		rra
		jr nc,PLY_NoNewTransposition2
		ld de,PLY_Transposition2 + 1
		ldi
	.PLY_NoNewTransposition2
		rra
		jr nc,PLY_NoNewTransposition3
		ld de,PLY_Transposition3 + 1
		ldi
	.PLY_NoNewTransposition3

	// Get the Tracks addresses.
		ld de,PLY_Track1_PT + 1
		ldi
		ldi
		ld de,PLY_Track2_PT + 1
		ldi
		ldi
		ld de,PLY_Track3_PT + 1
		ldi
		ldi

	// Get the Special Track address, if it has changed.
		rra
		jr nc,PLY_NoNewHeight
		ld de,PLY_Height + 1
		ldi
	.PLY_NoNewHeight

		rra
		jr nc,PLY_NoNewSpecialTrack
	.PLY_NewSpecialTrack
		ld e,(hl)
		inc hl
		ld d,(hl)
		inc hl
		ld (PLY_SaveSpecialTrack + 1),de

	.PLY_NoNewSpecialTrack
		ld (PLY_Linker_PT + 1),hl
	.PLY_SaveSpecialTrack 
		ld hl,0
		ld (PLY_SpecialTrack_PT + 1),hl

	// Reset the SpecialTrack/Tracks line counter.
	// We can't rely on the song data, because the Pattern Height is not related to the Tracks Height.
		ld a,1
		ld (PLY_SpecialTrack_WaitCounter + 1),a
		ld (PLY_Track1_WaitCounter + 1),a
		ld (PLY_Track2_WaitCounter + 1),a
		ld (PLY_Track3_WaitCounter + 1),a	

	.PLY_Height 
		ld a,1
	.PLY_HeightEnd
		ld (PLY_HeightCpt + 1),a

	// Read the Special Track/Tracks.
	// ------------------------------

	// Read the Special Track.
	.PLY_SpecialTrack_WaitCounter 
		ld a,1
		dec a
		jr nz,PLY_SpecialTrack_Wait

	.PLY_SpecialTrack_PT 
		ld hl,0
		ld a,(hl)
		inc hl
		// Data (1) or Wait (0) ?
		srl a				
		// If Wait, A contains the Wait value.
		jr nc,PLY_SpecialTrack_NewWait	
		// Data. Effect Type ?
		// Speed (0) or Digidrum (1) ?
		srl a				
		// First, we don't test the Effect Type, but only the Escape Code (=0)
		jr nz,PLY_SpecialTrack_NoEscapeCode
		ld a,(hl)
		inc hl
		
	//Now, we test the Effect type, since the Carry didn't change.
	.PLY_SpecialTrack_NoEscapeCode
		jr nc,PLY_SpecialTrack_Speed
		ld (PLY_Digidrum),a
		jr PLY_PT_SpecialTrack_EndData

	.PLY_SpecialTrack_Speed
		ld (PLY_Speed + 1),a
	.PLY_PT_SpecialTrack_EndData
		ld a,1
	.PLY_SpecialTrack_NewWait
		ld (PLY_SpecialTrack_PT + 1),hl
	.PLY_SpecialTrack_Wait
		ld (PLY_SpecialTrack_WaitCounter + 1),a

	// Read the Track 1.
	// -----------------

	.PLY_Track1_WaitCounter 
		//  Store the parameters, because the player below is called every frame, but the Read Track isn't.
		ld a,1
		dec a
		jr nz,PLY_Track1_NewInstrument_SetWait

	.PLY_Track1_PT 
		ld hl,0
		call PLY_ReadTrack
		ld (PLY_Track1_PT + 1),hl
		jr c,PLY_Track1_NewInstrument_SetWait


		// No Wait command. Can be a Note and/or Effects.
		// Make a copy of the flags+Volume in A, not to temper with the original.
		ld a,d			

		// Volume ? If bit 4 was 1, then volume exists on b3-b0
		rra			
		jr nc,PLY_Track1_SameVolume
		and 0xf // %1111

		// na_th_an :: this had to be modified
		// ld (PLY_Track1_Volume),a		
		ld (_PLY_Track1_Volume_Note + 2), a
		// 

	.PLY_Track1_SameVolume

		// New Pitch ?
		rl d				
		jr nc,PLY_Track1_NoNewPitch
		ld (PLY_Track1_PitchAdd + 1),ix
	.PLY_Track1_NoNewPitch

		// Note ? If no Note, we don't have to test if a new Instrument is here.
		rl d				
		jr nc,PLY_Track1_NoNoteGiven
		ld a,e
	.PLY_Transposition1 
		// Transpose Note according to the Transposition in the Linker.
		add a,0		

		// na_th_an :: this had to be modified		
		// ld (PLY_Track1_Note),a
		ld (_PLY_Track1_Volume_Note + 1), a
		// 

		// Reset the TrackPitch.
		ld hl,0				
		ld (PLY_Track1_Pitch + 1),hl

		// New Instrument ?
		rl d				
		jr c,PLY_Track1_NewInstrument

	.PLY_Track1_SavePTInstrument 
		// Same Instrument. We recover its address to restart it.
		ld hl,0	
		// Reset the Instrument Speed Counter. Never seemed useful...
		ld a,(PLY_Track1_InstrumentSpeed + 1)		
		ld (PLY_Track1_InstrumentSpeedCpt + 1),a
		jr PLY_Track1_InstrumentResetPT

		// New Instrument. We have to get its new address, and Speed.
	.PLY_Track1_NewInstrument		
		// H is already set to 0 before.
		ld l,b				
		add hl,hl
	.PLY_Track1_InstrumentsTablePT 
		ld bc,0
		add hl,bc
		// Get Instrument address.
		ld a,(hl)			
		inc hl
		ld h,(hl)
		ld l,a
		// Get Instrument speed.
		ld a,(hl)			
		inc hl
		ld (PLY_Track1_InstrumentSpeed + 1),a
		ld (PLY_Track1_InstrumentSpeedCpt + 1),a
		ld a,(hl)
		// Get IsRetrig?. Code it only if different to 0, else next Instruments are going to overwrite it.
		or a				
		// jr z,$+5   // Not supported by z88dk, so:
		jr  z, ___skipldisretrigtrk1
		ld (PLY_PSGReg13_Retrig + 1),a
	.___skipldisretrigtrk1
		inc hl

		// When using the Instrument again, no need to give the Speed, it is skipped.
		ld (PLY_Track1_SavePTInstrument + 1),hl		

	.PLY_Track1_InstrumentResetPT
		ld (PLY_Track1_Instrument + 1),hl

	.PLY_Track1_NoNoteGiven

		ld a,1
	.PLY_Track1_NewInstrument_SetWait
		ld (PLY_Track1_WaitCounter + 1),a

	// Read the Track 2.
	// -----------------

	.PLY_Track2_WaitCounter 
		// Store the parameters, because the player below is called every frame, but the Read Track isn't.
		ld a,1
		dec a
		jr nz,PLY_Track2_NewInstrument_SetWait

	.PLY_Track2_PT ld hl,0
		call PLY_ReadTrack
		ld (PLY_Track2_PT + 1),hl
		jr c,PLY_Track2_NewInstrument_SetWait

		// No Wait command. Can be a Note and/or Effects.
		// Make a copy of the flags+Volume in A, not to temper with the original.
		ld a,d			

		// Volume ? If bit 4 was 1, then volume exists on b3-b0
		rra			
		jr nc,PLY_Track2_SameVolume
		and 0xf // %1111

		// na_th_an :: this had to be modified
		// ld (PLY_Track2_Volume),a
		ld (_PLY_Track2_Volume_Note + 2), a
		// 

	.PLY_Track2_SameVolume

		// New Pitch ?
		rl d				
		jr nc,PLY_Track2_NoNewPitch
		ld (PLY_Track2_PitchAdd + 1),ix
	.PLY_Track2_NoNewPitch

		// Note ? If no Note, we don't have to test if a new Instrument is here.
		rl d				
		jr nc,PLY_Track2_NoNoteGiven
		ld a,e
	.PLY_Transposition2 
		// Transpose Note according to the Transposition in the Linker.
		add a,0		
		
		// na_th_an :: this had to be modified		
		// ld (PLY_Track2_Note),a
		ld (_PLY_Track2_Volume_Note + 1), a
		//

		// Reset the TrackPitch.
		ld hl,0				
		ld (PLY_Track2_Pitch + 1),hl

		// New Instrument ?
		rl d				
		jr c,PLY_Track2_NewInstrument
	.PLY_Track2_SavePTInstrument 
		// Same Instrument. We recover its address to restart it.
		ld hl,0	
		// Reset the Instrument Speed Counter. Never seemed useful...
		ld a,(PLY_Track2_InstrumentSpeed + 1)		
		ld (PLY_Track2_InstrumentSpeedCpt + 1),a
		jr PLY_Track2_InstrumentResetPT

	.PLY_Track2_NewInstrument		
		// New Instrument. We have to get its new address, and Speed.
		// H is already set to 0 before.
		ld l,b				
		add hl,hl
	.PLY_Track2_InstrumentsTablePT 
		ld bc,0
		add hl,bc
		// Get Instrument address.
		ld a,(hl)			
		inc hl
		ld h,(hl)
		ld l,a
		// Get Instrument speed.
		ld a,(hl)			
		inc hl
		ld (PLY_Track2_InstrumentSpeed + 1),a
		ld (PLY_Track2_InstrumentSpeedCpt + 1),a
		ld a,(hl)
		// Get IsRetrig?. Code it only if different to 0, else next Instruments are going to overwrite it.
		or a				
		// jr z,$+5  // Not supported by z88dk, so:
		jr z, ___skipldisretrigtrk2
		ld (PLY_PSGReg13_Retrig + 1),a
	.___skipldisretrigtrk2
		inc hl

		// When using the Instrument again, no need to give the Speed, it is skipped.
		ld (PLY_Track2_SavePTInstrument + 1),hl		

	.PLY_Track2_InstrumentResetPT
		ld (PLY_Track2_Instrument + 1),hl

	.PLY_Track2_NoNoteGiven

		ld a,1
	.PLY_Track2_NewInstrument_SetWait
		ld (PLY_Track2_WaitCounter + 1),a

	// Read the Track 3.
	// -----------------

	.PLY_Track3_WaitCounter 
		// Store the parameters, because the player below is called every frame, but the Read Track isn't.
		ld a,1
		dec a
		jr nz,PLY_Track3_NewInstrument_SetWait

	.PLY_Track3_PT 
		ld hl,0
		call PLY_ReadTrack
		ld (PLY_Track3_PT + 1),hl
		jr c,PLY_Track3_NewInstrument_SetWait

		// No Wait command. Can be a Note and/or Effects.
		// Make a copy of the flags+Volume in A, not to temper with the original.
		ld a,d			

		// Volume ? If bit 4 was 1, then volume exists on b3-b0
		rra			
		jr nc,PLY_Track3_SameVolume
		and 0xf // %1111

		// na_th_an :: this had to be modified
		// ld (PLY_Track3_Volume),a
		ld (_PLY_Track3_Volume_Note + 2), a
		// 

	.PLY_Track3_SameVolume

		// New Pitch ?
		rl d				
		jr nc,PLY_Track3_NoNewPitch
		ld (PLY_Track3_PitchAdd + 1),ix
	.PLY_Track3_NoNewPitch

		//Note ? If no Note, we don't have to test if a new Instrument is here.
		rl d				
		jr nc,PLY_Track3_NoNoteGiven
		ld a,e
	.PLY_Transposition3 
		// Transpose Note according to the Transposition in the Linker.
		add a,0	
		
		// na_th_an :: this had to be modified
		// ld (PLY_Track3_Note),a
		ld (_PLY_Track3_Volume_Note + 1), a
		//

		// Reset the TrackPitch.
		ld hl,0				
		ld (PLY_Track3_Pitch + 1),hl

		// New Instrument ?
		rl d				
		jr c,PLY_Track3_NewInstrument
	.PLY_Track3_SavePTInstrument 
		// Same Instrument. We recover its address to restart it.
		ld hl,0	
		// Reset the Instrument Speed Counter. Never seemed useful...
		ld a,(PLY_Track3_InstrumentSpeed + 1)		
		ld (PLY_Track3_InstrumentSpeedCpt + 1),a
		jr PLY_Track3_InstrumentResetPT

	.PLY_Track3_NewInstrument		
		// New Instrument. We have to get its new address, and Speed.
		// H is already set to 0 before.
		ld l,b				
		add hl,hl
	.PLY_Track3_InstrumentsTablePT 
		ld bc,0
		add hl,bc
		// Get Instrument address.
		ld a,(hl)			
		inc hl
		ld h,(hl)
		ld l,a
		// Get Instrument speed.
		ld a,(hl)			
		inc hl
		ld (PLY_Track3_InstrumentSpeed + 1),a
		ld (PLY_Track3_InstrumentSpeedCpt + 1),a
		ld a,(hl)
		// Get IsRetrig?. Code it only if different to 0, else next Instruments are going to overwrite it.
		or a				
		// jr z,$+5 // Not supported by z88dk, so:
		jr z, ___skipldisretrigtrk3
		ld (PLY_PSGReg13_Retrig + 1),a
	.___skipldisretrigtrk3
		inc hl

		// When using the Instrument again, no need to give the Speed, it is skipped.
		ld (PLY_Track3_SavePTInstrument + 1),hl		

	.PLY_Track3_InstrumentResetPT
		ld (PLY_Track3_Instrument + 1),hl

	.PLY_Track3_NoNoteGiven

		ld a,1
	.PLY_Track3_NewInstrument_SetWait
		ld (PLY_Track3_WaitCounter + 1),a

	.PLY_Speed 
		ld a,1
	.PLY_SpeedEnd
		ld (PLY_SpeedCpt + 1),a

	// Play the Sound on Track 3
	// -------------------------
	
	// Plays the sound on each frame, but only save the forwarded Instrument pointer when Instrument Speed is reached.
	// This is needed because TrackPitch is involved in the Software Frequency/Hardware Frequency calculation, and is calculated every frame.

		ld iy,PLY_PSGRegistersArray + 4
	.PLY_Track3_Pitch 
		ld hl,0
	.PLY_Track3_PitchAdd 
		ld de,0
		add hl,de
		ld (PLY_Track3_Pitch + 1),hl
		. Shift the Pitch to slow its speed.
		sra h				
		rr l
		sra h
		rr l
		ex de,hl
		exx

	// Self modifying code. These two equs point to the literal "0" in the ld de, 0 below.
	// Volume is MSB, Note is LSB. I'm using a label and fixing the code which addresses the equs.
	// PLY_Track3_Volume equ $+2
	// PLY_Track3_Note equ $+1
	._PLY_Track3_Volume_Note
		// D=Inverted Volume E=Note
		ld de,0				

	.PLY_Track3_Instrument 
		ld hl,0
		call PLY_PlaySound

	.PLY_Track3_InstrumentSpeedCpt 
		ld a,1
		dec a
		jr nz,PLY_Track3_PlayNoForward
		ld (PLY_Track3_Instrument + 1),hl
	
	.PLY_Track3_InstrumentSpeed 
		ld a,6
	.PLY_Track3_PlayNoForward
		ld (PLY_Track3_InstrumentSpeedCpt + 1),a

	// Play Sound Effects on Track 3 
	
	.PLY_SFX_Track3_Pitch 
		ld de,0
		exx
	
	// Self modifying code. These two equs point to the literal "0" in the ld de, 0 below.
	// Volume is MSB, Note is LSB. I'm using a label and fixing the code which addresses the equs.
	// PLY_SFX_Track3_Volume equ $+2
	// PLY_SFX_Track3_Note equ $+1
	._PLY_SFX_Track3_Volume_note
		// D=Inverted Volume E=Note
		ld de,0				

	.PLY_SFX_Track3_Instrument 
		// If 0, no sound effect.
		ld hl,0	
		ld a,l
		or h
		jr z,PLY_SFX_Track3_End
		ld a,1
		ld (PLY_PS_EndSound_SFX + 1),a
		call PLY_PlaySound
		xor a
		ld (PLY_PS_EndSound_SFX + 1),a
		// If the new address is 0, the instrument is over. Speed is set in the process, we don't care.
		ld a,l				
		or h
		jr z,PLY_SFX_Track3_Instrument_SetAddress

	.PLY_SFX_Track3_InstrumentSpeedCpt 
		ld a,1
		dec a
		jr nz,PLY_SFX_Track3_PlayNoForward
	.PLY_SFX_Track3_Instrument_SetAddress
		ld (PLY_SFX_Track3_Instrument + 1),hl
	.PLY_SFX_Track3_InstrumentSpeed 
		ld a,6
	.PLY_SFX_Track3_PlayNoForward
		ld (PLY_SFX_Track3_InstrumentSpeedCpt + 1),a

	.PLY_SFX_Track3_End

		// Save the Register 7 of the Track 3.
		ld a,ixl			
		ex af,af

	// Play the Sound on Track 2
	// -------------------------

		ld iy,PLY_PSGRegistersArray + 2
	.PLY_Track2_Pitch 
		ld hl,0
	.PLY_Track2_PitchAdd 
		ld de,0
		add hl,de
		ld (PLY_Track2_Pitch + 1),hl
		// Shift the Pitch to slow its speed.
		sra h				
		rr l
		sra h
		rr l
		ex de,hl
		exx

	// Self modifying code. These two equs point to the literal "0" in the ld de, 0 below.
	// Volume is MSB, Note is LSB. I'm using a label and fixing the code which addresses the equs.
	// PLY_Track2_Volume equ $+2
	// PLY_Track2_Note equ $+1
	._PLY_Track2_Volume_Note
		// D=Inverted Volume E=Note
		ld de,0				

	.PLY_Track2_Instrument 
		// ld hl,0
		call PLY_PlaySound

	.PLY_Track2_InstrumentSpeedCpt 
		ld a,1
		dec a
		jr nz,PLY_Track2_PlayNoForward
		ld (PLY_Track2_Instrument + 1),hl
	.PLY_Track2_InstrumentSpeed 
		ld a,6
	.PLY_Track2_PlayNoForward
		ld (PLY_Track2_InstrumentSpeedCpt + 1),a

	// Play Sound Effects on Track 2

	.PLY_SFX_Track2_Pitch 
		ld de,0
		exx

	// Self modifying code. These two equs point to the literal "0" in the ld de, 0 below.
	// Volume is MSB, Note is LSB. I'm using a label and fixing the code which addresses the equs.		
	// PLY_SFX_Track2_Volume equ $+2
	// PLY_SFX_Track2_Note equ $+1
	._PLY_SFX_Track2_Volume_note
		// D=Inverted Volume E=Note
		ld de,0				

	.PLY_SFX_Track2_Instrument 
		ld hl,0	;If 0, no sound effect.
		ld a,l
		or h
		jr z,PLY_SFX_Track2_End
		ld a,1
		ld (PLY_PS_EndSound_SFX + 1),a
		call PLY_PlaySound
		xor a
		ld (PLY_PS_EndSound_SFX + 1),a
		// If the new address is 0, the instrument is over. Speed is set in the process, we don't care.
		ld a,l				
		or h
		jr z,PLY_SFX_Track2_Instrument_SetAddress

	.PLY_SFX_Track2_InstrumentSpeedCpt 
		ld a,1
		dec a
		jr nz,PLY_SFX_Track2_PlayNoForward

	.PLY_SFX_Track2_Instrument_SetAddress
		ld (PLY_SFX_Track2_Instrument + 1),hl

	.PLY_SFX_Track2_InstrumentSpeed 
		ld a,6
	.PLY_SFX_Track2_PlayNoForward
		ld (PLY_SFX_Track2_InstrumentSpeedCpt + 1),a

	.PLY_SFX_Track2_End
	
		ex af,af
		// Mix Reg7 from Track2 with Track3, making room first.
		add a,a			
		or ixl
		rla
		ex af,af

	// Play the Sound on Track 1
	// -------------------------

		ld iy,PLY_PSGRegistersArray
	.PLY_Track1_Pitch 
		ld hl,0
	.PLY_Track1_PitchAdd 
		ld de,0
		add hl,de
		ld (PLY_Track1_Pitch + 1),hl
		// Shift the Pitch to slow its speed.
		sra h				
		rr l
		sra h
		rr l
		ex de,hl
		exx

	// Self modifying code. These two equs point to the literal "0" in the ld de, 0 below.
	// Volume is MSB, Note is LSB. I'm using a label and fixing the code which addresses the equs.			
	// PLY_Track1_Volume equ $+2
	// PLY_Track1_Note equ $+1
	._PLY_Track1_Volume_Note
		// D=Inverted Volume E=Note
		ld de,0				

	.PLY_Track1_Instrument 
		ld hl,0
		call PLY_PlaySound

	.PLY_Track1_InstrumentSpeedCpt 
		ld a,1
		dec a
		jr nz,PLY_Track1_PlayNoForward
		ld (PLY_Track1_Instrument + 1),hl
	.PLY_Track1_InstrumentSpeed 
		ld a,6
	.PLY_Track1_PlayNoForward
		ld (PLY_Track1_InstrumentSpeedCpt + 1),a

	// Play Sound Effects on Track 1
	
	.PLY_SFX_Track1_Pitch 
		ld de,0
		exx
	
	// Self modifying code. These two equs point to the literal "0" in the ld de, 0 below.
	// Volume is MSB, Note is LSB. I'm using a label and fixing the code which addresses the equs.
	// PLY_SFX_Track1_Volume equ $+2
	// PLY_SFX_Track1_Note equ $+1
	._PLY_SFX_Track1_Volume_note
		// D=Inverted Volume E=Note
		ld de,0				

	.PLY_SFX_Track1_Instrument 
		// If 0, no sound effect.
		ld hl,0	
		ld a,l
		or h
		jr z,PLY_SFX_Track1_End
		ld a,1
		ld (PLY_PS_EndSound_SFX + 1),a
		call PLY_PlaySound
		xor a
		ld (PLY_PS_EndSound_SFX + 1),a
		// If the new address is 0, the instrument is over. Speed is set in the process, we don't care.
		ld a,l				
		or h
		jr z,PLY_SFX_Track1_Instrument_SetAddress

	.PLY_SFX_Track1_InstrumentSpeedCpt 
		ld a,1
		dec a
		jr nz,PLY_SFX_Track1_PlayNoForward

	.PLY_SFX_Track1_Instrument_SetAddress
		ld (PLY_SFX_Track1_Instrument + 1),hl

	.PLY_SFX_Track1_InstrumentSpeed 
		ld a,6
	.PLY_SFX_Track1_PlayNoForward
		ld (PLY_SFX_Track1_InstrumentSpeedCpt + 1),a

	.PLY_SFX_Track1_End
	
		ex af,af
		or ixl			;Mix Reg7 from Track3 with Track2+1.

	// ;Send the registers to PSG. 

	.PLY_SendRegisters

		ld de,0xc080
		ld b,0xf6
		out (c),d	;0xf6c0
		exx
		ld hl,PLY_PSGRegistersArray
		ld e,0xf6
		ld bc,0xf401

	// Register 0
		defb 0xed,0x71	;0xf400+Register
		ld b,e
		defb 0xed,0x71	;0xf600
		dec b
		outi		;0xf400+value
		exx
		out (c),e	;0xf680
		out (c),d	;0xf6c0
		exx

	// Register 1
		out (c),c
		ld b,e
		defb 0xed,0x71
		dec b
		outi
		exx
		out (c),e
		out (c),d
		exx
		inc c

	// Register 2
		out (c),c
		ld b,e
		defb 0xed,0x71
		dec b
		outi
		exx
		out (c),e
		out (c),d
		exx
		inc c

	// Register 3
		out (c),c
		ld b,e
		defb 0xed,0x71
		dec b
		outi
		exx
		out (c),e
		out (c),d
		exx
		inc c

	// Register 4
		out (c),c
		ld b,e
		defb 0xed,0x71
		dec b
		outi
		exx
		out (c),e
		out (c),d
		exx
		inc c

	// Register 5
		out (c),c
		ld b,e
		defb 0xed,0x71
		dec b
		outi
		exx
		out (c),e
		out (c),d
		exx
		inc c

	// Register 6
		out (c),c
		ld b,e
		defb 0xed,0x71
		dec b
		outi
		exx
		out (c),e
		out (c),d
		exx
		inc c

	// Register 7
		out (c),c
		ld b,e
		defb 0xed,0x71
		dec b
		dec b
		out (c),a			;Read A register instead of the list.
		exx
		out (c),e
		out (c),d
		exx
		inc c

	// Register 8
		out (c),c
		ld b,e
		defb 0xed,0x71
		dec b
		outi
		exx
		out (c),e
		out (c),d
		exx
		inc c
		inc hl				;Skip unused byte.

	// Register 9
		out (c),c
		ld b,e
		defb 0xed,0x71
		dec b
		outi
		exx
		out (c),e
		out (c),d
		exx
		inc c
		inc hl				;Skip unused byte.

	// Register 10
		out (c),c
		ld b,e
		defb 0xed,0x71
		dec b
		outi
		exx
		out (c),e
		out (c),d
		exx
		inc c

	// Register 11
		out (c),c
		ld b,e
		defb 0xed,0x71
		dec b
		outi
		exx
		out (c),e
		out (c),d
		exx
		inc c

	// Register 12
		out (c),c
		ld b,e
		defb 0xed,0x71
		dec b
		outi
		exx
		out (c),e
		out (c),d
		exx
		inc c

	// Register 13

	.PLY_PSGReg13_Code
		ld a,(hl)
	.PLY_PSGReg13_Retrig 
		cp 255				;If IsRetrig?, force the R13 to be triggered.
		ret z
		ld (PLY_PSGReg13_Retrig + 1),a
		out (c),c
		ld b,e
		defb 0xed,0x71
		dec b
		outi
		exx
		out (c),e
		out (c),d
		ret

	// There are two holes in the list, because the Volume registers are set relatively to the Frequency of the same Channel (+7, always).
	// Also, the Reg7 is passed as a register, so is not kept in the memory.
	// TODO Move this to 0xDF80?

	.PLY_PSGRegistersArray
	.PLY_PSGReg0 
		defb 0
	.PLY_PSGReg1 
		defb 0
	.PLY_PSGReg2 
		defb 0
	.PLY_PSGReg3 
		defb 0
	.PLY_PSGReg4 
		defb 0
	.PLY_PSGReg5 
		defb 0
	.PLY_PSGReg6 
		defb 0
	.PLY_PSGReg8 
		defb 0		;+7
	    defb 0
	.PLY_PSGReg9 
		defb 0		;+9
	    defb 0
	.PLY_PSGReg10 
		defb 0		;+11
	.PLY_PSGReg11 
		defb 0
	.PLY_PSGReg12 
		defb 0
	.PLY_PSGReg13 
		defb 0
	.PLY_PSGRegistersArray_End

	// Plays a sound stream.
	// HL=Pointer on Instrument Data
	// IY=Pointer on Register code (volume, frequency).
	// E=Note
	// D=Inverted Volume
	// DE'=TrackPitch
	// 
	// RET=
	// HL=New Instrument pointer.
	// IXL=Reg7 mask (x00x)
	// 
	// Also used inside =
	// B,C=read byte/second byte.
	// IXH=Save original Note (only used for Independant mode).	

	.PLY_PlaySound
		ld b,(hl)
		inc hl
		rr b
		jp c,PLY_PS_Hard

	// Software Sound
	
		// Second Byte needed ?
		rr b
		jr c,PLY_PS_S_SecondByteNeeded

		// No second byte needed. We need to check if Volume is null or not.
		ld a,b
		and 0xf // %1111
		jr nz,PLY_PS_S_SoundOn

		// Null Volume. It means no Sound. We stop the Sound, the Noise, and it's over.
		// We have to make the volume to 0, because if a bass Hard was activated before, we have to stop it.
		ld (iy + 7),a			
		ld ixl,0x9 // %1001

		ret

	.PLY_PS_S_SoundOn
		//Volume is here, no Second Byte needed. It means we have a simple Software sound (Sound = On, Noise = Off)
		//We have to test Arpeggio and Pitch, however.
		ld ixl,0x8 // %1000

		// Code Volume.
		sub d						
		//jr nc,$+3
		jr nc, ___PLY_PS_S_SoundOn_skip3
		xor a
	.___PLY_PS_S_SoundOn_skip3
		ld (iy + 7),a

		// Needed for the subroutine to get the good flags.
		rr b						
		call PLY_PS_CalculateFrequency
		// Code Frequency.
		ld (iy + 0),l					
		ld (iy + 1),h
		exx

		ret

	.PLY_PS_S_SecondByteNeeded
		// By defaut, No Noise, Sound.
		ld ixl,0x8 // %1000	

		// Second Byte needed.
		ld c,(hl)
		inc hl

		// Noise ?
		ld a,c
		and 0x1F // %11111
		jr z,PLY_PS_S_SBN_NoNoise
		ld (PLY_PSGReg6),a
		// Open Noise Channel.
		ld ixl,0 // %0000					
	.PLY_PS_S_SBN_NoNoise

		// Here we have either Volume and/or Sound. So first we need to read the Volume.
		ld a,b
		and 0xf // %1111
		sub d						;Code Volume.
		//jr nc,$+3
		jr nc, ___PLY_PS_S_SBN_NoNoise_skip3
		xor a
	.___PLY_PS_S_SBN_NoNoise_skip3
		ld (iy + 7),a

		// Sound ?
		bit 5,c
		jr nz,PLY_PS_S_SBN_Sound
		// No Sound. Stop here.
		inc ixl						;Set Sound bit to stop the Sound.
		ret

	.PLY_PS_S_SBN_Sound
		// Manual Frequency ?
		rr b						;Needed for the subroutine to get the good flags.
		bit 6,c
		call PLY_PS_CalculateFrequency_TestManualFrequency
		ld (iy + 0),l					;Code Frequency.
		ld (iy + 1),h
		exx

		ret

	// Hard Sound

	.PLY_PS_Hard
		// We don't set the Volume to 16 now because we may have reached the end of the sound !

		// Test Retrig here, it is common to every Hard sounds.
		rr b						
		jr nc,PLY_PS_Hard_NoRetrig
		// Retrig only if it is the first step in this line of Instrument !
		ld a,(PLY_Track1_InstrumentSpeedCpt + 1)	
		ld c,a
		ld a,(PLY_Track1_InstrumentSpeed + 1)
		cp c
		jr nz,PLY_PS_Hard_NoRetrig
		// PLY_RetrigValue
		ld a,0xfe 
		ld (PLY_PSGReg13_Retrig + 1),a
	.PLY_PS_Hard_NoRetrig

		// Independant/Loop or Software/Hardware Dependent ?
		// We don't shift the bits, so that we can use the same code (Frequency calculation) several times.
		bit 1,b				
		jp nz,PLY_PS_Hard_LoopOrIndependent

		// Hardware Sound.
		// Set Volume
		ld (iy + 7),16					
		// Sound is always On here (only Independence mode can switch it off).
		ld ixl,%1000					

		/7 This code is common to both Software and Hardware Dependent.
		// Get Second Byte.
		ld c,(hl)			
		inc hl
		// Get the Hardware Envelope waveform.
		ld a,c				
		// We don't care about the bit 7-4, but we have to clear them, else the waveform might be reset.
		and 0xf // %1111			
		ld (PLY_PSGReg13),a

		bit 0,b
		jr z,PLY_PS_HardwareDependent

	// Software Dependent
	
		// Calculate the Software frequency
		// Manual Frequency ? -2 Because the byte has been shifted previously.
		bit 4-2,b		
		call PLY_PS_CalculateFrequency_TestManualFrequency
		// Code Software Frequency.
		ld (iy + 0),l		
		ld (iy + 1),h
		exx

		// Shift the Frequency.
		ld a,c
		rra
		// Shift=Shift*4. The shift is inverted in memory (7 - Editor Shift).
		rra			
		and 0x1c // %11100
		ld (PLY_PS_SD_Shift + 1),a
		// Used to get the HardwarePitch flag within the second registers set.
		ld a,b			
		exx

	.PLY_PS_SD_Shift 
		//jr $+2 		// !!
		jr _PLY_PS_SD_Shift0
	._PLY_PS_SD_Shift0
		srl h
		rr l
		srl h
		rr l
		srl h
		rr l
		srl h
		rr l
		srl h
		rr l
		srl h
		rr l
		srl h
		rr l
		//jr nc,$+3
		jr nc, ___PLY_PS_SD_Shift_B_skip3
		inc hl
	.___PLY_PS_SD_Shift_B_skip3

		// Hardware Pitch ?
		bit 7-2,a
		jr z,PLY_PS_SD_NoHardwarePitch
		// Get Pitch and add it to the just calculated Hardware Frequency.
		exx						
		ld a,(hl)
		inc hl
		exx
		// Slow. Can be optimised ? Probably never used anyway.....
		add a,l						
		ld l,a
		exx
		ld a,(hl)
		inc hl
		exx
		adc a,h
		ld h,a
	.PLY_PS_SD_NoHardwarePitch
		ld (PLY_PSGReg11),hl
		exx

		// This code is also used by Hardware Dependent.
	.PLY_PS_SD_Noise
		// Noise ?
		bit 7,c
		ret z
		ld a,(hl)
		inc hl
		ld (PLY_PSGReg6),a
		ld ixl,0x0 // %0000
		ret	

	// Hardware Dependent
	
	.PLY_PS_HardwareDependent
		// Calculate the Hardware frequency
		// Manual Hardware Frequency ? -2 Because the byte has been shifted previously.
		bit 4-2,b			
		call PLY_PS_CalculateFrequency_TestManualFrequency
		// Code Hardware Frequency.
		ld (PLY_PSGReg11),hl		
		exx

		// Shift the Hardware Frequency.
		ld a,c
		rra
		// Shift=Shift*4. The shift is inverted in memory (7 - Editor Shift).
		rra			
		and 0x1c // %11100
		ld (PLY_PS_HD_Shift + 1),a
		// Used to get the Software flag within the second registers set.
		ld a,b			
		exx

	.PLY_PS_HD_Shift 
		//jr $+2
		jr _PLY_PS_HD_Shift0
	._PLY_PS_HD_Shift0
		sla l
		rl h
		sla l
		rl h
		sla l
		rl h
		sla l
		rl h
		sla l
		rl h
		sla l
		rl h
		sla l
		rl h

		// oftware Pitch ?
		bit 7-2,a
		jr z,PLY_PS_HD_NoSoftwarePitch
		// Get Pitch and add it to the just calculated Software Frequency.
		exx						
		ld a,(hl)
		inc hl
		exx
		add a,l
		// Slow. Can be optimised ? Probably never used anyway.....
		ld l,a						
		exx
		ld a,(hl)
		inc hl
		exx
		adc a,h
		ld h,a
	.PLY_PS_HD_NoSoftwarePitch
		// Code Frequency.
		ld (iy + 0),l					
		ld (iy + 1),h
		exx

		// Go to manage Noise, common to Software Dependent.
		jr PLY_PS_SD_Noise

	.PLY_PS_Hard_LoopOrIndependent
		// We mustn't shift it to get the result in the Carry, as it would be mess the structure
		bit 0,b					
		// of the flags, making it uncompatible with the common code.
		jr z,PLY_PS_Independent			

		// The sound has ended.
		// Mark the "end of sound" by returning a 0 as an address.
		
	.PLY_PS_EndSound_SFX ld a,0			;Is the sound played is a SFX (1) or a normal sound (0) ?
		or a
		jr z,PLY_PS_EndSound_NotASFX
		ld hl,0
		ret
	.PLY_PS_EndSound_NotASFX
	
		// The sound has ended. Read the new pointer and restart instrument.

		ld a,(hl)
		inc hl
		ld h,(hl)
		ld l,a
		jp PLY_PlaySound

	// Independent

	.PLY_PS_Independent
		// Set Volume
		ld (iy + 7),16			

		// Sound ?
		// -2 Because the byte has been shifted previously.
		bit 7-2,b			
		jr nz,PLY_PS_I_SoundOn
		
		// No Sound ! It means we don't care about the software frequency (manual frequency, arpeggio, pitch).
		ld ixl,0x9 // %1001

		jr PLY_PS_I_SkipSoftwareFrequencyCalculation
	
	.PLY_PS_I_SoundOn
		// Sound is on.
		ld ixl,0x8 // %1000			
		// Save the original note for the Hardware frequency, because a Software Arpeggio will modify it.
		ld ixh,e			

		// Calculate the Software frequency
		// Manual Frequency ? -2 Because the byte has been shifted previously.
		bit 4-2,b			
		call PLY_PS_CalculateFrequency_TestManualFrequency
		// Code Software Frequency.
		ld (iy + 0),l			
		ld (iy + 1),h
		exx

		ld e,ixh
	.PLY_PS_I_SkipSoftwareFrequencyCalculation

		// Get Second Byte.
		ld b,(hl)			
		inc hl
		// Get the Hardware Envelope waveform.
		ld a,b				
		// We don't care about the bit 7-4, but we have to clear them, else the waveform might be reset.
		and 0xf //%1111			
		ld (PLY_PSGReg13),a

		// Calculate the Hardware frequency
		// Must shift it to match the expected data of the subroutine.
		rr b				
		rr b
		// Manual Hardware Frequency ? -2 Because the byte has been shifted previously.
		bit 4-2,b			
		call PLY_PS_CalculateFrequency_TestManualFrequency
		ld (PLY_PSGReg11),hl		;Code Hardware Frequency.
		exx

		// Noise ? We can't use the previous common code, because the setting of the Noise is different, since Independent can have no Sound.
		bit 7-2,b
		ret z
		ld a,(hl)
		inc hl
		ld (PLY_PSGReg6),a
		// Set the Noise bit.
		ld a,ixl	
		res 3,a
		ld ixl,a
		ret		

	// Subroutine that =
	// If Manual Frequency? (Flag Z off), read frequency (Word) and adds the TrackPitch (DE').
	// Else, Auto Frequency.
	// 	if Arpeggio? = 1 (bit 3 from B), read it (Byte).
	// 	if Pitch? = 1 (bit 4 from B), read it (Word).
	// 	Calculate the frequency according to the Note (E) + Arpeggio + TrackPitch (DE').

	// HL = Pointer on Instrument data.
	// DE'= TrackPitch.

	// RET=
	// HL = Pointer on Instrument moved forward.
	// HL'= Frequency
	// 	RETURN IN AUXILIARY REGISTERS
	.PLY_PS_CalculateFrequency_TestManualFrequency
		jr z,PLY_PS_CalculateFrequency
		// Manual Frequency. We read it, no need to read Pitch and Arpeggio.
		// However, we add TrackPitch to the read Frequency, and that's all.
		ld a,(hl)
		inc hl
		exx
		// Add TrackPitch LSB.
		add a,e						
		ld l,a
		exx
		ld a,(hl)
		inc hl
		exx
		// Add TrackPitch HSB.
		adc a,d						
		ld h,a
		ret

	.PLY_PS_CalculateFrequency
		// Pitch ?
		bit 5-1,b
		jr z,PLY_PS_S_SoundOn_NoPitch
		ld a,(hl)
		inc hl
		exx
		// If Pitch found, add it directly to the TrackPitch.
		add a,e						
		ld e,a
		exx
		ld a,(hl)
		inc hl
		exx
		adc a,d
		ld d,a
		exx
		PLY_PS_S_SoundOn_NoPitch

		// Arpeggio ?
		ld a,e
		bit 4-1,b
		jr z,PLY_PS_S_SoundOn_ArpeggioEnd
		// Add Arpeggio to Note.
		add a,(hl)					
		inc hl
		cp 144
		// jr c,$+4
		jr c, PLY_PS_S_SoundOn_ArpeggioEnd
		ld a,143
	.PLY_PS_S_SoundOn_ArpeggioEnd

		// Frequency calculation.
		exx
		ld l,a
		ld h,0
		add hl,hl
		
		ld bc,PLY_FrequencyTable
		add hl,bc

		ld a,(hl)
		inc hl
		ld h,(hl)
		ld l,a
		add hl,de					;Add TrackPitch + InstrumentPitch (if any).

		ret

	// Read one Track.
	// HL=Track Pointer.

	// Ret =
	// HL=New Track Pointer.
	// Carry = 1 = Wait A lines. Carry=0=Line not empty.
	// A=Wait (0(=256)-127), if Carry.
	// D=Parameters + Volume.
	// E=Note
	// B=Instrument. 0=RST
	// IX=PitchAdd. Only used if Pitch? = 1.
	.PLY_ReadTrack
		ld a,(hl)
		inc hl
		// Full Optimisation ? If yes = Note only, no Pitch, no Volume, Same Instrument.
		srl a			
		jr c,PLY_ReadTrack_FullOptimisation
		// 0-31 = Wait.
		sub 32			
		jr c,PLY_ReadTrack_Wait
		jr z,PLY_ReadTrack_NoOptimisation_EscapeCode
		// 0 (32-32) = Escape Code for more Notes (parameters will be read)
		dec a			

		// Note. Parameters are present. But the note is only present if Note? flag is 1.
		// Save Note.
		ld e,a			

		// Read Parameters
	.PLY_ReadTrack_ReadParameters
		ld a,(hl)
		// Save Parameters.
		ld d,a			
		inc hl

		// Pitch ?
		rla			
		jr nc,PLY_ReadTrack_Pitch_End
		// Get PitchAdd
		ld b,(hl)		
		ld ixl,b
		inc hl
		ld b,(hl)
		ld ixh,b
		inc hl
	.PLY_ReadTrack_Pitch_End

		// Skip IsNote? flag.
		rla			
		// New Instrument ?
		rla			
		ret nc
		ld b,(hl)
		inc hl
		// Remove Carry, as the player interpret it as a Wait command.
		or a			
		ret

	// Escape code, read the Note and returns to read the Parameters.
	.PLY_ReadTrack_NoOptimisation_EscapeCode
		ld e,(hl)
		inc hl
		jr PLY_ReadTrack_ReadParameters

	.PLY_ReadTrack_FullOptimisation
		// Note only, no Pitch, no Volume, Same Instrument.
		// Note only.
		ld d,0x40 // %01000000			
		sub 1
		ld e,a
		ret nc
		// Escape Code found (0). Read Note.
		ld e,(hl)			
		inc hl
		or a
		ret

	.PLY_ReadTrack_Wait
		add a,32
		ret

	.PLY_FrequencyTable
		defw 3822,3608,3405,3214,3034,2863,2703,2551,2408,2273,2145,2025
		defw 1911,1804,1703,1607,1517,1432,1351,1276,1204,1136,1073,1012
		defw 956,902,851,804,758,716,676,638,602,568,536,506
		defw 478,451,426,402,379,358,338,319,301,284,268,253
		defw 239,225,213,201,190,179,169,159,150,142,134,127
		defw 119,113,106,100,95,89,84,80,75,71,67,63
		defw 60,56,53,50,47,45,42,40,38,36,34,32
		defw 30,28,27,25,24,22,21,20,19,18,17,16
		defw 15,14,13,13,12,11,11,10,9,9,8,8
		defw 7,7,7,6,6,6,5,5,5,4,4,4
		defw 4,4,3,3,3,3,3,2,2,2,2,2
		defw 2,2,2,2,1,1,1,1,1,1,1,1	

	// DE = Music
	.PLY_Init
		// Skip Header, SampleChannel, YM Clock (DB*3), and Replay Frequency.
		ld hl,9				
		add hl,de

		ld de,PLY_Speed + 1
		// Copy Speed.
		ldi				
		// Get Instruments chunk size.
		ld c,(hl)			
		inc hl
		ld b,(hl)
		inc hl
		ld (PLY_Track1_InstrumentsTablePT + 1),hl
		ld (PLY_Track2_InstrumentsTablePT + 1),hl
		ld (PLY_Track3_InstrumentsTablePT + 1),hl

		// Skip Instruments to go to the Linker address.
		add hl,bc			
		// Get the pre-Linker information of the first pattern.
		ld de,PLY_Height + 1
		ldi
		ld de,PLY_Transposition1 + 1
		ldi
		ld de,PLY_Transposition2 + 1
		ldi
		ld de,PLY_Transposition3 + 1
		ldi
		ld de,PLY_SaveSpecialTrack + 1
		ldi
		ldi
		// Get the Linker address.
		ld (PLY_Linker_PT + 1),hl	

		ld a,1
		ld (PLY_SpeedCpt + 1),a
		ld (PLY_HeightCpt + 1),a

		ld a,#ff
		ld (PLY_PSGReg13),a
		
		// Set the Instruments pointers to Instrument 0 data (Header has to be skipped).
		ld hl,(PLY_Track1_InstrumentsTablePT + 1)
		ld e,(hl)
		inc hl
		ld d,(hl)
		ex de,hl
		// Skip Instrument 0 Header.
		inc hl					
		inc hl
		ld (PLY_Track1_Instrument + 1),hl
		ld (PLY_Track2_Instrument + 1),hl
		ld (PLY_Track3_Instrument + 1),hl
		ret	

	;Stop the music, cut the channels.
	.PLY_Stop
		ld hl,PLY_PSGReg8
		ld bc,0x0300
		ld (hl),c
		inc hl
		djnz $-2
		ld a,0x3f // %00111111
		jp PLY_SendRegisters

	//Initialize the Sound Effects.
	//DE = SFX Music.
	.PLY_SFX_Init
		//Find the Instrument Table.
		ld hl,12
		add hl,de
		ld (PLY_SFX_Play_InstrumentTable + 1),hl
		
	// Clear the three channels of any sound effect.
	.PLY_SFX_StopAll
		ld hl,0
		ld (PLY_SFX_Track1_Instrument + 1),hl
		ld (PLY_SFX_Track2_Instrument + 1),hl
		ld (PLY_SFX_Track3_Instrument + 1),hl
		ret

	// Initialize the Sound Effects.
	// DE = SFX Music.
	.PLY_SFX_Init
		// Find the Instrument Table.
		ld hl,12
		add hl,de
		ld (PLY_SFX_Play_InstrumentTable + 1),hl
		
	// Clear the three channels of any sound effect.
	.PLY_SFX_StopAll
		ld hl,0
		ld (PLY_SFX_Track1_Instrument + 1),hl
		ld (PLY_SFX_Track2_Instrument + 1),hl
		ld (PLY_SFX_Track3_Instrument + 1),hl
		ret

	// PLY_SFX_OffsetPitch equ 0
	// PLY_SFX_OffsetVolume equ PLY_SFX_Track1_Volume - PLY_SFX_Track1_Pitch
	// PLY_SFX_OffsetNote equ PLY_SFX_Track1_Note - PLY_SFX_Track1_Pitch
	// PLY_SFX_OffsetInstrument equ PLY_SFX_Track1_Instrument - PLY_SFX_Track1_Pitch
	// PLY_SFX_OffsetSpeed equ PLY_SFX_Track1_InstrumentSpeed - PLY_SFX_Track1_Pitch
	// PLY_SFX_OffsetSpeedCpt equ PLY_SFX_Track1_InstrumentSpeedCpt - PLY_SFX_Track1_Pitch

	// I don't really know how to translate the above constructions to z88dk inline assembly,
	// so I've used pasmo to assemble the chunk of code and pre-calculate the numbers:

	// PLY_SFX_OffsetPitch 				EQU 00000H
	// PLY_SFX_Track1_VolumeNote 		EQU 00004H
	// PLY_SFX_OffsetVolume 			EQU 00006H
	// PLY_SFX_OffsetNote 				EQU 00005H
	// PLY_SFX_OffsetInstrument 		EQU 00007H
	// PLY_SFX_OffsetSpeed 				EQU 00023H
	// PLY_SFX_OffsetSpeedCpt			EQU 0001BH

	// Plays a Sound Effects along with the music.
	// A = No Channel (0,1,2)
	// L = SFX Number (>0)
	// H = Volume (0...F)
	// E = Note (0...143)
	// D = Speed (0 = As original, 1...255 = new Speed (1 is fastest))
	// BC = Inverted Pitch (-#FFFF -> FFFF). 0 is no pitch. The higher the pitch, the lower the sound.
	PLY_SFX_Play
		ld ix,PLY_SFX_Track1_Pitch
		or a
		jr z,PLY_SFX_Play_Selected
		ld ix,PLY_SFX_Track2_Pitch
		dec a
		jr z,PLY_SFX_Play_Selected
		ld ix,PLY_SFX_Track3_Pitch
		
	PLY_SFX_Play_Selected
		//Set Pitch
		//ld (ix + PLY_SFX_OffsetPitch + 1),c	
		ld (ix + 0 + 1),c	

		//ld (ix + PLY_SFX_OffsetPitch + 2),b
		ld (ix + 0 + 2),b

		// Set Note
		ld a,e					
		//ld (ix + PLY_SFX_OffsetNote),a
		ld (ix + 5),a
		// Set Volume
		ld a,15					
		sub h
		//ld (ix + PLY_SFX_OffsetVolume),a
		ld (ix + 6),a
		// Set Instrument Address
		ld h,0					
		add hl,hl
	.PLY_SFX_Play_InstrumentTable
		ld bc,0
		add hl,bc
		ld a,(hl)
		inc hl
		ld h,(hl)
		ld l,a
		// Read Speed or use the user's one ?
		ld a,d					
		or a
		jr nz,PLY_SFX_Play_UserSpeed
		// Get Speed
		ld a,(hl)				
	.PLY_SFX_Play_UserSpeed
		//ld (ix + PLY_SFX_OffsetSpeed + 1),a
		ld (ix + 0x23 + 1),a
		//ld (ix + PLY_SFX_OffsetSpeedCpt + 1),a
		ld (ix + 0x1B + 1),a
		// Skip Retrig
		inc hl					
		inc hl
		//ld (ix + PLY_SFX_OffsetInstrument + 1),l
		ld (ix + 7 + 1),l
		//ld (ix + PLY_SFX_OffsetInstrument + 2),h
		ld (ix + 7 + 2),h

		ret

	//Stops a sound effect on the selected channel
	//E = No Channel (0,1,2)
	//I used the E register instead of A so that Basic users can call this code in a straightforward way (call player+15, value).
	.PLY_SFX_Stop
		ld a,e
		ld hl,PLY_SFX_Track1_Instrument + 1
		or a
		jr z,PLY_SFX_Stop_ChannelFound
		ld hl,PLY_SFX_Track2_Instrument + 1
		dec a
		jr z,PLY_SFX_Stop_ChannelFound
		ld hl,PLY_SFX_Track3_Instrument + 1
		dec a

	.PLY_SFX_Stop_ChannelFound
		ld (hl),a
		inc hl
		ld (hl),a
		ret	

#endasm
		