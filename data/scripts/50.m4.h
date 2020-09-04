// Player's mom at game start (player has appearance 0)
#include "scriptlib.m4.h"

CHECK_FLAG( 5, 1, 1 ) // Should only activate when the rival has appearance 1
    JUMP_TO_END
MOVE_PLAYER( RIGHT, 0 )
SPAWN_MAPOBJECT( 227, 21, 26 )
    MOVE_MAPOBJECT_R( 0, DOWN, 2 )
    MOVE_MAPOBJECT_R( 0, LEFT, 0 )
    MESSAGE( 12, 0 )
    ATTACH_PLAYER
    MOVE_MAPOBJECT_R( 0, UP, 2 )
    REMOVE_PLAYER
DESTROY_MAPOBJECT_R( 0 )
MOVE_PLAYER( UP, 1 )
// Inside part
SPAWN_MAPOBJECT( 227, 19, 27 )
    MOVE_MAPOBJECT_R( 0, UP, 0 )
    MESSAGE( 16, 0 )
    MOVE_MAPOBJECT_R( 0, LEFT, 0 )
    MOVE_PLAYER( RIGHT, 0 )
    MESSAGE( 50, 0 )
    MOVE_MAPOBJECT_R( 0, UP, 1 )
    MOVE_MAPOBJECT_R( 0, LEFT, 1 )
    MOVE_PLAYER( UP, 0 )
    ATTACH_PLAYER
    MOVE_MAPOBJECT_R( 0, UP, 4 )
    REMOVE_PLAYER
    MOVE_MAPOBJECT_R( 0, RIGHT, 1 )
    MOVE_MAPOBJECT_R( 0, LEFT, 0 )
    MOVE_PLAYER( UP, 2 )
    GET_MAPOBJECT( 19, 22, 3 )
    DESTROY_MAPOBJECT_R( 0 )
SET_FLAG( 8, 1 )
END_OF_PROGRAM

