// rival's mom
#include "scriptlib.m4.h"

CHECK_FLAG( 3, 0, 2 )
    MESSAGE( 100, 0 )
    JUMP_TO_END
CHECK_FLAG( 17, 0, 2 )
    MESSAGE( 88, 0 )
    JUMP_TO_END
CHECK_FLAG( 12, 1, 2 )
    // Player has not met rival yet
    MESSAGE( 60, 0 )
    JUMP_TO_END
MESSAGE( 70, 0 )
END_OF_PROGRAM
