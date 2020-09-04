// Dude on route 104 giving player TM 50 bullet seed
#include "scriptlib.m4.h"

CHECK_FLAG( 40, 1, 4 )
    MESSAGE( 193, 0 )
    GIVE_ITEM( I_TM50, 1 )
    SET_FLAG( 40, 1 )
    JUMP_TO_END
MESSAGE( 194, 0 )
END_OF_PROGRAM
