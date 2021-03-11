// hm flash in granite cave
#include "scriptlib.m4.h"

CHECK_FLAG( 154, 1, 6 )
    CHECK_FLAG( 166, 1, 2 )
        MESSAGE( 348, 0 )
        SKIP( 1 )
        MESSAGE( 442, 0 )
    GIVE_ITEM( I_TM95, 1 )
    SET_FLAG( 154, 1 )
MESSAGE( 349, 0 )
END_OF_PROGRAM
