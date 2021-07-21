// jirachi cave, colored blocks (green)
#include "scriptlib.m4.h"

// Check if blue crystal is activated
CHECK_FLAG( 219, 1, 1 )
    JUMP_TO_END

// big crystal
SET_BLOCK( 21, 23, 0x397 )
// small crystals
SET_BLOCK( 20, 21, 0x38c )
SET_BLOCK( 22, 21, 0x38c )
SET_BLOCK( 19, 22, 0x38c )
SET_BLOCK( 23, 22, 0x38c )
SET_BLOCK( 19, 24, 0x38c )
SET_BLOCK( 23, 24, 0x38c )
SET_BLOCK( 20, 25, 0x38c )
SET_BLOCK( 22, 25, 0x38c )

SET_BLOCK( 18, 18, 0x38c )
SET_BLOCK( 17, 19, 0x38c )
SET_BLOCK( 21, 18, 0x38c )

SET_BLOCK( 19, 15, 0x38c )
SET_BLOCK( 23, 15, 0x38c )
SET_BLOCK( 14, 20, 0x38c )
SET_BLOCK( 14, 25, 0x38c )

SET_BLOCK(  6, 16, 0x38c )

END_OF_PROGRAM
