// sealed chamber room 2, wailord / relicanth
#include "scriptlib.m4.h"

MESSAGE( 627, 9 ) // braille msg

// check for wailord
CHECK_PKMN_IN_SLOT( PKMN_WAILORD, 0, 1 )
    JUMP_TO_END

// check for relicanth
CHECK_PKMN_IN_SLOT( PKMN_RELICANTH, 5, 1 )
    JUMP_TO_END

EARTHQUAKE
WAIT( 15 )
EARTHQUAKE
WAIT( 40 )

PLAY_SOUND_EFFECT( SFX_ENTER_DOOR )
WAIT( 40 )
PLAY_SOUND_EFFECT( SFX_ENTER_DOOR )
WAIT( 40 )
PLAY_SOUND_EFFECT( SFX_ENTER_DOOR )
WAIT( 40 )
PLAY_SOUND_EFFECT( SFX_ENTER_DOOR )
WAIT( 40 )
PLAY_SOUND_EFFECT( SFX_ENTER_DOOR )
WAIT( 40 )

SET_FLAG( 136, 1 )
MESSAGE( 635, 1 )
END_OF_PROGRAM
