// mauville coin clerk
#include "scriptlib.m4.h"

MESSAGE( 982, 0 )

// check if player already has a coin case
CHECK_ITEM( I_COIN_CASE, 1, 1 )
    // has coin case
    SKIP( 2 )
// else
    MESSAGE( 983, 0 )
    JUMP_TO_END

MESSAGE( 984, 0 )
// ask if player wants to buy coins
YES_NO_MESSAGE( 985, 128, 2 )
    MESSAGE( 986, 0 )
    JUMP_TO_END

// try to pay $1000
CHECK_MONEY( 1000, 2 )
    // not enough money
    MESSAGE( 987, 0 )
    JUMP_TO_END

PAY_MONEY( 1000 )
MESSAGE( 988, 0 )
ADD_CURRENCY( 50, CURRENCY_COINS )
MESSAGE( 989, 1 )

