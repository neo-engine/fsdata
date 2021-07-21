// jirachi cave, colored blocks (blue)
#include "scriptlib.m4.h"

// Check if blue crystal is activated
CHECK_FLAG( 217, 1, 1 )
    JUMP_TO_END

// big crystal
SET_BLOCK( 21, 10, 0x3ff )
// small crystals
SET_BLOCK( 20,  8, 0x38e )
SET_BLOCK( 22,  8, 0x38e )
SET_BLOCK( 19,  9, 0x38e )
SET_BLOCK( 23,  9, 0x38e )
SET_BLOCK( 19, 11, 0x38e )
SET_BLOCK( 23, 11, 0x38e )
SET_BLOCK( 20, 12, 0x38e )
SET_BLOCK( 22, 12, 0x38e )
SET_BLOCK( 17, 13, 0x38e )
SET_BLOCK( 18, 14, 0x38e )
SET_BLOCK( 21, 14, 0x38e )
SET_BLOCK( 19, 17, 0x38e )
SET_BLOCK( 23, 17, 0x38e )
SET_BLOCK( 14, 12, 0x38e )
SET_BLOCK( 14,  7, 0x38e )

END_OF_PROGRAM
