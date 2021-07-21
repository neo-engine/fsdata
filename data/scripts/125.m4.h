// red crystal cave (54/3_1), colored blocks (red)
#include "scriptlib.m4.h"

// Check if red crystal is activated
CHECK_FLAG( 216, 1, 1 )
    JUMP_TO_END

// big crystal
SET_BLOCK(  5, 6, 0x3f7 )
// small crystals
SET_BLOCK(  4, 4, 0x38f )
SET_BLOCK(  6, 4, 0x38f )
SET_BLOCK(  3, 5, 0x38f )
SET_BLOCK(  7, 5, 0x38f )
SET_BLOCK(  3, 7, 0x38f )
SET_BLOCK(  7, 7, 0x38f )
SET_BLOCK(  4, 8, 0x38f )
SET_BLOCK(  6, 8, 0x38f )
