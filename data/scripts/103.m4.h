// rescue wailmer quest lady
#include "scriptlib.m4.h"

// quest non unlocked
CHECK_FLAG( 59, 1, 2 )
    MESSAGE( 227, 0 )
    JUMP_TO_END

// quest completed
CHECK_FLAG( 174, 0, 2 )
    MESSAGE( 446, 0 )
    JUMP_TO_END

// quest completed, hand out reward
CHECK_FLAG( 173, 0, 4 )
    MESSAGE( 445, 0 )
    GIVE_ITEM( I_MYSTIC_WATER, 1 )
    SET_FLAG( 174, 1 )
    JUMP_TO_END

// quest ongoing
MESSAGE( 443, 0 )
END_OF_PROGRAM
