// blue crystals in crystal cavern
#include "scriptlib.m4.h"

// Check if blue crystal is activated
CHECK_FLAG( 217, 1, 1 )
    JUMP_TO_END

// small crystals
SET_BLOCK( 26, 17, 0x38e )
SET_BLOCK( 21, 21, 0x38e )
SET_BLOCK( 10, 22, 0x38e )
SET_BLOCK(  7, 19, 0x38e )
SET_BLOCK(  8, 13, 0x38e )
