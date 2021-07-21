// scary pkmn, sableye 2
#include "scriptlib.m4.h"

MESSAGE( 454, 0 )

// battle sableye
MESSAGE( 449, 0 )
SET_FLAG( 181, 1 )
PLAY_MUSIC( BGM_BATTLE_WILD )
BATTLE_PKMN( 302, 30 )
RESTORE_MUSIC
CHECK_REGISTER( 0, 1, 3 )
    SET_FLAG( 181, 0 )
    FAINT_PLAYER
    JUMP_TO_END

CHECK_REGISTER( 1, 1, 1 )
    // player did not capture wailmer
    MESSAGE( 455, 0 )

MESSAGE( 457, 0 )

END_OF_PROGRAM
