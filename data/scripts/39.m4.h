// getting the wailmer pail
#include "scriptlib.m4.h"

MESSAGE( 205, 0 )
CHECK_FLAG( 46, 1, 2 )
    MESSAGE( 206, 0 )
    SET_FLAG( 46, 1 )
YES_NO_MESSAGE( 207, 0, 2 )
    MESSAGE( 208, 0 )
    JUMP_TO_END
MESSAGE( 209, 0 )
END_OF_PROGRAM
