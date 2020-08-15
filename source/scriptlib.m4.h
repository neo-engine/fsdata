// Basic things useful for any map script.
//
// A map script is first processed by the C preprocessor (to allow aliases
// for pkmn names, etc), then by GNU m4, and then compiled.
// Empty lines and c(++)-style comments are ignored.
changequote(<!,!>)dnl
dnl
#include "pokemonNames.h"
#include "locationNames.h"
#include "itemNames.h"
#include "moveNames.h"
#include "soundbank.h"
dnl
// General m4 macros
define(<!for!>,<!ifelse($#,0,<!<!$0!>!>,<!ifelse(eval($2<=$3),1,
                <!pushdef(<!$1!>,$2)$4<!!>popdef(<!$1!>)$0(<!$1!>,incr($2),$3,<!$4!>)!>)!>)!>)dnl
dnl
define(<!foreach!>,<!ifelse(eval($#>2),1,
            <!pushdef(<!$1!>,<!$3!>)$2<!!>popdef(<!$1!>)dnl
            <!!>ifelse(eval($#>3),1,<!$0(<!$1!>,<!$2!>,shift(shift(shift($@))))!>)!>)!>)dnl
dnl
define(<!while!>,<!ifelse($#,0,<!<!$0!>!>,eval($1+0),1,<!$2<!!>$0($@)!>)!>)dnl
dnl
// General map script aliases
dnl
define(<!ins4!>,<!eval((($1 & 255) << 24) | (($2 & 255) << 16) | (($3 & 255) << 8) | ($4 & 255))!>)
define(<!ins3!>,<!eval((($1 & 255) << 24) | (($2 & 4095) << 12) | ($3 & 4095))!>)
dnl
#define EVAL_REG 0
dnl
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
dnl
#define EOP 0
#define SMO 1
#define MMO 2
#define DMO 3
#define CFL 4
#define SFL 5
#define CRG 6
#define SRG 7
#define MRG 8
#define JMP 9
#define JMB 10
dnl
#define SMOR 11
#define MMOR 12
#define DMOR 13
#define CFLR 14
#define SFLR 15
#define CRGL 16
#define CRGG 17
#define CRGN 18
#define MPL  19
#define CMO 20
#define ATT 90
#define REM 91
#define BTR 100
dnl
#define PMO 117
#define SMC 118
#define SLC 119
#define SWT 120
#define WAT 121
#define MBG 122
#define MIT 123
dnl
#define YNM 125
#define CLL 126
#define MSG 127
dnl
#define MESSAGE( p_messageId, p_messageType ) ins3( MSG, p_messageId, p_messageType )
dnl
#define SPAWN_MAPOBJECT( p_picId, p_locX, p_locY ) ins4( SMO, p_picId, p_locX, p_locY ) /* dnl Spawns a new map object at (globX, globY); writes the new MO id to REGISTER1 */
#define MOVE_MAPOBJECT( p_mapObject, p_direction, p_amount ) ins4( MMO, p_mapObject, p_direction, p_amount )/* Moves the specified MO in the specified direction. */
#define DESTROY_MAPOBJECT( p_mapObject ) ins4( DMO, p_mapObject, 0, 0 )
dnl
#define SPAWN_MAPOBJECT_R( p_register, p_localX, p_localY ) ins4( SMOR, p_register, p_globX, p_globY ) /* dnl Spawns a new map object at (globX, globY); writes the new MO id to REGISTER1 */
#define MOVE_MAPOBJECT_R( p_register, p_direction, p_amount ) ins4( MMOR, p_register, p_direction, p_amount )/* Moves the specified MO in the specified direction. */
#define DESTROY_MAPOBJECT_R( p_register ) ins4( DMOR, p_register, 0, 0 )
dnl
dnl
#define CHECK_FLAG( p_flag, p_value, p_skippedInstructionsIfTrue ) ins4( CFL, p_flag, p_value, p_skippedInstructionsIfTrue ) /* Checks whether the specified flag has the specified value, skips the specified number of instructions (after the current one) if the check passes */
#define SET_FLAG( p_flag, p_value ) ins4( SFL, p_flag, p_value, 0 )
dnl
#define CHECK_FLAG_R( p_register, p_value, p_skippedInstructionsIfTrue ) ins4( CFL, p_register, p_value, p_skippedInstructionsIfTrue ) /* Checks whether the specified flag has the specified value, skips the specified number of instructions (after the current one) if the check passes */
#define SET_FLAG_R( p_register, p_value ) ins4( SFLR, p_register, p_value, 0 )
dnl
#define MOVE_PLAYER( p_direction, p_amount ) ins4( MPL, 0, p_direction, p_amount )
dnl
#define CHECK_REGISTER( p_register, p_value, p_skippedInstructionsIfTrue ) ins4( CRG, p_register, p_value, p_skippedInstructionsIfTrue )
#define CHECK_REGISTER_L( p_register, p_value, p_skippedInstructionsIfTrue ) ins4( CRGL, p_register, p_value, p_skippedInstructionsIfTrue )
#define CHECK_REGISTER_G( p_register, p_value, p_skippedInstructionsIfTrue ) ins4( CRGG, p_register, p_value, p_skippedInstructionsIfTrue )
#define CHECK_REGISTER_N( p_register, p_value, p_skippedInstructionsIfTrue ) ins4( CRGN, p_register, p_value, p_skippedInstructionsIfTrue )
#define SET_REGISTER( p_register, p_value ) ins4( SRG, p_register, p_value, 0 )
dnl
#define GET_CURRENT_MAPOBJECT ins4( CMO, 0, 0, 0 )
#define WAIT( p_duration ) ins3( WAT, p_duration, 0 )
dnl
#define YES_NO_MESSAGE( p_messageId, p_messageType, p_skipIfYes ) ins3( YNM, p_messageId, p_messageType ) \
    CHECK_REGISTER( EVAL_REG, 1, p_skipIfYes )
dnl
#define PLAY_MUSIC_ONESHOT( p_modId, p_duration ) ins3( PMO, p_modId, p_duration )
dnl
#define BADGE_COUNT( p_region ) ins4( CLL, 3, p_region, 0 )
#define HEAL_TEAM ins4( CLL, 1, 0, 0 )
#define SELL_ITEMS ins4( CLL, 2, 0, 0 )
dnl
#define MART_BEGIN( p_coinType, p_allowSell ) ins4( MBG, p_coinType, p_allowSell, 0 )
#define MART_ITEM( p_item, p_price ) ins3( MIT, p_item, p_price )
dnl
#define ATTACH_PLAYER ins4( ATT, 0, 0, 0 )
#define REMOVE_PLAYER ins4( REM, 0, 0, 0 )
dnl
#define END_OF_PROGRAM ins4( EOP, 0, 0, 0 )
#define JUMP_TO_END ins4( EOP, 0, 0, 0 )
