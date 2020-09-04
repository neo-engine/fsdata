// getting the wailmer pail
#include "scriptlib.m4.h"

CHECK_FLAG( 45, 1, 3 )
    MESSAGE( 203, 0 )
    GIVE_ITEM( I_WAILMER_PAIL, 1 )
    SET_FLAG( 45, 1 )
MESSAGE( 204, 0 )
END_OF_PROGRAM
