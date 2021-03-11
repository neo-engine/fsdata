// activate munna once it is night
#include "scriptlib.m4.h"

GET_CURRENT_TIME
CHECK_REGISTER_N( EVAL_REG, DAYTIME_NIGHT, 2 )
    SET_FLAG( 178, 1 )
    JUMP_TO_END
SET_FLAG( 178, 0 )
END_OF_PROGRAM

