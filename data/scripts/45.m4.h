// Getting HM01 cut
#include "scriptlib.m4.h"

CHECK_FLAG( 54, 1, 3 )
    MESSAGE( 240, 0 )
    GIVE_ITEM( I_HM01, 1 )
    SET_FLAG( 54, 1 )
MESSAGE( 241, 0 )
END_OF_PROGRAM
