// little girl at littleroot's entry when prof birch is in trouble
#include "scriptlib.m4.h"

CHECK_FLAG( 16, 0, 1 ) // Should only activate if player has not talked to little girl yet
    JUMP_TO_END
GET_MAPOBJECT( 26, 19, 3 )
    LOCK_R( 0 )
    EXCLAMATION_R( 0 ) // Show exclamation mark
    MOVE_MAPOBJECT_R( 0, RIGHT, 0 )
    MOVE_PLAYER( LEFT, 0 )
    MESSAGE( 75, 0 )
    SET_FLAG( 16, 1 )
    UNLOCK_R( 0 )
    MOVE_PLAYER( UP, 3 )
    MOVE_MAPOBJECT_R( 0, UP, 0 )
END_OF_PROGRAM
