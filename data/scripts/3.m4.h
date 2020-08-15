// Player's mom at game start
#include "scriptlib.m4.h"

CHECK_FLAG( 5, 0, 1 ) // Should only activate when the rival has appearance 0
    JUMP_TO_END
SPAWN_MAPOBJECT( 20, 30, 26 ) // TODO: correct pic num
    MOVE_MAPOBJECT_R( 0, DOWN, 2 )
    MOVE_MAPOBJECT_R( 0, LEFT, 0 )
    MESSAGE( 12, 0 )
    ATTACH_PLAYER
    MOVE_MAPOBJECT_R( 0, UP, 2 )
    REMOVE_PLAYER
DESTROY_MAPOBJECT_R( 0 )
MOVE_PLAYER( UP, 1 )
SET_FLAG( 8, 1 )
END_OF_PROGRAM

