// finding munna
#include "scriptlib.m4.h"


// quest not unlocked
CHECK_FLAG( 150, 1, 2 )
    MESSAGE( 398, 0 )
    JUMP_TO_END

// quest completed
CHECK_FLAG( 177, 0, 2 )
    MESSAGE( 451, 0 )
    JUMP_TO_END

// quest completed, hand out reward
CHECK_FLAG( 176, 0, 4 )
    MESSAGE( 452, 0 )
    GIVE_ITEM( I_MOON_STONE, 1 )
    SET_FLAG( 177, 1 )
    JUMP_TO_END

// quest ongoing
SET_FLAG( 175, 1 )
MESSAGE( 453, 0 )
END_OF_PROGRAM
