// winstrates hand out macho brace
#include "scriptlib.m4.h"

CHECK_FLAG( 391, 0, 2 )
    MESSAGE( 1096, 0 )
    JUMP_TO_END

MESSAGE( 1095, 0 )
GIVE_ITEM( I_MACHO_BRACE, 1 )
SET_FLAG( 391, 1 )

END_OF_PROGRAM
