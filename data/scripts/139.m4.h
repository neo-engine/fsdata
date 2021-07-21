// yellow crystals in crystal cavern
#include "scriptlib.m4.h"

// Check if yellow crystal is activated
CHECK_FLAG( 218, 1, 1 )
    JUMP_TO_END

// small crystals
SET_BLOCK( 21, 15, 0x3d6 )
SET_BLOCK( 10, 20, 0x3d6 )
SET_BLOCK( 11, 16, 0x3d6 )
SET_BLOCK(  8, 17, 0x3d6 )
SET_BLOCK(  7, 13, 0x3d6 )
