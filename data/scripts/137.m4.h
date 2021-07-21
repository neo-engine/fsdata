// red crystals in crystal cavern
#include "scriptlib.m4.h"

// Check if red crystal is activated
CHECK_FLAG( 216, 1, 1 )
    JUMP_TO_END

// small crystals
SET_BLOCK( 25, 20, 0x38f )
SET_BLOCK( 22, 22, 0x38f )
SET_BLOCK( 19, 14, 0x38f )
SET_BLOCK( 15, 23, 0x38f )
SET_BLOCK( 10, 19, 0x38f )
SET_BLOCK( 7, 23, 0x38f )
SET_BLOCK( 7, 15, 0x38f )
SET_BLOCK( 11, 14, 0x38f )
