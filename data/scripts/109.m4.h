// scary pkmn (1)
#include "scriptlib.m4.h"

// quest completed
CHECK_FLAG( 183, 0, 2 )
    MESSAGE( 458, 0 )
    JUMP_TO_END

// quest completed, hand out reward
CHECK_FLAG( 182, 0, 6 )
    MESSAGE( 460, 0 )
    TAKE_ITEM( I_SPARKLING_STONE, 1 )
    MESSAGE( 461, 0 )
    GIVE_ITEM( I_DAWN_STONE, 1 )
    SET_FLAG( 183, 1 )
    JUMP_TO_END

// quest ongoing
SET_FLAG( 179, 1 )
MESSAGE( 459, 0 )
END_OF_PROGRAM
