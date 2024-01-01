// Mauville trade dream ball for coin case
#include "scriptlib.m4.h"

// check if player already has a coin case
CHECK_ITEM( I_COIN_CASE, 1, 2 )
    MESSAGE( 955, 0 )
    JUMP_TO_END

MESSAGE( 952, 0 )
CHECK_ITEM( I_DREAM_BALL, 1, 1 )
    SKIP( 1 )
// else
    JUMP_TO_END

YES_NO_MESSAGE( 953, 0, 2 )
    MESSAGE( 956, 0 )
    JUMP_TO_END

MESSAGE( 954, 0 )
TAKE_ITEM( I_DREAM_BALL, 1 )
GIVE_ITEM( I_COIN_CASE, 1 )
MESSAGE( 955, 0 )
