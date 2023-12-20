// Basic things useful for any map script.
//
// A map script is first processed by the C preprocessor (to allow aliases
// for pkmn names, etc), then by GNU m4, and then compiled.
// Empty lines and c(++)-style comments are ignored.
changequote(<!,!>)dnl
dnl
#include "bgmNames.h"
#include "itemNames.h"
#include "locationNames.h"
#include "moveNames.h"
#include "pokemonNames.h"
dnl
#define WEATHER_NOTHING         0
#define WEATHER_SUNNY           1
#define WEATHER_REGULAR         2
#define WEATHER_RAINY           3
#define WEATHER_SNOW            4
#define WEATHER_THUNDERSTORM    5
#define WEATHER_MIST            6
#define WEATHER_BLIZZARD        7
#define WEATHER_SANDSTORM       8
#define WEATHER_FOG             9
#define WEATHER_DENSE_MIST      0xa
#define WEATHER_CLOUDY          0xb
#define WEATHER_HEAVY_SUNLIGHT  0xc
#define WEATHER_HEAVY_RAIN      0xd
#define WEATHER_UNDERWATER      0xe
#define WEATHER_DARK_FLASHABLE  0xf
#define WEATHER_DARK_PERMANENT  0x10
#define WEATHER_DARK_FLASH_USED 0x11
#define WEATHER_FOREST_CLOUDS   0x12
#define WEATHER_ASH_RAIN        0x13
#define WEATHER_FLASH_1         0x14
#define WEATHER_FLASH_2         0x15
dnl
#define DAYTIME_NIGHT   0
#define DAYTIME_MORNING 1
#define DAYTIME_DAY     2
#define DAYTIME_DUSK    3
#define DAYTIME_EVENING 4
dnl
#define SFX_BATTLE_ABILITY       0
#define SFX_BATTLE_BALLDROP      1
#define SFX_BATTLE_BALLSHAKE     2
#define SFX_BATTLE_DAMAGE_NORMAL 3
#define SFX_BATTLE_DAMAGE_SUPER  4
#define SFX_BATTLE_DAMAGE_WEAK   5
#define SFX_BATTLE_DECREASE      6
#define SFX_BATTLE_ESCAPE        7
#define SFX_BATTLE_EXPFULL       8
#define SFX_BATTLE_FAINT         9
#define SFX_BATTLE_INCREASE      10
#define SFX_BATTLE_JUMPTOBALL    11
#define SFX_BATTLE_RECALL        12
#define SFX_BATTLE_THROW         13
#define SFX_BIKE                 14
#define SFX_BUMP                 15
#define SFX_CANCEL               16
#define SFX_CAVE_WARP            17
#define SFX_CHOOSE               18
#define SFX_ENTER_DOOR           19
#define SFX_EXMARK               20
#define SFX_JUMP                 21
#define SFX_MENU                 22
#define SFX_NAV                  23
#define SFX_OBTAIN_EGG           24
#define SFX_OBTAIN_ITEM          25
#define SFX_OBTAIN_KEY_ITEM      26
#define SFX_PC_CLOSE             27
#define SFX_PC_OPEN              28
#define SFX_SAVE                 29
#define SFX_SELECT               30
#define SFX_SHINY                31
#define SFX_USE_ITEM             32
#define SFX_WARP                 33
#define SFX_TELEPORT_DOWN        34
#define SFX_TELEPORT_UP          35
#define SFX_SLIDING_DOOR         36
#define SFX_HM_CUT               37
#define SFX_HM_FLY               38
#define SFX_HM_ROCKSMASH         39
#define SFX_HM_STRENGTH          40
#define SFX_OBTAIN_TM            41
dnl
#define MOVEMODE_WALK       0
#define MOVEMODE_BIKE       ( 1 << 2 )
#define MOVEMODE_ACRO_BIKE  ( ( 1 << 2 ) | ( 1 << 0 ) )
#define MOVEMODE_MACH_BIKE  ( ( 1 << 2 ) | ( 1 << 1 ) )
#define MOVEMODE_BIKE_JUMP  ( ( 1 << 2 ) | ( 1 << 0 ) | ( 1 << 1 ) )
#define MOVEMODE_SIT        ( 1 << 3 )
#define MOVEMODE_DIVE       ( 1 << 4 )
#define MOVEMODE_ROCK_CLIMB ( 1 << 5 )
#define MOVEMODE_STRENGTH   ( 1 << 6 )
#define MOVEMODE_SURF       ( 1 << 7 )
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
define(<!ins4x!>,<!eval((($1 & 255) << 24) | (($2 & 2047) << 13) | (($3 & 31) << 8) | ($4 & 255))!>)
define(<!ins4s!>,<!eval((($1 & 255) << 24) | (($2 & 31) << 19) | (($3 & 31) << 14) | ($4 & 16383))!>)
define(<!ins3s!>,<!eval((($1 & 255) << 24) | (($2 & 31) << 19) | (($3 & 31) << 14) | ($4 & 16383))!>)
dnl
#define EVAL_REG 0
dnl
#define UP    0
#define RIGHT 1
#define DOWN  2
#define LEFT  3
dnl
#define SINGLE 0
#define DOUBLE 1
dnl
#define EOP  0
#define SMO  1
#define MMO  2
#define DMO  3
#define CFL  4
#define SFL  5
#define CRG  6
#define SRG  7
#define MRG  8
#define JMP  9
#define JMB  10
#define SMOR 11
#define MMOR 12
#define DMOR 13
#define CFLR 14
#define SFLR 15
#define CRGL 16
#define CRGG 17
#define CRGN 18
#define MPL  19
#define CMO  20
#define GMO  21
#define CPP  22
#define LCKR 23
#define ULKR 24
#define BNK  25
#define WRP  26
#define CVR  27
#define CVRN 28
#define CVRG 29
#define CVRL 30
#define MFO  31
#define MFOR 32
#define GIT  33
#define STF  34
#define CTF  35
#define ADD  36
#define ARG  37
#define DIV  38
#define DRG  39
#define HPL  40
#define SPL  41
#define WPL  42
#define MINR 43
#define MAXR 44
#define GVR  45
#define SVR  46
#define SVRR 47
dnl
#define SUB  48
#define SUBR 49
dnl
#define FMM 50
#define UMM 51
#define GMM 52
#define CMM 53
dnl
#define PMR  54
#define PMRA 55
dnl
#define HPK 60
dnl
#define CMN 70
#define PMN 71
dnl
#define EXM  88
#define EXMR 88
#define RDR  89
#define ATT  90
#define REM  91
#define FIXR 92
#define UFXR 93
dnl
#define FNT  99
#define BTR  100
#define BPK  101
#define ITM  102
#define TTM  103
#define UTM  104
#define BTRR 105
#define BPKR 106
#define ITMR 107
#define TTMR 108
#define UTMR 109
dnl
#define SRT 110
#define CRT 111
dnl
#define COUR 112
#define MSC  113
#define RMS  114
#define CRY  115
#define SFX  116
#define PMO  117
#define SMC  118
#define SLC  119
#define SWT  120
#define WAT  121
#define MBG  122
#define MIT  123
#define COU  124
#define YNM  125
#define CLL  126
#define MSG  127
#define CBG  128
#define CIT  129
#define BTZ  130
dnl
#define MAP 140
#define EQ  141
dnl
#define DES 150
dnl
#define SBC  196
#define SBCC 197
#define SMM  198
dnl
dnl
#define CHECK_PKMN_IN_SLOT( p_pkmn, p_slot, p_skipIfTrue ) \
    ins3s( PMR, p_slot, p_skipIfTrue, p_pkmn )
