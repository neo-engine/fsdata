// green crystal cave (54/3_1), colored blocks (green)
#include "scriptlib.m4.h"

// Check if green crystal is activated
CHECK_FLAG( 219, 1, 1 )
    JUMP_TO_END

// big crystal
SET_BLOCK( 26, 26, 0x397 )
// small crystals
SET_BLOCK( 25, 24, 0x38c )
SET_BLOCK( 27, 24, 0x38c )
SET_BLOCK( 24, 25, 0x38c )
SET_BLOCK( 28, 25, 0x38c )
SET_BLOCK( 24, 27, 0x38c )
SET_BLOCK( 28, 27, 0x38c )
SET_BLOCK( 25, 28, 0x38c )
SET_BLOCK( 27, 28, 0x38c )
