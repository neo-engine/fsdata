// devon dude being happy that he got his goods back
#include "scriptlib.m4.h"

CHECK_FLAG( 163, 0, 1 )
    JUMP_TO_END

HIDE_PKMN
GET_MAPOBJECT( 22, 26, 3 )
    COPY_REGISTER( 0, 1 )
    LOCK_R( 1 )
    EXCLAMATION_R( 1 ) // Show exclamation mark
    // Check if the player has the devon goods

    CHECK_ITEM( I_DEVON_GOODS, 1, 2 )
        // player got the goods back
        MESSAGE( 381, 0 )
        SKIP( 1 )
    MESSAGE( 405, 0 )
    GIVE_ITEM( I_PREMIER_BALL, 1 )
    // make the player follow into devon hq
    MESSAGE( 382, 0 )
    SET_FLAG( 163, 1 )
    WARP_CROSSBANK( 20, 0xa8, 0xae, 3 )
END_OF_PROGRAM
