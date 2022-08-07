// shoal cave, shell 4
#include "scriptlib.m4.h"

// shell 4
CHECK_FLAG( 230, 1, 4 )
    // not collected yet, collect shell
    GIVE_ITEM( I_SHOAL_SHELL, 1 )
    SET_BLOCK( 9, 20, 0x35B )
    SET_FLAG( 230, 1 )
    JUMP_TO_END

MESSAGE( 568, 0 )
