// getting miracle seed
#include "scriptlib.m4.h"

CHECK_FLAG( 59, 1, 4 )
    MESSAGE( 271, 0 )
    GIVE_ITEM( I_MIRACLE_SEED, 1 )
    SET_FLAG( 59, 1 )
    JUMP_TO_END
MESSAGE( 272, 0 )
END_OF_PROGRAM
