// devon dude ranting about getting robbed by Team A
#include "scriptlib.m4.h"

CHECK_FLAG( 157, 0, 1 )
    JUMP_TO_END

GET_MAPOBJECT( 22, 26, 3 )
    COPY_REGISTER( 0, 1 )
    LOCK_R( 1 )
    EXCLAMATION_R( 1 ) // Show exclamation mark
    MOVE_MAPOBJECT_R( 1, LEFT, 0 )
    CHECK_FLAG( 36, 0, 2 )
        MESSAGE( 366, 0 )
        SKIP( 2 )
    MESSAGE( 368, 0 )
    GIVE_ITEM( I_PREMIER_BALL, 3 )
    SET_FLAG( 157, 1 )
    UNLOCK_R( 1 )
END_OF_PROGRAM
