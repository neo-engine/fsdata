// ocean museum entry fee (right)
#include "scriptlib.m4.h"

CHECK_FLAG( 193, 1, 1 )
    JUMP_TO_END
MOVE_PLAYER( RIGHT, 0 )
MESSAGE( 499, 0 )
YES_NO_MESSAGE( 496, 128, 2 ) // show money
    MOVE_PLAYER( DOWN, 1 )
    JUMP_TO_END
// try to pay $50
CHECK_MONEY( 50, 3 )
    MESSAGE( 497, 0 )
    MOVE_PLAYER( DOWN, 1 )
    JUMP_TO_END
PAY_MONEY( 50 )
MESSAGE( 498, 0 )
SET_FLAG( 193, 0 )
END_OF_PROGRAM
