// shoal cave, jiisan
#include "scriptlib.m4.h"

// general message
MESSAGE( 569, 0 )

// check ingredients
CHECK_ITEM( I_SHOAL_SALT, 4, 13 )
    // player has item
    CHECK_ITEM( I_SHOAL_SHELL, 4, 11 )
        // player has item
        MESSAGE( 571, 0 )
        YES_NO_MESSAGE_N( 572, 0, 6 )
            // yes
            TAKE_ITEM( I_SHOAL_SALT, 4 )
            TAKE_ITEM( I_SHOAL_SHELL, 4 )
            MESSAGE( 573, 0 )
            GIVE_ITEM( I_SHELL_BELL, 1 )
            MESSAGE( 574, 0 )
            JUMP_TO_END
            // no
            MESSAGE( 575, 0 )
            JUMP_TO_END
// player has no item
MESSAGE( 570, 0 )
