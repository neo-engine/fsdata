// peeko dude before rusturf tunnel
#include "scriptlib.m4.h"

GET_MAPOBJECT( 14, 25, 3 )
    COPY_REGISTER( 0, 1 )
    MOVE_MAPOBJECT_R( 1, RIGHT, 0 )
    MOVE_PLAYER( LEFT, 0 )
    LOCK_R( 1 )
    MESSAGE( 268, 0 )
    UNLOCK_R( 1 )
    SET_FLAG( 158, 1 )
END_OF_PROGRAM
