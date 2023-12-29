// slateport battle tent lobby tm torment
#include "scriptlib.m4.h"

// tm collected
CHECK_FLAG( 366, 1, 3 )
    MESSAGE( 855, 0 )
    GIVE_ITEM( I_TM41, 1 )
    SET_FLAG( 366, 1 )
MESSAGE( 856, 0 )

END_OF_PROGRAM
