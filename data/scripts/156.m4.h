// shoal cave 16/3_1, salts/shells
#include "scriptlib.m4.h"

// salt 1
CHECK_FLAG( 223, 1, 1 )
    SET_BLOCK( 14, 26, 0x358 )
// salt 2
CHECK_FLAG( 224, 1, 1 )
    SET_BLOCK( 30, 9, 0x358 )

// shell 1
CHECK_FLAG( 227, 1, 1 )
    SET_BLOCK( 6, 9, 0x359 )
// shell 2
CHECK_FLAG( 228, 1, 1 )
    SET_BLOCK( 16, 13, 0x359 )
