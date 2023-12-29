// lilycove contest hall lobby reception
#include "scriptlib.m4.h"

// pokeblock case collected
CHECK_FLAG( 352, 1, 4 )
    MESSAGE( 748, 0 )
    GIVE_ITEM( I_POKEBLOCK_CASE, 1 )
    SET_FLAG( 352, 1 )
    MESSAGE( 749, 0 )

MESSAGE( 750, 0 )
// TODO

// for desquid purposes, set flag that player participated in contest
SET_FLAG( 365, 1 )

END_OF_PROGRAM
