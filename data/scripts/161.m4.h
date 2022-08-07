// shoal cave, salt 1
#include "scriptlib.m4.h"

// salt 1
CHECK_FLAG( 223, 1, 4 )
    // not collected yet, collect salt
    GIVE_ITEM( I_SHOAL_SALT, 1 )
    SET_BLOCK( 14, 26, 0x35A )
    SET_FLAG( 223, 1 )
    JUMP_TO_END

MESSAGE( 567, 0 )
