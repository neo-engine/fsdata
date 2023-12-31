// mauville wally
#include "scriptlib.m4.h"

GET_CURRENT_MAPOBJECT
COPY_REGISTER( 0, 1 )
LOCK_R( 1 )

MOVE_MAPOBJECT_R( 1, RIGHT, 0 )
MESSAGE( 936, 0 )
MESSAGE( 937, 0 )
MESSAGE( 938, 0 )
MOVE_MAPOBJECT_R( 1, DOWN, 0 )
EXCLAMATION_R( 0 )
MESSAGE( 939, 0 )

// battle wally
CHECK_FLAG( 27, 1, 2 )
    // ralts is not shiny
    BATTLE_TRAINER( 97, SINGLE )
    SKIP( 1 )
// else
    // ralts is shiny
    BATTLE_TRAINER( 98, SINGLE )

CHECK_REGISTER( 0, 1, 2 )
FAINT_PLAYER
JUMP_TO_END

SET_FLAG( 368, 1 )
MESSAGE( 940, 0 )

HIDE_PKMN
MOVE_PLAYER( RIGHT, 1 )
MOVE_PLAYER( LEFT, 0 )
MOVE_MAPOBJECT_R( 1, DOWN, 1 )

GET_MAPOBJECT( 9, 8, 3 )
LOCK_R( 0 )
MOVE_MAPOBJECT_R( 0, LEFT, 1 )
MOVE_MAPOBJECT_R( 0, DOWN, 0 )

MESSAGE( 941, 0 )
MOVE_MAPOBJECT_R( 1, DOWN, 3 )
MOVE_MAPOBJECT_R( 1, LEFT, 8 )
UNLOCK_R( 1 )
DESTROY_MAPOBJECT_R( 1 )

MOVE_MAPOBJECT_R( 0, DOWN, 1 )
MOVE_MAPOBJECT_R( 0, RIGHT, 0 )
MESSAGE( 942, 0 )

MOVE_MAPOBJECT_R( 0, DOWN, 3 )
MOVE_MAPOBJECT_R( 0, LEFT, 8 )

UNLOCK_R( 0 )
DESTROY_MAPOBJECT_R( 0 )

