// Champ (Wallace) on room enter
#include "scriptlib.m4.h"

#define V_HALL_OF_FAME_VICTORIES 37
SET_TRAINER_FLAG( 79, 0 )
SET_TRAINER_FLAG( 72, 0 )

MOVE_PLAYER( UP, 5 )

CHECK_VAR( V_HALL_OF_FAME_VICTORIES, 0, 3 )
// player is champ
    MESSAGE( 659, 0 )
    BATTLE_TRAINER( 79, DOUBLE )
    SKIP( 2 )
// player is not yet champ
    MESSAGE( 658, 0 )
    BATTLE_TRAINER( 72, SINGLE )

CHECK_REGISTER( 0, 1, 2 )
    FAINT_PLAYER
    JUMP_TO_END

// increase number of times player defeated champion
GET_VAR( V_HALL_OF_FAME_VICTORIES, 5 )
ADD_CONSTANT_TO_REGISTER( 5, 1 )
SET_VAR_REG( V_HALL_OF_FAME_VICTORIES, 5 )

// activate door
SET_BLOCK( 15, 10, 0x346 )
SET_BLOCK( 15, 11, 0x347 )

// after battle message
MESSAGE( 660, 0 )

MOVE_PLAYER( RIGHT, 1 )
MOVE_PLAYER( UP, 3 )
MOVE_PLAYER( LEFT, 1 )
MOVE_PLAYER( UP, 2 )

END_OF_PROGRAM
