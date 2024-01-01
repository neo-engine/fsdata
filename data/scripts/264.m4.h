// mauville city rydel (bike shop owner)
#include "scriptlib.m4.h"

CHECK_FLAG( 380, 1, 2 )
    MESSAGE( 960, 0 )
    SET_FLAG( 380, 1 )

CHECK_FLAG( 379, 1, 17 )
    MESSAGE( 961, 0 )
    YES_NO_MESSAGE( 980, 0, 2 )
        // no need for bike
        MESSAGE( 962, 0 )
        JUMP_TO_END
    // else
    MESSAGE( 963, 0 )

    CBOX_BEGIN( 979, 0 )
    CBOX_ITEM( 964, 0 ) // mach bike
    CBOX_ITEM( 965, 1 ) // acro bike
    CBOX_RUN

    CHECK_REGISTER( 0, 1, 2 )
        GIVE_ITEM( I_MACH_BIKE, 1 )
        SKIP( 1 )
    // else
        GIVE_ITEM( I_ACRO_BIKE, 1 )

    MESSAGE( 966, 0 )
    SET_FLAG( 379, 1 )
    JUMP_TO_END

// ask if player wants to swap bikes
YES_NO_MESSAGE( 967, 0, 2 )
    MESSAGE( 969, 0 )
    JUMP_TO_END

MESSAGE( 968, 0 )
// check which bike the player owns
CHECK_ITEM( I_ACRO_BIKE, 1, 3 )
    TAKE_ITEM( I_ACRO_BIKE, 1 )
    GIVE_ITEM( I_MACH_BIKE, 1 )
    SKIP( 2 )
// else
    TAKE_ITEM( I_MACH_BIKE, 1 )
    GIVE_ITEM( I_ACRO_BIKE, 1 )

MESSAGE( 966, 0 )
END_OF_PROGRAM