#define CHECK_PKMN_NUMBER_IN_PARTY( p_pkmn, p_minNumber, p_skipIfTrue ) \
    ins3s( PMRA, p_minNumber, p_skipIfTrue, p_pkmn )
dnl
#define REDRAW_MAP ins4( MAP, 0, 0, 0 )
#define EARTHQUAKE ins4( EQ, 0, 0, 0 )
dnl
#define REGISTER_SEEN( p_idx )                ins3( DES, p_idx, 0 )
#define REGISTER_SEEN_FORME( p_idx, p_forme ) ins3( DES, p_idx, p_forme )
dnl
#define HIDE_PKMN ins4( HPK, 0, 0, 0 )
dnl
#define SET_WEATHER( p_newWeather )                 ins3( SWT, p_newWeather, 0 )
#define SET_BLOCK( p_mapX, p_mapY, p_blockIdx )     ins3s( SBC, p_mapX, p_mapY, p_blockIdx )
#define SET_BLOCK_COR( p_mapX, p_mapY, p_blockIdx ) ins3s( SBCC, p_mapX, p_mapY, p_blockIdx )
#define SET_MOVEMENT( p_mapX, p_mapY, p_movement )  ins3s( SMM, p_mapX, p_mapY, p_movement )
#define SET_BLOCK_AND_MOVEMENT( p_mapX, p_mapY, p_blockIdx, p_movement ) \
    ins3s( SBC, p_mapX, p_mapY, p_blockIdx ) ins3s( SMM, p_mapX, p_mapY, p_movement )
