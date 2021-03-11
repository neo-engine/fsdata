// scary pkmn, sableye 1
#include "scriptlib.m4.h"

MESSAGE( 454, 0 )

// battle sableye
MESSAGE( 449, 0 )
SET_FLAG( 180, 1 )
PLAY_MUSIC( MOD_BATTLE_WILD )
BATTLE_PKMN( 302, 25 )
RESTORE_MUSIC
CHECK_REGISTER( 0, 1, 3 )
    SET_FLAG( 180, 0 )
    FAINT_PLAYER
    JUMP_TO_END

CHECK_REGISTER( 1, 1, 1 )
    // player did not capture sableye
    MESSAGE( 455, 0 )

MESSAGE( 456, 0 )

END_OF_PROGRAM
