// verdanturf friendship rater
#include "scriptlib.m4.h"

MESSAGE( 917, 0 )

IS_EGG( 0 )
CHECK_REGISTER( 0, 0, 2 )
    MESSAGE( 935, 0 )
    JUMP_TO_END

GET_FRIENDSHIP( 0 )
// check if friendship is at least 200
CHECK_REGISTER_G( 0, 0, 2 )
    MESSAGE( 924, 0 )
    JUMP_TO_END
CHECK_REGISTER_G( 0, 49, 2 )
    MESSAGE( 923, 0 )
    JUMP_TO_END
CHECK_REGISTER_G( 0, 99, 2 )
    MESSAGE( 922, 0 )
    JUMP_TO_END
CHECK_REGISTER_G( 0, 149, 2 )
    MESSAGE( 921, 0 )
    JUMP_TO_END
CHECK_REGISTER_G( 0, 199, 2 )
    MESSAGE( 920, 0 )
    JUMP_TO_END
CHECK_REGISTER_G( 0, 254, 2 )
    MESSAGE( 919, 0 )
    JUMP_TO_END
MESSAGE( 918, 0 )