dnl
#define WARP_CROSSBANK( p_bank, p_globX, p_globY, p_z ) \
    ins4( BNK, p_bank, p_z, 0 ) ins3( WRP, p_globX, p_globY )
dnl
#define FAINT_PLAYER ins4( FNT, 0, 0, 0 )
dnl
#define LOCK_R( p_register )   ins4( LCKR, p_register, 0, 0 )
#define UNLOCK_R( p_register ) ins4( ULKR, p_register, 0, 0 )
dnl
#define CHECK_PLAYER_POS( p_posX, p_posY, p_posZ ) ins4( CPP, p_posX, p_posY, p_posZ )
#define COPY_REGISTER( p_source, p_target )        ins4( MRG, p_source, p_target, 0 )
dnl
#define MIN( p_sreg1, p_sreg2, p_treg ) ins4( MINR, p_sreg1, p_sreg2, p_treg )
#define MAX( p_sreg1, p_sreg2, p_treg ) ins4( MAXR, p_sreg1, p_sreg2, p_treg )
dnl
#define ADD_CONSTANT_TO_REGISTER( p_targetRegister, p_constant ) \
    ins3( ADD, p_targetRegister, p_constant )
#define ADD_REGISTER_TO_REGISTER( p_targetRegister, p_sourceRegister ) \
    ins4( ARG, p_targetRegister, p_sourceRegister, 0 )
#define SUBTRACT_CONSTANT_FROM_REGISTER( p_targetRegister, p_constant ) \
    ins3( SUB, p_targetRegister, p_constant )
#define SUBTRACT_REGISTER_FROM_REGISTER( p_targetRegister, p_sourceRegister ) \
    ins4( SUBR, p_targetRegister, p_sourceRegister, 0 )
#define DIVIDE_REGISTER_BY_CONSTANT( p_targetRegister, p_constant ) \
    ins3( DIV, p_targetRegister, p_constant )
#define DIVIDE_REGISTER_BY_REGISTER( p_targetRegister, p_sourceRegister ) \
    ins4( DRG, p_targetRegister, p_sourceRegister, 0 )
