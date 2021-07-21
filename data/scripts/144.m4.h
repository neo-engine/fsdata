// green crystal
#include "scriptlib.m4.h"

#define SHARD I_GREEN_SHARD
#define REQ_AMOUNT 77

#define CRYSTAL_FLAG 219
#define CRYSTAL_VAR 13

#define IDLE_MSG 534
#define ACTIVATED_MSG 556
#define STATUS_SING_MSG 557
#define STATUS_MULT_MSG 558
#define REACT_MSG 559
#define DONATE_MSG 560
#define SUCCESS_MSG 561

// Check if red crystal is activated
CHECK_FLAG( CRYSTAL_FLAG, 0, 2 )
    MESSAGE( ACTIVATED_MSG, 0 )
    JUMP_TO_END

MESSAGE( IDLE_MSG, 0 )
// Check how many shards have been placed in the crystal

CHECK_VAR( CRYSTAL_VAR, 0, 5 )
    CHECK_VAR_G( CRYSTAL_VAR, 1, 2 )
        MESSAGE( STATUS_SING_MSG, 0 )
        SKIP( 1 )
        MESSAGE( STATUS_MULT_MSG, 0 )
    SKIP( 5 )

CHECK_ITEM( SHARD, 1, 2 )
    MESSAGE( REACT_MSG, 0 )
    SKIP( 1 )
    JUMP_TO_END

CHECK_VAR_L( CRYSTAL_VAR, REQ_AMOUNT, 1 )
    SET_VAR( CRYSTAL_VAR, REQ_AMOUNT )

// Compute how many shards are still needed
SET_REGISTER( 6, REQ_AMOUNT )
GET_VAR( CRYSTAL_VAR, 5 )
SUBTRACT_REGISTER_FROM_REGISTER( 6, 5 )

// Check if additional shards are needed
CHECK_REGISTER( 6, 0, 12 )
    // check how many shards can be donated max
    GET_ITEM_AMOUNT( SHARD )

    CHECK_REGISTER_G( 0, 0, 1 )
        JUMP_TO_END

    MIN( EVAL_REG, 6, 4 )
// Ask if the player wants to add a shard
    COUNTER_MESSAGE_REG( DONATE_MSG, 4 )

    // player doesn't want to donate a shard
    CHECK_REGISTER_G( 0, 0, 1 )
        JUMP_TO_END

    // take item from player
    SET_REGISTER( 1, SHARD )
    COPY_REGISTER( 0, 2 )
    TAKE_ITEM_R( 1 )

    // Set variable
    ADD_REGISTER_TO_REGISTER( 5, 2 )
    SET_VAR_REG( CRYSTAL_VAR, 5 )

// Check if enough shards are placed in the crystal

CHECK_VAR_G( CRYSTAL_VAR, REQ_AMOUNT - 1, 1 )
    JUMP_TO_END

SET_FLAG( CRYSTAL_FLAG, 1 )
REDRAW_MAP
MESSAGE( SUCCESS_MSG, 0 )
