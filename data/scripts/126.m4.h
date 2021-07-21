// blue crystal cave (54/3_1), colored blocks (blue)
#include "scriptlib.m4.h"

// Check if blue crystal is activated
CHECK_FLAG( 217, 1, 1 )
    JUMP_TO_END

// big crystal
SET_BLOCK( 26, 6, 0x3ff )
// small crystals
SET_BLOCK( 25, 4, 0x38e )
SET_BLOCK( 27, 4, 0x38e )
SET_BLOCK( 24, 5, 0x38e )
SET_BLOCK( 28, 5, 0x38e )
SET_BLOCK( 24, 7, 0x38e )
SET_BLOCK( 28, 7, 0x38e )
SET_BLOCK( 25, 8, 0x38e )
SET_BLOCK( 27, 8, 0x38e )
