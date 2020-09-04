// nerd stopping player from leaving oldale town
#include "scriptlib.m4.h"

CHECK_FLAG( 3, 0, 1 ) // don't activate if player obtained the pokedex
    JUMP_TO_END
GET_MAPOBJECT( 17, 21, 3 )
EXCLAMATION_R( 0 )
MESSAGE( 91, 0 )
MOVE_MAPOBJECT_R( 0, UP, 1 )
MOVE_PLAYER( RIGHT, 0 )
ATTACH_PLAYER
MOVE_MAPOBJECT_R( 0, RIGHT, 1 )
REMOVE_PLAYER
MOVE_MAPOBJECT_R( 0, LEFT, 0 )
MESSAGE( 92, 0 )
MOVE_MAPOBJECT_R( 0, DOWN, 1 )
MOVE_MAPOBJECT_R( 0, LEFT, 1 )
END_OF_PROGRAM
