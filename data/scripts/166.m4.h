// shoal cave, shell 2
#include "scriptlib.m4.h"

// shell 2
CHECK_FLAG( 228, 1, 4 )
    // not collected yet, collect salt
    GIVE_ITEM( I_SHOAL_SHELL, 1 )
    SET_BLOCK( 16, 13, 0x35B )
    SET_FLAG( 228, 1 )
    JUMP_TO_END

MESSAGE( 568, 0 )
