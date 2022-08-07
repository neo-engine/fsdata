// shoal cave, salt 4
#include "scriptlib.m4.h"

// salt 4
CHECK_FLAG( 226, 1, 4 )
    // not collected yet, collect salt
    GIVE_ITEM( I_SHOAL_SALT, 1 )
    SET_BLOCK( 18, 6, 0x35A )
    SET_FLAG( 226, 1 )
    JUMP_TO_END

MESSAGE( 567, 0 )
