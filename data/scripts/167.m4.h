// shoal cave, shell 3
#include "scriptlib.m4.h"

// shell 3
CHECK_FLAG( 229, 1, 4 )
    // not collected yet, collect shell
    GIVE_ITEM( I_SHOAL_SHELL, 1 )
    SET_BLOCK( 9, 10, 0x35B )
    SET_FLAG( 229, 1 )
    JUMP_TO_END

MESSAGE( 568, 0 )
