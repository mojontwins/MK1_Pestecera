PLY_SFX_Track1_Pitch ld de,0
	exx
; PLY_SFX_Track1_Volume equ $+2
; PLY_SFX_Track1_Note equ $+1
PLY_SFX_Track1_VolumeNote
	ld de,0				;D=Inverted Volume E=Note
PLY_SFX_Track1_Instrument ld hl,0	;If 0, no sound effect.
	ld a,l
	or h
	jr z,PLY_SFX_Track1_End
	ld a,1
	ld (PLY_PS_EndSound_SFX + 1),a
	;call PLY_PlaySound
	xor a
	ld (PLY_PS_EndSound_SFX + 1),a
	ld a,l				;If the new address is 0, the instrument is over. Speed is set in the process, we don't care.
	or h
	jr z,PLY_SFX_Track1_Instrument_SetAddress

PLY_SFX_Track1_InstrumentSpeedCpt ld a,1
	dec a
	jr nz,PLY_SFX_Track1_PlayNoForward
PLY_SFX_Track1_Instrument_SetAddress
	ld (PLY_SFX_Track1_Instrument + 1),hl
PLY_SFX_Track1_InstrumentSpeed ld a,6
PLY_SFX_Track1_PlayNoForward
	ld (PLY_SFX_Track1_InstrumentSpeedCpt + 1),a

PLY_SFX_Track1_End

PLY_PS_EndSound_SFX 
	ld a,0			;Is the sound played is a SFX (1) or a normal sound (0) ?