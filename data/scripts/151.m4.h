// infinity cave warp script reserved/entry1
#include "scriptlib.m4.h"

INIT_INFINITY_CAVE( 3 )
CONTINUE_INFINITY_CAVE

COPY_REGISTER( 0, 2 )
COPY_REGISTER( 1, 3 )

SET_REGISTER( 0, 1 ) // type (cave entry)
SET_REGISTER( 1, 99 ) // bank
SET_REGISTER( 4, 27 ) // y
SET_REGISTER( 5, 15 ) // x
SET_REGISTER( 6, 3 ) // z

