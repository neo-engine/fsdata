// rival's mom on first enter of player
#include "scriptlib.m4.h"

CHECK_FLAG( 5, 1, 1 ) // Should only activate when the rival has appearance 0
    JUMP_TO_END
CHECK_FLAG( 11, 0, 1 )
    JUMP_TO_END
GET_MAPOBJECT( 18, 26, 3 )
    EXCLAMATION_R( 0 ) // Show exclamation mark
    MOVE_MAPOBJECT_R( 0, DOWN, 1 )
    MOVE_MAPOBJECT_R( 0, LEFT, 5 )
    MOVE_PLAYER( RIGHT, 0 )
    MESSAGE( 59, 0 )
    MOVE_MAPOBJECT_R( 0, RIGHT, 5 )
    MOVE_MAPOBJECT_R( 0, UP, 1 )
    MOVE_MAPOBJECT_R( 0, LEFT, 0 )
    SET_FLAG( 11, 1 )
    MOVE_PLAYER( UP, 0 )
END_OF_PROGRAM
