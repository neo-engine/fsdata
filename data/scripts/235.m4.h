// seashore gouse vendor
#include "scriptlib.m4.h"

// got the reward already, normal vendor for soda pop
CHECK_FLAG( 354, 0, 5 )
    MESSAGE( 788, 0 )
    MART_BEGIN( 0, 0 )
    MART_ITEM( I_SODA_POP, 30 )
    SELL_ITEMS
    JUMP_TO_END

CHECK_FLAG( 355, 1, 1 )
    // intro message
    MESSAGE( 789, 0 )

// check if all trainers are defeated
CHECK_TRAINER_FLAG( 87, 0, 6 )
    CHECK_TRAINER_FLAG( 88, 0, 5 )
        CHECK_TRAINER_FLAG( 89, 0, 4 )
            MESSAGE( 791, 0 )
            SET_FLAG( 354, 1 )
            GIVE_ITEM( I_SODA_POP, 6 )
            JUMP_TO_END

// default dialog (shouldn't appear on first meeting)
CHECK_FLAG( 355, 0, 2 )
    MESSAGE( 790, 0 )
    JUMP_TO_END
// else
    SET_FLAG( 355, 1 )


