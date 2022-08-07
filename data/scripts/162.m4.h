// shoal cave, salt 2
#include "scriptlib.m4.h"

// salt 2
CHECK_FLAG( 224, 1, 4 )
    // not collected yet, collect salt
    GIVE_ITEM( I_SHOAL_SALT, 1 )
    SET_BLOCK( 30, 9, 0x35A )
    SET_FLAG( 224, 1 )
    JUMP_TO_END

MESSAGE( 567, 0 )
