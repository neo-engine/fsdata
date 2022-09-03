//  sealed chamber room 1, dig used
#include "scriptlib.m4.h"

EARTHQUAKE
WAIT( 15 )
EARTHQUAKE
WAIT( 40 )

// mark wall collapsed
SET_FLAG( 135, 1 )

REDRAW_MAP

