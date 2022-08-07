// shoal cave, shell 1
#include "scriptlib.m4.h"

// shell 1
CHECK_FLAG( 227, 1, 4 )
    // not collected yet, collect salt
    GIVE_ITEM( I_SHOAL_SHELL, 1 )
    SET_BLOCK( 6, 9, 0x35B )
    SET_FLAG( 227, 1 )
    JUMP_TO_END

MESSAGE( 568, 0 )
