// MTE MK1 (la Churrera) v5.0
// Copyleft 2010-2014, 2020 by the Mojon Twins

// Modify p_vy
// Don't forget to use the veng_selector if VENG_SELECTOR is defined.

// Replicates the normal gravity / jetpac code from MK1 
// But this support variable A/G for puri / paco

#asm
		; Signed comparisons are hard
		; p_vy <= PLAYER_MAX_VY_CAYENDO - PLAYER_G

		; We are going to take a shortcut.
		; If p_vy < 0, just add PLAYER_G.
		; If p_vy > 0, we can use unsigned comparison anyway.

		ld  hl, (_p_vy)
		bit 7, h
		jr  nz, _player_gravity_add 	; < 0

	._player_gravity_comp1
		ld  de, PLAYER_MAX_VY_CAYENDO - PLAYER_G
		or  a
		push hl
		sbc hl, de
		pop hl
		jr  nc, _player_gravity_maximum

	._player_gravity_add
		ld  de, PLAYER_G
		add hl, de
		jr  _player_gravity_vy_set

	._player_gravity_maximum
		ld  hl, PLAYER_MAX_VY_CAYENDO

	._player_gravity_vy_set
		ld  (_p_vy), hl

	._player_gravity_done

		ld  a, (_p_gotten)
		or  a
		jr  z, _player_gravity_p_gotten_done

		; If HL = pvy > 0
		bit 7, h 
		jr  nz, _player_gravity_p_gotten_done

		ld  hl, 0
		ld  (_p_vy), hl
		
	._player_gravity_p_gotten_done
#endasm

if (cpc_TestKey (KEY_UP)) {
	#include "my/ci/on_controller_pressed/up.h"
	
	#asm
		// p_vy -= PLAYER_INCR_JETPAC;
			ld  hl, (_p_vy)
		._player_jetpac_increment
			ld  de, -PLAYER_INCR_JETPAC
			add hl, de
			ld  (_p_vy), hl

		// if (p_vy < -PLAYER_MAX_VY_JETPAC) p_vy = -PLAYER_MAX_VY_JETPAC;
		// Simplifying: if p_vy >= 0 -> do nothing.
		// If p_vy < 0, consider it unsigned 
		// Negative numbers if considered positive: -2 < -1 -> 254 < 255
		// So we can compare as if they were unsigned.

		// Is p_vy positive or negative
			bit 7, h 
			jr z, _player_jetpac_check_done

		// Negative, compare as unsigned.
		._player_jetpac_check_ld
			ld  de, -PLAYER_MAX_VY_JETPAC

			xor a
			sbc hl, de 

			jr  nc, _player_jetpac_check_done

			ld  (_p_vy), de

		._player_jetpac_check_done

	#endasm

	#include "my/ci/on_jetpac_boost.h"
} 