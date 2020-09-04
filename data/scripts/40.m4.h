// getting a berry in ppfs
#include "scriptlib.m4.h"

CHECK_FLAG( 47, 1, 5 )
    MESSAGE( 210, 0 )
    GIVE_ITEM( I_OCCA_BERRY, 1 )
    GIVE_ITEM( I_PASSHO_BERRY, 1 )
    GIVE_ITEM( I_RINDO_BERRY, 1 )
    SET_FLAG( 47, 1 )
MESSAGE( 211, 0 )
END_OF_PROGRAM