dnl
#define PLAY_MUSIC( p_musicId ) ins3( MSC, p_musicId, 0 )
#define RESTORE_MUSIC           ins3( RMS, 0, 0 )
dnl
#define GET_MAPOBJECT( p_localX, p_localY, p_z ) ins4( GMO, p_localX, p_localY, p_z )
#define EXCLAMATION( p_objectId )                ins4( EXM, p_objectId, 0, 0 )
#define EXCLAMATION_R( p_register )              ins4( EXMR, p_register, 0, 0 )
#define REDRAW_OBJECTS                           ins4( RDR, 0, 0, 0 )
#define SKIP( p_skippedInsFor )                  ins4( JMP, p_skippedInsFor, 0, 0 )
#define REWIND( p_skippedInsBack )               ins4( JMB, p_skippedInsBack, 0, 0 )
#define FIX_MAPOBJECT_R( p_register )            ins4( FIXR, p_register, 0, 0 )
#define UNFIX_MAPOBJECT_R( p_register )          ins4( UFXR, p_register, 0, 0 )
dnl
#define MESSAGE( p_messageId, p_messageType ) ins3( MSG, p_messageId, p_messageType )
dnl
#define CHANGE_MOVE_MODE( p_mode ) ins3( CMM, p_mode, 0 )
#define FORCE_MOVE_MODE            ins4( FMM, 0, 0, 0 )
#define UNLOCK_MOVE_MODE           ins4( UMM, 0, 0, 0 )
#define GET_MOVE_MODE              ins4( GMM, 0, 0, 0 )
#define CHECK_CURRENT_MOVE_MODE( p_mode, p_skipIfYes ) \
    GET_MOVE_MODE CHECK_REGISTER( EVAL_REG, p_mode, p_skipIfYes )
#define CHECK_CURRENT_MOVE_MODE_N( p_mode, p_skipIfNo ) \
    GET_MOVE_MODE CHECK_REGISTER_N( EVAL_REG, p_mode, p_skipIfNo )
dnl
#define SPAWN_MAPOBJECT( p_picId, p_locX, p_locY )                                                 \
    ins4s( SMO, p_locX, p_locY, p_picId ) /* dnl Spawns a new map object at (globX, globY); writes \
                                            the new MO id to REGISTER 0 */
#define MOVE_MAPOBJECT( p_mapObject, p_direction, p_amount ) \
    ins4( MMO, p_mapObject, p_direction,                     \
          p_amount ) /* Moves the specified MO in the specified direction. */
#define MOVE_MAPOBJECT_FAST( p_mapObject, p_direction, p_amount ) \
    ins4( MFO, p_mapObject, p_direction,                          \
          p_amount ) /* Moves the specified MO in the specified direction. */
#define DESTROY_MAPOBJECT( p_mapObject ) ins4( DMO, p_mapObject, 0, 0 )
dnl
#define SPAWN_MAPOBJECT_R( p_register, p_localX, p_localY )                                        \
    ins4( SMOR, p_register, p_localX, p_localY ) /* dnl Spawns a new map object at (globX, globY); \
                                                  writes the new MO id to REGISTER 0 */
#define MOVE_MAPOBJECT_R( p_register, p_direction, p_amount ) \
    ins4( MMOR, p_register, p_direction,                      \
          p_amount ) /* Moves the specified MO in the specified direction. */
#define MOVE_MAPOBJECT_FAST_R( p_register, p_direction, p_amount ) \
    ins4( MFOR, p_register, p_direction,                           \
          p_amount ) /* Moves the specified MO in the specified direction. */
#define DESTROY_MAPOBJECT_R( p_register ) ins4( DMOR, p_register, 0, 0 )
dnl
dnl
#define CHECK_VAR( p_var, p_value, p_skippedInstructionsIfTrue )                               \
    ins4( CVR, p_var, p_value,                                                                 \
          p_skippedInstructionsIfTrue ) /* Checks whether the specified flag has the specified \
                                           value, skips the specified number of instructions   \
                                           (after the current one) if the check passes */
#define CHECK_VAR_N( p_var, p_value, p_skippedInstructionsIfFalse )                             \
    ins4( CVRN, p_var, p_value,                                                                 \
          p_skippedInstructionsIfFalse ) /* Checks whether the specified flag has the specified \
                                            value, skips the specified number of instructions   \
                                            (after the current one) if the check passes */
