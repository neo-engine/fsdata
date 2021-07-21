// crystal cavern hiker at entry
#include "scriptlib.m4.h"

SET_REGISTER( 2, 0 )

// Check how many crystals got activated
CHECK_FLAG( 216, 0, 1 )
    ADD_CONSTANT_TO_REGISTER( 2, 1 )
CHECK_FLAG( 217, 0, 1 )
    ADD_CONSTANT_TO_REGISTER( 2, 1 )
CHECK_FLAG( 218, 0, 1 )
    ADD_CONSTANT_TO_REGISTER( 2, 1 )
CHECK_FLAG( 219, 0, 1 )
    ADD_CONSTANT_TO_REGISTER( 2, 1 )

CHECK_REGISTER_N( 2, 0, 2 )
    MESSAGE( 562, 0 )
    JUMP_TO_END
MESSAGE( 563, 0 )
