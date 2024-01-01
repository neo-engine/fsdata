// gift eevee in blossand town
#include "scriptlib.m4.h"


CHECK_FLAG( 387, 1, 13 )
    MESSAGE( 1064, 0 )
    YES_NO_MESSAGE( 1065, 0, 2 )
        MESSAGE( 1067, 0 )
        JUMP_TO_END

    GIFT_PKMN( PKMN_EEVEE, 5 )

    CHECK_REGISTER( 0, 1, 2 )
        MESSAGE( 1067, 0 )
        JUMP_TO_END

    SET_FLAG( 387, 1 )
    MESSAGE( 1066, 0 )
    REDRAW_OBJECTS
    JUMP_TO_END

// "how is eevee doing"
MESSAGE( 1063, 0 )
END_OF_PROGRAM
