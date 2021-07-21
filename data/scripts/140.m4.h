// green crystals in crystal cavern
#include "scriptlib.m4.h"

// Check if green crystal is activated
CHECK_FLAG( 219, 1, 1 )
    JUMP_TO_END

// small crystals
SET_BLOCK( 23, 22, 0x38c )
SET_BLOCK( 8, 21, 0x38c )
SET_BLOCK( 9, 18, 0x38c )
SET_BLOCK( 8, 11, 0x38c )
SET_BLOCK( 10, 13, 0x38c )
