// mauvile gym floor tile 1
#include "scriptlib.m4.h"

// Activates
//
//    +--+
//    |  |
// +--+--+--+
// | *|  |* |
// +--+--+--+
// | *|   * |
// +--+  +--+
// | *|   * |
// +--+  +--+
//   o    *

// reset map
// reset flags
SET_FLAG( 370, 0 )
SET_FLAG( 371, 0 )
SET_FLAG( 372, 0 )
SET_FLAG( 373, 0 )
SET_FLAG( 374, 0 )
SET_FLAG( 375, 0 )
SET_FLAG( 376, 0 )
SET_FLAG( 377, 0 )

// reset bottom switches
SET_BLOCK( 13, 19, 0x205 )
SET_BLOCK( 18, 19, 0x205 )
SET_BLOCK( 13, 16, 0x205 )
SET_BLOCK( 18, 16, 0x205 )
SET_BLOCK( 13, 13, 0x205 )
SET_BLOCK( 18, 13, 0x205 )
SET_BLOCK( 13, 10, 0x205 )
SET_BLOCK( 18, 10, 0x205 )

// reset barriers
// horizontal barriers starting from bottom
SET_BLOCK_AND_MOVEMENT( 15, 17, 0x220, 1 )
SET_BLOCK_AND_MOVEMENT( 16, 17, 0x221, 1 )
SET_BLOCK_AND_MOVEMENT( 15, 18, 0x228, 1 )
SET_BLOCK_AND_MOVEMENT( 16, 18, 0x229, 1 )

SET_BLOCK_AND_MOVEMENT( 15, 14, 0x220, 1 )
SET_BLOCK_AND_MOVEMENT( 16, 14, 0x221, 1 )
SET_BLOCK_AND_MOVEMENT( 15, 15, 0x228, 1 )
SET_BLOCK_AND_MOVEMENT( 16, 15, 0x229, 1 )

SET_BLOCK_AND_MOVEMENT( 15, 11, 0x220, 1 )
SET_BLOCK_AND_MOVEMENT( 16, 11, 0x221, 1 )
SET_BLOCK_AND_MOVEMENT( 15, 12, 0x228, 1 )
SET_BLOCK_AND_MOVEMENT( 16, 12, 0x229, 1 )

SET_BLOCK_AND_MOVEMENT( 15, 8, 0x220, 1 )
SET_BLOCK_AND_MOVEMENT( 16, 8, 0x221, 1 )
SET_BLOCK_AND_MOVEMENT( 15, 9, 0x228, 1 )
SET_BLOCK_AND_MOVEMENT( 16, 9, 0x229, 1 )

SET_BLOCK_AND_MOVEMENT( 15, 5, 0x220, 1 )
SET_BLOCK_AND_MOVEMENT( 16, 5, 0x221, 1 )
SET_BLOCK_AND_MOVEMENT( 15, 6, 0x228, 1 )
SET_BLOCK_AND_MOVEMENT( 16, 6, 0x229, 1 )

// left vertical barriers from bottom
SET_BLOCK_AND_MOVEMENT( 14, 15, 0x240, 1 )
SET_BLOCK_AND_MOVEMENT( 14, 16, 0x248, 1 )
SET_BLOCK_AND_MOVEMENT( 14, 17, 0x250, 1 )

SET_BLOCK_AND_MOVEMENT( 14, 12, 0x240, 1 )
SET_BLOCK_AND_MOVEMENT( 14, 13, 0x248, 1 )
SET_BLOCK_AND_MOVEMENT( 14, 14, 0x250, 1 )

SET_BLOCK_AND_MOVEMENT( 14, 9, 0x240, 1 )
SET_BLOCK_AND_MOVEMENT( 14, 10, 0x248, 1 )
SET_BLOCK_AND_MOVEMENT( 14, 11, 0x250, 1 )

// right vertical barriers from bottom
SET_BLOCK_AND_MOVEMENT( 17, 15, 0x240, 1 )
SET_BLOCK_AND_MOVEMENT( 17, 16, 0x248, 1 )
SET_BLOCK_AND_MOVEMENT( 17, 17, 0x250, 1 )

SET_BLOCK_AND_MOVEMENT( 17, 12, 0x240, 1 )
SET_BLOCK_AND_MOVEMENT( 17, 13, 0x248, 1 )
SET_BLOCK_AND_MOVEMENT( 17, 14, 0x250, 1 )

SET_BLOCK_AND_MOVEMENT( 17, 9, 0x240, 1 )
SET_BLOCK_AND_MOVEMENT( 17, 10, 0x248, 1 )
SET_BLOCK_AND_MOVEMENT( 17, 11, 0x250, 1 )


// set floor tile that was stepped on
SET_FLAG( 370, 1 )
SET_BLOCK( 13, 19, 0x206 )

SET_BLOCK_AND_MOVEMENT( 15, 17, 0x230, 0 )
SET_BLOCK_AND_MOVEMENT( 16, 17, 0x231, 0 )
SET_BLOCK_AND_MOVEMENT( 15, 18, 0x238, 0 )
SET_BLOCK_AND_MOVEMENT( 16, 18, 0x239, 0 )

SET_BLOCK_AND_MOVEMENT( 15, 14, 0x230, 0 )
SET_BLOCK_AND_MOVEMENT( 16, 14, 0x231, 0 )
SET_BLOCK_AND_MOVEMENT( 15, 15, 0x238, 0 )
SET_BLOCK_AND_MOVEMENT( 16, 15, 0x239, 0 )


SET_BLOCK_AND_MOVEMENT( 17, 15, 0x242, 1 )
SET_BLOCK_AND_MOVEMENT( 17, 16, 0x232, 0 )
SET_BLOCK_AND_MOVEMENT( 17, 17, 0x250, 1 )

SET_BLOCK_AND_MOVEMENT( 17, 12, 0x242, 1 )
SET_BLOCK_AND_MOVEMENT( 17, 13, 0x232, 0 )
SET_BLOCK_AND_MOVEMENT( 17, 14, 0x250, 1 )