#define CHECK_VAR_L( p_var, p_value, p_skippedIfTrue )                                        \
    ins4( CVRL, p_var, p_value,                                                               \
          p_skippedIfTrue ) /* Checks whether the specified flag has the specified            \
                                            value, skips the specified number of instructions \
                                            (after the current one) if the check passes */
#define CHECK_VAR_G( p_var, p_value, p_skippedIfTrue )                                        \
    ins4( CVRG, p_var, p_value,                                                               \
          p_skippedIfTrue ) /* Checks whether the specified flag has the specified            \
                                            value, skips the specified number of instructions \
                                            (after the current one) if the check passes */
dnl
#define CHECK_FLAG( p_flag, p_value, p_skippedInstructionsIfTrue )                              \
    ins4x( CFL, p_flag, p_value,                                                                \
           p_skippedInstructionsIfTrue ) /* Checks whether the specified flag has the specified \
                                            value, skips the specified number of instructions   \
                                            (after the current one) if the check passes */
#define CHECK_FLAG_N( p_flag, p_value, p_skippedInstructionsIfFalse )                            \
    ins4x( CFL, p_flag, 1 - p_value,                                                             \
           p_skippedInstructionsIfFalse ) /* Checks whether the specified flag has the specified \
                                             value, skips the specified number of instructions   \
                                             (after the current one) if the check passes */
#define CHECK_TRAINER_FLAG( p_flag, p_value, p_skippedInstructionsIfTrue )                      \
    ins4x( CTF, p_flag, p_value,                                                                \
           p_skippedInstructionsIfTrue ) /* Checks whether the specified flag has the specified \
                                            value, skips the specified number of instructions   \
                                            (after the current one) if the check passes */
#define CHECK_TRAINER_FLAG_N( p_flag, p_value, p_skippedInstructionsIfFalse )                    \
    ins4x( CTF, p_flag, 1 - p_value,                                                             \
           p_skippedInstructionsIfFalse ) /* Checks whether the specified flag has the specified \
                                             value, skips the specified number of instructions   \
                                             (after the current one) if the check passes */
dnl
#define SET_VAR( p_var, p_value )        ins3( SVR, p_var, p_value )
#define SET_VAR_REG( p_var, p_register ) ins3( SVRR, p_var, p_register )
#define GET_VAR( p_var, p_register )     ins3( GVR, p_var, p_register )
dnl
#define SET_FLAG( p_flag, p_value )         ins4x( SFL, p_flag, p_value, 0 )
#define CLEAR_FLAG( p_flag )                ins4x( SFL, p_flag, 0, 0 )
#define SET_TRAINER_FLAG( p_flag, p_value ) ins4x( STF, p_flag, p_value, 0 )
dnl
#define CHECK_FLAG_R( p_register, p_value, p_skippedInstructionsIfTrue )                        \
    ins4x( CFL, p_register, p_value,                                                            \
           p_skippedInstructionsIfTrue ) /* Checks whether the specified flag has the specified \
                                            value, skips the specified number of instructions   \
                                            (after the current one) if the check passes */
#define SET_FLAG_R( p_register, p_value ) ins4x( SFLR, p_register, p_value, 0 )
dnl
#define SET_ROUTE( p_route )                  ins4( SRT, p_route, 0, 0 )
#define CHECK_ROUTE( p_route, p_skipIfEqual ) ins4( CRT, p_route, p_skipIfEqual, 0 )
dnl
#define MOVE_PLAYER( p_direction, p_amount ) ins4( MPL, 0, p_direction, p_amount )
#define WALK_PLAYER( p_direction, p_amount ) ins4( WPL, 0, p_direction, p_amount )
dnl
#define CHECK_REGISTER( p_register, p_value, p_skippedInstructionsIfTrue ) \
    ins4( CRG, p_register, p_value, p_skippedInstructionsIfTrue )
