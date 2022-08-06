// shoal cave warp script
#include "scriptlib.m4.h"

// if on high tide, warp to hid tide map
GET_CURRENT_HOURS_MOD_TWELVE

CHECK_REGISTER_L( 0, 6, 6 )

// high tide position
SET_REGISTER( 0, 1 ) // type (cave entry)
SET_REGISTER( 1, 16 ) // bank
SET_REGISTER( 2, 1 ) // mapy
SET_REGISTER( 3, 3 ) // mapx
SET_REGISTER( 4, 30 ) // y
SET_REGISTER( 5, 20 ) // x



// default position
SET_REGISTER( 0, 1 ) // type (cave entry)
SET_REGISTER( 1, 16 ) // bank
SET_REGISTER( 2, 1 ) // mapy
SET_REGISTER( 3, 1 ) // mapx
SET_REGISTER( 4, 30 ) // y
SET_REGISTER( 5, 20 ) // x



