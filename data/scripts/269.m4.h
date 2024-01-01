// slateport city dock
#include "scriptlib.m4.h"


// initial message
CHECK_FLAG( 382, 1, 2 )
    MESSAGE( 995, 0 )
    SET_FLAG( 382, 1 )

CHECK_ROUTE( 1, 1 )
    SKIP( 8 )
CHECK_FLAG( 384, 1, 7 ) // goods already delivered
// { on route 1
    // check if player got sent to capt. stern already
    CHECK_FLAG( 356, 1, 4 )
        MESSAGE( 996, 0 )
        SET_FLAG( 383, 1 )
        SET_FLAG( 356, 1 )
        JUMP_TO_END
    // else
        MESSAGE( 997, 0 )
    JUMP_TO_END
// }


// check if player is champ
CHECK_FLAG( 385, 0, 2 )
    MESSAGE( 1000, 0 )
    JUMP_TO_END

// check if player won badge 7
CHECK_FLAG( 381, 0, 2 )
    MESSAGE( 999, 0 )
    JUMP_TO_END

MESSAGE( 998, 0 )

