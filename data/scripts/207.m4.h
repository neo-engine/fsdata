// E4 Sydney level script
#include "scriptlib.m4.h"

CHECK_TRAINER_FLAG( 77, 0, 9 )
    SET_BLOCK( 14, 21, 0x2D7 )
    SET_BLOCK( 14, 22, 0x2DF )
    SET_BLOCK( 15, 21, 0x206 )
    SET_BLOCK( 15, 22, 0x20E )
    SET_BLOCK( 16, 21, 0x2E5 )

    SET_BLOCK( 16, 22, 0x2E6 )
    SET_BLOCK( 15, 10, 0x344 )
    SET_BLOCK( 15, 11, 0x345 )
    JUMP_TO_END

CHECK_TRAINER_FLAG( 70, 0, 9 )
    SET_BLOCK( 14, 21, 0x2D7 )
    SET_BLOCK( 14, 22, 0x2DF )
    SET_BLOCK( 15, 21, 0x206 )
    SET_BLOCK( 15, 22, 0x20E )
    SET_BLOCK( 16, 21, 0x2E5 )

    SET_BLOCK( 16, 22, 0x2E6 )
    SET_BLOCK( 15, 10, 0x344 )
    SET_BLOCK( 15, 11, 0x345 )
    JUMP_TO_END

SET_BLOCK( 14, 21, 0x2D7 )
SET_BLOCK( 14, 22, 0x2DF )
SET_BLOCK( 15, 21, 0x206 )
SET_BLOCK( 15, 22, 0x20E )
SET_BLOCK( 16, 21, 0x2E5 )
SET_BLOCK( 16, 22, 0x2E6 )
END_OF_PROGRAM
