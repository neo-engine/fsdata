// Getting HM07 rock smash
#include "scriptlib.m4.h"


CHECK_FLAG( 386, 1, 5 )
    MESSAGE( 1055, 0 )
    GIVE_ITEM( I_HM09, 1 )
    SET_FLAG( 386, 1 )
    MESSAGE( 1056, 0 )
    JUMP_TO_END

// check if player collected eviolite
CHECK_FLAG( 301, 1, 2 )
    MESSAGE( 1056, 0 )
    JUMP_TO_END

MESSAGE( 1057, 0 )
END_OF_PROGRAM
