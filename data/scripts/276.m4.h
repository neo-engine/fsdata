// black glasses dude
#include "scriptlib.m4.h"

// check if player collected black glasses
CHECK_FLAG( 103, 1, 2 )
    MESSAGE( 1075, 0 )
    JUMP_TO_END

CHECK_FLAG( 389, 1, 4 )
    MESSAGE( 1076, 0 )
    MESSAGE( 1077, 0 )
    SET_FLAG( 389, 1 )
    JUMP_TO_END

MESSAGE( 1078, 0 )
END_OF_PROGRAM
