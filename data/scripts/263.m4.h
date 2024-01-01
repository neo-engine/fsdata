// Getting HM07 rock smash
#include "scriptlib.m4.h"

CHECK_FLAG( 378, 1, 5 )
    MESSAGE( 957 , 0 )
    GIVE_ITEM( I_HM07, 1 )
    SET_FLAG( 378, 1 )
    MESSAGE( 958 , 0 )
    JUMP_TO_END
MESSAGE( 959, 0 )
END_OF_PROGRAM
