// shoal cave, salt 3
#include "scriptlib.m4.h"

// salt 1
CHECK_FLAG( 225, 1, 4 )
    // not collected yet, collect salt
    GIVE_ITEM( I_SHOAL_SALT, 1 )
    SET_BLOCK( 11, 18, 0x35A )
    SET_FLAG( 225, 1 )
    JUMP_TO_END

MESSAGE( 567, 0 )
