// little girl at littleroot's entry when prof birch is in trouble (when talked to)
#include "scriptlib.m4.h"

CHECK_FLAG( 16, 0, 1 ) // Should only activate if player has not talked to little girl yet
    JUMP_TO_END
GET_MAPOBJECT( 26, 19, 3 )
    EXCLAMATION_R( 0 ) // Show exclamation mark
    LOCK_R( 0 )
    MESSAGE( 75, 0 )
    SET_FLAG( 16, 1 )
    MOVE_PLAYER( RIGHT, 1 )
    MOVE_MAPOBJECT_R( 0, UP, 0 )
    MOVE_PLAYER( UP, 4 )
    UNLOCK_R( 0 )
END_OF_PROGRAM