#define CHECK_REGISTER_L( p_register, p_value, p_skippedInstructionsIfTrue ) \
    ins4( CRGL, p_register, p_value, p_skippedInstructionsIfTrue )
#define CHECK_REGISTER_G( p_register, p_value, p_skippedInstructionsIfTrue ) \
    ins4( CRGG, p_register, p_value, p_skippedInstructionsIfTrue )
#define CHECK_REGISTER_N( p_register, p_value, p_skippedInstructionsIfFalse ) \
    ins4( CRGN, p_register, p_value, p_skippedInstructionsIfFalse )
#define SET_REGISTER( p_register, p_value ) ins3( SRG, p_register, p_value )
dnl
#define GET_CURRENT_MAPOBJECT ins4( CMO, 0, 0, 0 )
#define WAIT( p_duration )    ins3( WAT, p_duration, 0 )
dnl
// checks if the player has at least p_money, skips p_skipIfYes ins if that is the case.
#define CHECK_MONEY( p_money, p_skipIfYes ) ins3( CMN, p_money, p_skipIfYes )
#define PAY_MONEY( p_money )                ins3( PMN, p_money, 0 )
dnl
#define GET_ITEM_AMOUNT( p_itemId ) ins3( GIT, p_itemId, 0 )
#define CHECK_ITEM( p_itemId, p_quantity, p_skipIfNo ) \
    GET_ITEM_AMOUNT( p_itemId ) CHECK_REGISTER_L( EVAL_REG, p_quantity, p_skipIfNo )
#define YES_NO_MESSAGE( p_messageId, p_messageType, p_skipIfYes ) \
    ins3( YNM, p_messageId, p_messageType ) CHECK_REGISTER( EVAL_REG, 1, p_skipIfYes )
#define YES_NO_MESSAGE_D( p_messageId, p_messageType ) ins3( YNM, p_messageId, p_messageType )
#define YES_NO_MESSAGE_N( p_messageId, p_messageType, p_skipIfNo ) \
    ins3( YNM, p_messageId, p_messageType ) CHECK_REGISTER( EVAL_REG, 0, p_skipIfNo )
