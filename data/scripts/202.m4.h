// PKMN league badge check (left)
#include "scriptlib.m4.h"

// Check that all 8 badges are obtained

MESSAGE( 670, 0 )
BADGE_COUNT( 0 )
CHECK_REGISTER( EVAL_REG, 8, 2 )
    MESSAGE( 672, 0 )
    JUMP_TO_END

// Check successful
MESSAGE( 671, 0 )

GET_MAPOBJECT( 16, 23, 3 )
COPY_REGISTER( 0, 2 )
MOVE_MAPOBJECT_R( 2, UP, 1 )
MOVE_MAPOBJECT_R( 2, RIGHT, 1 )
MOVE_MAPOBJECT_R( 2, LEFT, 0 )

CLEAR_FLAG( 300 )
CLEAR_FLAG( 301 )
CLEAR_FLAG( 302 )
CLEAR_FLAG( 303 )

MOVE_PLAYER( UP, 3 )

END_OF_PROGRAM