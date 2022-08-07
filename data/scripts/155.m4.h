// shoal cave reset script
#include "scriptlib.m4.h"

// Check if at least 6 playtime hours have passed since the last reset
GET_PLAYTIME_HOURS
COPY_REGISTER( 0, 1 )
GET_VAR( 36, 2 )
SUBTRACT_REGISTER_FROM_REGISTER( 1, 2 )
CHECK_REGISTER_G( 1, 6, 1 )
    JUMP_TO_END

// reset "salt/shell collected" flags
CLEAR_FLAG( 223 )
CLEAR_FLAG( 224 )
CLEAR_FLAG( 225 )
CLEAR_FLAG( 226 )

CLEAR_FLAG( 227 )
CLEAR_FLAG( 228 )
CLEAR_FLAG( 229 )
CLEAR_FLAG( 230 )

// set new update time
GET_PLAYTIME_HOURS
SET_VAR_REG( 36, 0 )

