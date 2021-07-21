// yellow crystal cave (54/3_1), colored blocks (yellow)
#include "scriptlib.m4.h"

// Check if yellow crystal is activated
CHECK_FLAG( 218, 1, 1 )
    JUMP_TO_END

// big crystal
SET_BLOCK(  5, 26, 0x2b9 )
// small crystals
SET_BLOCK(  4, 24, 0x3d6 )
SET_BLOCK(  6, 24, 0x3d6 )
SET_BLOCK(  3, 25, 0x3d6 )
SET_BLOCK(  7, 25, 0x3d6 )
SET_BLOCK(  3, 27, 0x3d6 )
SET_BLOCK(  7, 27, 0x3d6 )
SET_BLOCK(  4, 28, 0x3d6 )
SET_BLOCK(  6, 28, 0x3d6 )
