// PKMN league badge check (right)
#include "scriptlib.m4.h"

// Check that all 8 badges are obtained

MESSAGE( 670, 0 )
BADGE_COUNT( 0 )
CHECK_REGISTER( EVAL_REG, 8, 2 )
    MESSAGE( 672, 0 )
    JUMP_TO_END

// Check successful
MESSAGE( 671, 0 )

GET_MAPOBJECT( 17, 23, 3 )
COPY_REGISTER( 0, 2 )
MOVE_MAPOBJECT_R( 2, UP, 1 )
MOVE_MAPOBJECT_R( 2, LEFT, 1 )
MOVE_MAPOBJECT_R( 2, RIGHT, 0 )

MOVE_PLAYER( UP, 3 )

END_OF_PROGRAM
