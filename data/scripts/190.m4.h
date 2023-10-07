// E4 Phoebe
#include "scriptlib.m4.h"

#define V_HALL_OF_FAME_VICTORIES 37

CHECK_VAR( V_HALL_OF_FAME_VICTORIES, 0, 6 )
// player is champ
    // check if already battled
    CHECK_TRAINER_FLAG( 75, 0, 2 )
        MESSAGE( 646, 0 )
        JUMP_TO_END
    MESSAGE( 648, 0 )
    BATTLE_TRAINER( 75, DOUBLE )
    SKIP( 5 )
// player is not yet champ
    // check if already battled
    CHECK_TRAINER_FLAG( 68, 0, 2 )
        MESSAGE( 646, 0 )
        JUMP_TO_END
    MESSAGE( 647, 0 )
    BATTLE_TRAINER( 68, SINGLE )

CHECK_REGISTER( 0, 1, 2 )
    FAINT_PLAYER
    JUMP_TO_END

SET_TRAINER_FLAG( 75, 1 )
SET_TRAINER_FLAG( 68, 1 )
// activate door
SET_BLOCK( 15, 10, 0x344 )
SET_BLOCK( 15, 11, 0x345 )
SET_BLOCK( 14, 21, 0x2D7 )
SET_BLOCK( 14, 22, 0x2DF )
SET_BLOCK( 15, 21, 0x206 )
SET_BLOCK( 15, 22, 0x20E )
SET_BLOCK( 16, 21, 0x2E5 )
SET_BLOCK( 16, 22, 0x2E6 )
// after battle message
MESSAGE( 649, 0 )

END_OF_PROGRAM
