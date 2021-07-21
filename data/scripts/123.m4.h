// jirachi cave, colored blocks (yellow)
#include "scriptlib.m4.h"

// Check if blue crystal is activated
CHECK_FLAG( 218, 1, 1 )
    JUMP_TO_END

// big crystal
SET_BLOCK( 9, 23, 0x2b9 )
// small crystals
SET_BLOCK(  8, 21, 0x3d6 )
SET_BLOCK( 10, 21, 0x3d6 )
SET_BLOCK(  7, 22, 0x3d6 )
SET_BLOCK( 11, 22, 0x3d6 )
SET_BLOCK(  7, 24, 0x3d6 )
SET_BLOCK( 11, 24, 0x3d6 )
SET_BLOCK(  8, 25, 0x3d6 )
SET_BLOCK( 10, 25, 0x3d6 )

SET_BLOCK(  9, 18, 0x3d6 )
SET_BLOCK(  7, 15, 0x3d6 )
SET_BLOCK( 11, 15, 0x3d6 )
SET_BLOCK( 12, 18, 0x3d6 )
SET_BLOCK( 13, 19, 0x3d6 )
SET_BLOCK( 16, 20, 0x3d6 )
SET_BLOCK( 16, 25, 0x3d6 )

SET_BLOCK( 15,  6, 0x3d6 )

END_OF_PROGRAM
