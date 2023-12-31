// obtain fishing rod in dewford
// gives player one of (old rod, good rod, super rod); the first one the player does not
// already own
#include "scriptlib.m4.h"

CHECK_FLAG( 367, 0, 2 ) // rod given
    MESSAGE( 906, 0 )
    JUMP_TO_END
// Ask if the player wants a fishing rod

YES_NO_MESSAGE( 908, 0, 2 )
    MESSAGE( 907, 0 )
    JUMP_TO_END

MESSAGE( 904, 0 )
CHECK_ITEM( I_OLD_ROD, 1, 6 )
    CHECK_ITEM( I_GOOD_ROD, 1, 2 )
        GIVE_ITEM( I_SUPER_ROD, 1 )
        SKIP( 3 )
    GIVE_ITEM( I_GOOD_ROD, 1 )
    SKIP( 1 )
GIVE_ITEM( I_OLD_ROD, 1 )
MESSAGE( 905, 0 )

SET_FLAG( 367, 1 )

END_OF_PROGRAM
