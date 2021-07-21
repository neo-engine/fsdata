// jirachi cave, colored blocks (red)
#include "scriptlib.m4.h"

// Check if red crystal is activated
CHECK_FLAG( 216, 1, 1 )
    JUMP_TO_END

// big crystal
SET_BLOCK(  9, 10, 0x3f7 )
// small crystals
SET_BLOCK(  8,  8, 0x38f )
SET_BLOCK( 10,  8, 0x38f )
SET_BLOCK(  7,  9, 0x38f )
SET_BLOCK( 11,  9, 0x38f )
SET_BLOCK(  7, 11, 0x38f )
SET_BLOCK( 11, 11, 0x38f )
SET_BLOCK(  8, 12, 0x38f )
SET_BLOCK( 10, 12, 0x38f )
SET_BLOCK( 13, 13, 0x38f )
SET_BLOCK( 12, 14, 0x38f )
SET_BLOCK(  9, 14, 0x38f )
SET_BLOCK(  7, 17, 0x38f )
SET_BLOCK( 11, 17, 0x38f )
SET_BLOCK( 16, 12, 0x38f )
SET_BLOCK( 16,  7, 0x38f )

SET_BLOCK( 24, 16, 0x38f )

END_OF_PROGRAM