dnl
#define COUNTER_MESSAGE( p_messageId, p_maxVal )        ins3( COU, p_messageId, p_maxVal )
#define COUNTER_MESSAGE_REG( p_messageId, p_maxValReg ) ins3( COUR, p_messageId, p_maxValReg )
dnl
#define PLAY_MUSIC_ONESHOT( p_modId, p_duration ) ins3( PMO, p_modId, p_duration )
#define PLAY_SOUND_EFFECT( p_sfx )                ins3( SFX, p_sfx, 0 )
#define PLAY_CRY( p_pkmnId, p_forme )             ins3( CRY, p_pkmnId, p_forme )
dnl
#define BADGE_COUNT( p_region )          ins4( CLL, 3, p_region, 0 )
#define HEAL_TEAM                        ins4( CLL, 1, 0, 0 )
#define SELL_ITEMS                       ins4( CLL, 2, 0, 0 )
#define GET_INITGAME_ITEMCOUNT           ins4( CLL, 4, 0, 0 )
#define GET_INITGAME_ITEM                ins4( CLL, 5, 0, 0 )
#define INIT_PKMN                        ins4( CLL, 6, 0, 0 )
#define INIT_BOT                         ins4( CLL, 7, 0, 0 )
#define CATCHING_TUTORIAL                ins4( CLL, 8, 0, 0 )
#define AWARD_BADGE( p_region, p_badge ) ins4( CLL, 9, p_region, p_badge )
#define CBOX_RUN                         ins4( CLL, 10, 0, 0 )
#define GET_CURRENT_TIME                 ins4( CLL, 11, 0, 0 )
#define DAY_CARE_OLD_LADY( p_dayCare )   ins4( CLL, 12, p_dayCare, 0 )
#define DAY_CARE_OLD_MAN( p_dayCare )    ins4( CLL, 13, p_dayCare, 0 )
#define SAVE_GAME                        ins4( CLL, 14, 0, 0 )
#define FORCE_SAVE_GAME                  ins4( CLL, 14, 1, 0 )
#define GET_CURRENT_HOURS                ins4( CLL, 15, 24, 0 )
#define GET_CURRENT_HOURS_MOD_TWELVE     ins4( CLL, 15, 12, 0 )
#define GET_PLAYTIME_HOURS               ins4( CLL, 16, 0, 0 )
#define HALL_OF_FAME                     ins4( CLL, 17, 0, 0 )
#define INIT_INFINITY_CAVE( p_stat )     ins4( CLL, 18, p_stat, 0 )
#define CONTINUE_INFINITY_CAVE           ins4( CLL, 19, 0, 0 )
#define MAPENTER_INFINITY_CAVE           ins4( CLL, 20, 0, 0 )
#define GATECHECK_INFINITY_CAVE          ins4( CLL, 21, 0, 0 )
#define SELF_TRADER                      ins4( CLL, 22, 0, 0 )
#define INGAME_TRADE( p_tradeIdx )       ins4( CLL, 23, p_tradeIdx, 0 )
#define MYSTERY_EVENT_CLERK              ins4( CLL, 24, 0, 0 )
dnl
// runs the battle factory script, starts right after the player saved
// p_level may be one of 0 - (battle tent, lv 30), 1 - (factory, lv 50), 2 - (factory 100)
#define BATTLE_FACTORY( p_level, p_rounds ) ins4( BTZ, 0, p_level, p_rounds )
dnl
#define BATTLE_TRAINER( p_trainerId, p_mode ) ins3( BTR, p_trainerId, p_mode )
#define BATTLE_PKMN( p_speciesId, p_level )   ins3( BPK, p_speciesId, p_level )
#define GIVE_ITEM( p_itemId, p_amount )       ins3( ITM, p_itemId, p_amount )
#define TAKE_ITEM( p_itemId, p_amount )       ins3( TTM, p_itemId, p_amount )
#define USE_ITEM( p_itemId, p_amount )        ins3( UTM, p_itemId, p_amount )
dnl
#define BATTLE_TRAINER_R( p_startRegister ) ins4( BTRR, p_startRegister, 0, 0 )
#define BATTLE_PKMN_R( p_startRegister )    ins4( BPKR, p_startRegister, 0, 0 )
#define GIVE_ITEM_R( p_startRegister )      ins4( ITMR, p_startRegister, 0, 0 )
#define TAKE_ITEM_R( p_startRegister )      ins4( TTMR, p_startRegister, 0, 0 )
#define USE_ITEM_R( p_startRegister )       ins4( UTMR, p_startRegister, 0, 0 )
dnl
#define MART_BEGIN( p_coinType, p_allowSell ) ins4( MBG, p_coinType, p_allowSell, 0 )
#define MART_ITEM( p_item, p_price )          ins3( MIT, p_item, p_price )
dnl
#define CBOX_BEGIN( p_message, p_msgType ) ins3( CBG, p_message, p_msgType )
#define CBOX_ITEM( p_stringId, p_payload ) ins3( CIT, p_stringId, p_payload )
dnl
#define ATTACH_PLAYER ins4( ATT, 0, 0, 0 )
#define REMOVE_PLAYER ins4( REM, 0, 0, 0 )
dnl
#define HIDE_PLAYER ins4( HPL, 0, 0, 0 )
#define SHOW_PLAYER ins4( SPL, 0, 0, 0 )
dnl
#define END_OF_PROGRAM ins4( EOP, 0, 0, 0 )
#define JUMP_TO_END    ins4( EOP, 0, 0, 0 )
