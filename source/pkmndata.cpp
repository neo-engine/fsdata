// Arguments
// pkmnnames.csv abtynames.csv movenames.csv itemnames.csv pkmndata.csv pkmndescr.csv
// pkmnformnames.csv pkmnformes.csv itemdata_medicine.csv

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "fsdata.h"

#define LEARNSET_SIZE 400

fsdataInfo FINFO;

map<pair<u16, u8>, pkmnEvolveData> pkmn_evolve;

map<u16, names>  location_names;
map<string, int> locations;

map<u16, names>  class_names;
map<string, int> classes;

map<string, int> abilities;
vector<names>    ability_names;
vector<descrs>   ability_descrs;

map<string, int> items;
vector<names>    item_names;
vector<itemData> item_data;
vector<descrs>   item_descrs;

map<string, int> moves;
map<string, int> alt_moves; // alternative move names
vector<names>    move_names;
vector<moveData> move_data;
vector<descrs>   move_descrs;

map<string, int>      pkmns;
vector<names>         pkmn_names;
vector<names>         pkmn_species;
vector<descrs>        pkmn_descrs;
vector<vector<names>> forme_names;

vector<pkmnLearnsetData>             pkmn_learnsets;
map<pair<u16, u8>, pkmnLearnsetData> forme_learnsets;

vector<pkmnData>              pkmn_data;
vector<vector<pkmnFormeData>> forme_data;

u8 parseTime( char* p_buffer ) {
    if( !strcmp( p_buffer, "Night" ) ) { return 0; }
    if( !strcmp( p_buffer, "Dawn" ) ) { return 1; }
    if( !strcmp( p_buffer, "Morning" ) ) { return 1; }
    if( !strcmp( p_buffer, "Day" ) ) { return 2; }
    if( !strcmp( p_buffer, "Dusk" ) ) { return 3; }
    if( !strcmp( p_buffer, "Evening" ) ) { return 4; }

    fprintf( stderr, "Unknown time \"%s\"", p_buffer );
    return 0;
}

u8 parseGender( char* p_buffer ) {
    if( !strcmp( p_buffer, "Female" ) ) { return 0; }
    if( !strcmp( p_buffer, "Genderless" ) ) { return 1; }
    if( !strcmp( p_buffer, "Male" ) ) { return 2; }

    fprintf( stderr, "Unknown gender \"%s\"\n", p_buffer );
    return 0;
}

u8 parseContest( char* p_buffer ) {
    if( !strcmp( p_buffer, "Cool" ) ) { return 0; }
    if( !strcmp( p_buffer, "Beauty" ) ) { return 1; }
    if( !strcmp( p_buffer, "Cute" ) ) { return 2; }
    if( !strcmp( p_buffer, "Smart" ) ) { return 3; }
    if( !strcmp( p_buffer, "Tough" ) ) { return 4; }

    fprintf( stderr, "Unknown contest stat \"%s\"\n", p_buffer );
    return 0;
}

pair<pair<u16, u8>, pkmnEvolution> parseEvolution( char* p_buffer ) {
    char          idxbuf[ 10 ], tgbuf[ 30 ], methodbuf[ 100 ];
    pkmnEvolution res = pkmnEvolution( );

    sscanf( p_buffer, "%[^,],%*[^,],%[^,],%hhu,%[^,\n]", idxbuf, tgbuf, &res.m_targetForme,
            methodbuf );

    u16 idx;
    u8  forme = 0;

    if( !sscanf( idxbuf, "%hu_%hhu", &idx, &forme ) ) {
        sscanf( idxbuf, "%hu", &idx );
        forme = 0;
    }

    if( !pkmns.count( string( fixEncoding( tgbuf ) ) ) ) {
        fprintf( stderr, "Unknown target Pokémon %s\n", tgbuf );
        exit( 1 );
    }

    res.m_target = pkmns[ string( fixEncoding( tgbuf ) ) ];

    char buf[ 100 ], buf2[ 100 ];

    if( !strcmp( methodbuf, "trade" ) ) {
        res.m_type = evolutionType::TRADE;
    } else if( !strcmp( methodbuf, "friendship" ) ) {
        res.m_type = evolutionType::FRIEND;
    } else if( !strcmp( methodbuf, "special" ) ) {
        res.m_type = evolutionType::SPECIAL_EVOL;
    } else if( sscanf( methodbuf, "friendshiptime:%[^:]", buf ) ) {
        res.m_param1 = parseTime( fixEncoding( buf ) );
        res.m_type   = evolutionType::FRIEND_AND_TIME;
    } else if( sscanf( methodbuf, "level:%hu", &res.m_param1 ) ) {
        res.m_type = evolutionType::LEVEL_UP;
    } else if( sscanf( methodbuf, "item:%[^:]", buf ) ) {
        res.m_param1 = items[ string( fixEncoding( buf ) ) ];
        if( !res.m_param1 ) {
            fprintf( stderr, "[%hu_%hhu] Unknown item \"%s\"\n", idx, forme, buf );
        }
        res.m_type = evolutionType::ITEM;
    } else if( sscanf( methodbuf, "tradeitem:%[^:]", buf ) ) {
        res.m_param1 = items[ string( fixEncoding( buf ) ) ];
        if( !res.m_param1 ) {
            fprintf( stderr, "[%hu_%hhu] Unknown item \"%s\"\n", idx, forme, buf );
        }
        res.m_type = evolutionType::TRADE_ITEM;
    } else if( sscanf( methodbuf, "tradewith:%[^:]", buf ) ) {
        res.m_param1 = pkmns[ string( fixEncoding( buf ) ) ];
        res.m_type   = evolutionType::TRADE_PKMN;
    } else if( sscanf( methodbuf, "contest:%[^:]", buf ) ) {
        res.m_param1 = parseContest( fixEncoding( buf ) );
        res.m_type   = evolutionType::CONTEST;
    } else if( sscanf( methodbuf, "move:%[^:]", buf ) ) {
        res.m_param1 = moves[ string( fixEncoding( buf ) ) ];
        res.m_type   = evolutionType::MOVE;
    } else if( sscanf( methodbuf, "location:%[^:]", buf ) ) {
        res.m_param1 = locations[ string( fixEncoding( buf ) ) ];
        res.m_type   = evolutionType::PLACE;
    } else if( sscanf( methodbuf, "itemlocation:%[^:]:%[^:]", buf, buf2 ) ) {
        res.m_param1 = items[ string( fixEncoding( buf ) ) ];
        res.m_param2 = locations[ string( fixEncoding( buf2 ) ) ];
        res.m_type   = evolutionType::ITEM_PLACE;
    } else if( sscanf( methodbuf, "itemgender:%[^:]:%[^:]", buf, buf2 ) ) {
        res.m_param1 = items[ string( fixEncoding( buf ) ) ];
        res.m_param2 = parseGender( fixEncoding( buf2 ) );
        res.m_type   = evolutionType::ITEM_GENDER;
    } else if( sscanf( methodbuf, "holditem:%[^:]:%[^:]", buf, buf2 ) ) {
        res.m_param1 = items[ string( fixEncoding( buf ) ) ];
        res.m_param2 = parseTime( fixEncoding( buf2 ) );
        res.m_type   = evolutionType::ITEM_HOLD;
    } else if( sscanf( methodbuf, "levellocation:%hu:%[^:]", &res.m_param1, buf ) ) {
        res.m_param2 = locations[ string( fixEncoding( buf ) ) ];
        res.m_type   = evolutionType::LEVEL_UP_AND_PLACE;
    } else if( sscanf( methodbuf, "leveltime:%hu:%[^:]", &res.m_param1, buf ) ) {
        res.m_param2 = parseTime( fixEncoding( buf ) );
        res.m_type   = evolutionType::LEVEL_UP_AND_TIME;
    } else if( sscanf( methodbuf, "levelgender:%hu:%[^:]", &res.m_param1, buf ) ) {
        res.m_param2 = parseGender( fixEncoding( buf ) );
        res.m_type   = evolutionType::LEVEL_UP_AND_GENDER;
    } else {
        fprintf( stderr, "[%hu_%hhu] Unknown evolution type \"%s\"\n", idx, forme, methodbuf );
    }

    return { { idx, forme }, res };
}

void readEvolutionData( char* p_path, map<pair<u16, u8>, pkmnEvolveData>& p_out ) {
    FILE* f = fopen( p_path, "r" );
    char  buffer[ 500 ];

    p_out = map<pair<u16, u8>, pkmnEvolveData>( );

    map<pair<u16, u8>, vector<pkmnEvolution>> edata = map<pair<u16, u8>, vector<pkmnEvolution>>( );

    set<pair<u16, u8>> evos = set<pair<u16, u8>>( );

    while( fgets( buffer, sizeof( buffer ), f ) ) {
        auto cur = parseEvolution( buffer );
        if( !edata.count( cur.first ) ) { edata[ cur.first ] = vector<pkmnEvolution>( ); }
        edata[ cur.first ].push_back( cur.second );
    }

    for( auto i : edata ) {
        pkmnEvolveData cur   = pkmnEvolveData( );
        cur.m_evolutionCount = i.second.size( );
        for( u8 j = 0; j < cur.m_evolutionCount; ++j ) {
            memcpy( &cur.m_evolutions[ j ], &i.second[ j ], sizeof( pkmnEvolution ) );
        }

        for( auto q : edata ) {
            for( auto j : q.second ) { evos.insert( pair( j.m_target, j.m_targetForme ) ); }
        }

        // Compute pre-evo (it's slow, but I'm lazy)
        cur.m_preEvolution  = 0;
        cur.m_baseEvolution = ( i.first.second << 16 ) | i.first.first;
        for( auto q : edata ) {
            for( auto j : q.second ) {
                if( pair( j.m_target, j.m_targetForme ) == i.first ) {
                    cur.m_preEvolution = q.first.first;
                    if( ( cur.m_baseEvolution & 0xffff ) > cur.m_preEvolution ) {
                        cur.m_baseEvolution = ( q.first.second << 16 ) | q.first.first;
                    }
                    break;
                }
            }
        }

        // compute base evolution; a pkmn has at most 2 evolutions, so just 1 extra pass
        // is enough
        for( auto q : edata ) {
            for( auto j : q.second ) {
                if( u32( ( j.m_targetForme << 16 ) | j.m_target ) == cur.m_baseEvolution ) {
                    if( ( cur.m_baseEvolution & 0xffff ) > q.first.first ) {
                        cur.m_baseEvolution = ( q.first.second << 16 ) | q.first.first;
                    }
                    break;
                }
            }
        }

        /*        fprintf( stderr, "[%hu|%hhu] base evo of %s is %s.\n", i.first.first,
           i.first.second, pkmn_names[ i.first.first ].m_name[ 0 ], pkmn_names[ cur.m_baseEvolution
           & 0xffff ].m_name[ 0 ] );
        */
        p_out[ i.first ] = cur;
    }

    // Check for pkmn with a pre-evo but no evo
    for( auto ii : evos ) {
        u16 i = ii.first;
        if( !p_out.count( ii ) ) {
            pkmnEvolveData cur   = pkmnEvolveData( );
            cur.m_evolutionCount = 0;
            cur.m_preEvolution   = 0;
            cur.m_baseEvolution  = ( ii.second << 16 ) | i;
            for( auto q : edata ) {
                for( auto j : q.second ) {
                    if( j.m_target == i && j.m_targetForme == ii.second ) {
                        cur.m_preEvolution = q.first.first;
                        if( ( cur.m_baseEvolution & 0xffff ) > cur.m_preEvolution ) {
                            cur.m_baseEvolution = ( q.first.second << 16 ) | q.first.first;
                        }
                        break;
                    }
                }
            }

            for( auto q : edata ) {
                for( auto j : q.second ) {
                    if( u32( ( j.m_targetForme << 16 ) | j.m_target ) == cur.m_baseEvolution ) {
                        if( ( cur.m_baseEvolution & 0xffff ) > q.first.first ) {
                            cur.m_baseEvolution = ( q.first.second << 16 ) | q.first.first;
                        }
                        break;
                    }
                }
            }

            if( cur.m_preEvolution ) {
                p_out[ ii ] = cur;

/*                fprintf( stderr, "[%hu|%hhu] base evo of %s is %s.\n", i, ii.second,
                         pkmn_names[ i ].m_name[ 0 ],
                         pkmn_names[ cur.m_baseEvolution & 0xffff ].m_name[ 0 ] );
*/            }
        }
    }

    fprintf( stderr, "read %lu objects from %s\n", p_out.size( ), p_path );
}

pair<u16, pkmnLearnsetData> parseLearnset( char* p_buffer ) {
    char* p   = strtok( p_buffer, "," );
    auto  res = pkmnLearnsetData( );

    if( !pkmns.count( string( fixEncoding( p ) ) ) ) {
        fprintf( stderr, "Unknown Pokémon %s\n", p );
        return { 0, res };
    }

    u16 pkmn = pkmns[ string( p ) ];

    while( ( p = strtok( NULL, "," ) ) ) {
        if( !strcmp( p, "\n" ) ) break;

        char mvname[ 50 ];
        u16  level, mid;
        sscanf( p, "%[^;];%hu", mvname, &level );

        if( !moves.count( string( mvname ) ) ) {
            if( !alt_moves.count( string( mvname ) ) ) {
                fprintf( stderr, "[%s] Unknown move \"%s\"\n", p, mvname );
                mid = 0;
            } else {
                mid = alt_moves[ string( mvname ) ];
            }
        } else {
            mid = moves[ string( mvname ) ];
        }
        res.push_back( { level, mid } );
    }

    sort( res.begin( ), res.end( ) );

    return { pkmn, res };
}

pair<pair<u16, u8>, pkmnLearnsetData> parseFormeLearnset( char* p_buffer ) {
    char* p   = strtok( p_buffer, "," );
    auto  res = pkmnLearnsetData( );

    char buffer[ 100 ];
    u8   forme;
    sscanf( p, "%[^_]_%hhu", buffer, &forme );

    if( !pkmns.count( string( fixEncoding( buffer ) ) ) ) {
        fprintf( stderr, "Unknown Pokémon %s\n", buffer );
        return { { 0, 0 }, res };
    }

    u16 pkmn = pkmns[ string( buffer ) ];

    while( ( p = strtok( NULL, "," ) ) ) {
        if( !strcmp( p, "\n" ) ) break;

        char mvname[ 50 ];
        u16  level, mid;
        sscanf( p, "%[^;];%hu", mvname, &level );

        if( !moves.count( string( mvname ) ) ) {
            if( !alt_moves.count( string( mvname ) ) ) {
                fprintf( stderr, "[%s] Unknown move \"%s\"\n", p, mvname );
                mid = 0;
            } else {
                mid = alt_moves[ string( mvname ) ];
            }
        } else {
            mid = moves[ string( mvname ) ];
        }
        res.push_back( { level, mid } );
    }

    sort( res.begin( ), res.end( ) );

    return { { pkmn, forme }, res };
}

void readLearnsetData( char* p_learnsetData, vector<pkmnLearnsetData>& p_out ) {
    FILE* f = fopen( p_learnsetData, "r" );
    char  buffer[ 6000 ];
    p_out.assign( pkmn_data.size( ), { } );
    while( f && fgets( buffer, sizeof( buffer ), f ) ) {
        auto tmp = parseLearnset( buffer );
        assert( tmp.first < p_out.size( ) );
        p_out[ tmp.first ] = tmp.second;
    }
    fclose( f );
}

void readFormeLearnsetData( char* p_learnsetData, map<pair<u16, u8>, pkmnLearnsetData>& p_out ) {
    FILE* f = fopen( p_learnsetData, "r" );
    char  buffer[ 6000 ];
    while( f && fgets( buffer, sizeof( buffer ), f ) ) {
        auto tmp           = parseFormeLearnset( buffer );
        p_out[ tmp.first ] = tmp.second;
    }
    fclose( f );
}

moveData parseMoveData( char* p_buffer ) {
    // printf( "parsing %s\n", p_buffer );

    moveData res = moveData( );

    u16  id;
    char alt_id[ 70 ];
    char type_buf[ 50 ] = { 0 }, contesttype_buf[ 50 ] = { 0 };
    char cat_buf[ 50 ] = { 0 }, defcat_buf[ 50 ] = { 0 };
    char weather_buf[ 50 ] = { 0 }, pseudoWeather_buf[ 50 ] = { 0 }, terrain_buf[ 50 ] = { 0 },
                         sidecond_buf[ 50 ] = { 0 };
    char slotcon_buf[ 50 ] = { 0 }, damage_buf[ 50 ] = { 0 }, target_buf[ 50 ] = { 0 },
                         prestg_buf[ 100 ] = { 0 };
    char heal_buf[ 50 ] = { 0 }, recoil_buf[ 50 ] = { 0 }, drain_buf[ 50 ] = { 0 },
                      multihit_buf[ 50 ] = { 0 };
    char volstat_buf[ 50 ] = { 0 }, secvolstat_buf[ 50 ] = { 0 };
    char boosts_buf[ 100 ] = { 0 }, selfboosts_buf[ 100 ] = { 0 }, secboost_buf[ 100 ] = { 0 },
                         secselfboost_buf[ 100 ] = { 0 };
    char flags_buf[ 500 ]                        = { 0 };
    char status_buf[ 50 ]                        = { 0 }, secstatus_buf[ 50 ]{ 0 };

    char critratio[ 20 ] = { 0 }, secchance[ 20 ] = { 0 };

    sscanf( p_buffer,
            "%hu,%hhu,%hhu,%[^,],%[^,],%[^,],%[^,],%hhu,%hhd,%[^,],%[^,],%[^,]"
            ",%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]"
            ",%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",
            &id, &res.m_accuracy, &res.m_basePower, damage_buf, cat_buf, defcat_buf, alt_id,
            &res.m_pp, &res.m_priority, weather_buf, flags_buf, terrain_buf, pseudoWeather_buf,
            selfboosts_buf, slotcon_buf, heal_buf, sidecond_buf, status_buf, recoil_buf,
            volstat_buf, prestg_buf, boosts_buf, secchance, secselfboost_buf, secboost_buf,
            secvolstat_buf, secstatus_buf, multihit_buf, critratio, drain_buf, target_buf, type_buf,
            contesttype_buf );

    /*
    printf( "%hu@ %hhu@ %hhu@ %s@ %s@ %s@ %s@ %hhu@ %hhd@ %s@ %s@ %s"
            "@ %s@ %s@ %s@ %s@ %s@ %s@ %s@ %s@ %s@ %s@ %hhu@ %s@ %s"
            "@ %s@ %s@ %s@ %s@ %s@ %s@ %s@ %s",
            id, res.m_accuracy, res.m_basePower, damage_buf, cat_buf, defcat_buf, alt_id,
            res.m_pp, res.m_priority, weather_buf, flags_buf, terrain_buf,
            pseudoWeather_buf, selfboosts_buf, slotcon_buf, heal_buf, sidecond_buf,
            status_buf, recoil_buf, volstat_buf, prestg_buf, boosts_buf,
            res.m_secondaryChance, secselfboost_buf, secboost_buf, secvolstat_buf, secstatus_buf,
            multihit_buf, critratio, drain_buf, target_buf, type_buf, contesttype_buf );
    */

    res.m_secondaryChance = getNumberOrNone( secchance );
    res.m_critRatio       = getNumberOrNone( critratio );

    alt_moves[ alt_id ] = id;

    res.m_type        = getType( type_buf );
    res.m_contestType = getContestType( contesttype_buf );

    res.m_category          = getMoveCategory( cat_buf );
    res.m_defensiveCategory = getMoveCategory( defcat_buf, res.m_category );

    res.m_weather       = getWeather( weather_buf );
    res.m_pseudoWeather = getPseudoWeather( pseudoWeather_buf );
    res.m_terrain       = getTerrain( terrain_buf );
    res.m_sideCondition = getSideCondition( sidecond_buf );

    res.m_slotCondition = getSlotCondition( slotcon_buf );
    res.m_fixedDamage   = getFixedDamage( damage_buf );
    res.m_target        = getTarget( target_buf );
    if( res.m_target == NO_TARGET ) { res.m_target = NORMAL; }
    res.m_pressureTarget = getTarget( prestg_buf );

    res.m_heal     = parseFraction( heal_buf );
    res.m_recoil   = parseFraction( recoil_buf );
    res.m_drain    = parseFraction( drain_buf );
    res.m_multiHit = parseMultiHit( multihit_buf );

    res.m_volatileStatus          = getVolatileStatus( volstat_buf );
    res.m_secondaryVolatileStatus = getVolatileStatus( secvolstat_buf );

    res.m_boosts              = parseBoosts( boosts_buf );
    res.m_selfBoosts          = parseBoosts( selfboosts_buf );
    res.m_secondaryBoosts     = parseBoosts( secboost_buf );
    res.m_secondarySelfBoosts = parseBoosts( secselfboost_buf );

    res.m_flags = parseMoveFlags( flags_buf );

    res.m_status          = getStatus( status_buf );
    res.m_secondaryStatus = getStatus( secstatus_buf );
    return res;
}

void readMoveData( char* p_moveData, vector<moveData>& p_out ) {
    FILE* f             = fopen( p_moveData, "r" );
    char  buffer[ 800 ] = { 0 };
    while( f && fgets( buffer, sizeof( buffer ), f ) ) p_out.push_back( parseMoveData( buffer ) );
    FINFO.m_maxMove = p_out.size( ) - 1;
    fclose( f );
}

const char* TYPE_NAMES[]
    = { "Normal",  "Fighting", "Flying", "Poison", "Ground", "Rock",  "Bug",
        "Ghost",   "Steel",    "???",    "Water",  "Fire",   "Grass", "Electric",
        "Psychic", "Ice",      "Dragon", "Dark",   "Fairy" };

const char* LEVEL_UP_TYPE_NAMES[]
    = { "Medium Fast", "Erratic", "Fluctuating", "Medium Slow", "Fast", "Slow" };

const char* EGG_GROUP_NAMES[] = {
    "None",       "Monster", "Water 1", "Bug",       "Flying",  "Field", "Fairy",  "Grass",
    "Human-like", "Water 3", "Mineral", "Amorphous", "Water 2", "Ditto", "Dragon", "Undiscovered" };

const char* GENDER_NAMES( u8 p_value ) {
    if( p_value >= 255 ) { return "genderless"; }
    if( p_value >= 254 ) { return "always female"; }
    if( p_value >= 223 ) { return "1m7f"; }
    if( p_value >= 191 ) { return "1m3f"; }
    if( p_value >= 127 ) { return "1m1f"; }
    if( p_value >= 63 ) { return "3m1f"; }
    if( p_value >= 31 ) { return "7m1f"; }
    return "always male";
}

const char* COLOR_NAMES[] = {
    "Red", "Blue", "Yellow", "Green", "Black", "Brown", "Purple", "Gray", "White", "Pink",
};

const char* SHAPE_NAMES[]
    = { "None",   "Pomaceous",    "Caudal",          "Ichthyic",      "Brachial",
        "Alvine", "Sciurine",     "Crural",          "Mensal",        "Alar",
        "Cilial", "Polycephalic", "Anthropomorphic", "Lepidopterous", "Chitinous" };

void dumpForme( FILE* p_f, const pkmnFormeData& p_data ) {
    if( p_data.m_types[ 0 ] != p_data.m_types[ 1 ] ) {
        fprintf( p_f, "    Types: [ %s, %s ]\n", TYPE_NAMES[ p_data.m_types[ 0 ] ],
                 TYPE_NAMES[ p_data.m_types[ 1 ] ] );
    } else {
        fprintf( p_f, "    Types: [ %s ]\n", TYPE_NAMES[ p_data.m_types[ 0 ] ] );
    }

    fprintf( p_f, "    Abilities:\n" );
    fprintf( p_f, "    - %s\n",
             p_data.m_abilities[ 0 ] ? ability_names[ p_data.m_abilities[ 0 ] ].m_name[ 0 ]
                                     : "None" );
    fprintf( p_f, "    - %s\n",
             p_data.m_abilities[ 1 ] ? ability_names[ p_data.m_abilities[ 1 ] ].m_name[ 0 ]
                                     : "None" );
    fprintf( p_f, "    - %s # (hidden)\n",
             p_data.m_abilities[ 2 ] ? ability_names[ p_data.m_abilities[ 2 ] ].m_name[ 0 ]
                                     : "None" );
    if( p_data.m_abilities[ 3 ] ) {
        fprintf( p_f, "    - %s # (unused)\n",
                 p_data.m_abilities[ 3 ] ? ability_names[ p_data.m_abilities[ 3 ] ].m_name[ 0 ]
                                         : "None" );
    }

    fprintf( p_f, "    Base Stats:\n" );
    fprintf( p_f, "    - HP: %d\n", p_data.m_bases[ 0 ] );
    fprintf( p_f, "    - Attack: %d\n", p_data.m_bases[ 1 ] );
    fprintf( p_f, "    - Defense: %d\n", p_data.m_bases[ 2 ] );
    fprintf( p_f, "    - Sp. Attack: %d\n", p_data.m_bases[ 3 ] );
    fprintf( p_f, "    - Sp. Defense: %d\n", p_data.m_bases[ 4 ] );
    fprintf( p_f, "    - Speed: %d\n", p_data.m_bases[ 5 ] );

    fprintf( p_f, "    EV Yield:\n" );
    fprintf( p_f, "    - HP: %d\n", p_data.m_evYield[ 0 ] );
    fprintf( p_f, "    - Attack: %d\n", p_data.m_evYield[ 1 ] );
    fprintf( p_f, "    - Defense: %d\n", p_data.m_evYield[ 2 ] );
    fprintf( p_f, "    - Sp. Attack: %d\n", p_data.m_evYield[ 3 ] );
    fprintf( p_f, "    - Sp. Defense: %d\n", p_data.m_evYield[ 4 ] );
    fprintf( p_f, "    - Speed: %d\n", p_data.m_evYield[ 5 ] );

    if( p_data.m_eggGroups >> 4 && p_data.m_eggGroups & 15 ) {
        fprintf( p_f, "    Egg Groups: [ %s, %s ]\n", EGG_GROUP_NAMES[ p_data.m_eggGroups >> 4 ],
                 EGG_GROUP_NAMES[ p_data.m_eggGroups & 15 ] );
    } else if( p_data.m_eggGroups >> 4 ) {
        fprintf( p_f, "    Egg Groups: [ %s ]\n", EGG_GROUP_NAMES[ p_data.m_eggGroups >> 4 ] );
    } else {
        fprintf( p_f, "    Egg Groups: [ %s ]\n", EGG_GROUP_NAMES[ p_data.m_eggGroups & 15 ] );
    }

    fprintf( p_f, "    Held Items:\n" );
    fprintf( p_f, "    - %s # 1%%\n",
             p_data.m_items[ 0 ] ? item_names[ p_data.m_items[ 0 ] ].m_name[ 0 ] : "None" );
    fprintf( p_f, "    - %s # 5%%\n",
             p_data.m_items[ 1 ] ? item_names[ p_data.m_items[ 1 ] ].m_name[ 0 ] : "None" );
    fprintf( p_f, "    - %s # 10%%\n",
             p_data.m_items[ 2 ] ? item_names[ p_data.m_items[ 2 ] ].m_name[ 0 ] : "None" );
    fprintf( p_f, "    - %s # 100%%\n",
             p_data.m_items[ 3 ] ? item_names[ p_data.m_items[ 3 ] ].m_name[ 0 ] : "None" );

    fprintf( p_f, "    Exp Yield: %d\n", p_data.m_expYield );
    fprintf( p_f, "    Gender Ratio: %s\n", GENDER_NAMES( p_data.m_genderRatio ) );
    fprintf( p_f, "    Size: %d # dm\n", p_data.m_size );
    fprintf( p_f, "    Weight: %d # hg\n", p_data.m_weight );
    fprintf( p_f, "    Color: %s\n", COLOR_NAMES[ p_data.m_colorShape >> 4 ] );
    fprintf( p_f, "    Shape: %s\n", SHAPE_NAMES[ p_data.m_colorShape & 15 ] );
}

void dumpEvolutions( FILE* p_f, const pkmnEvolveData& p_data ) {
    // TODO
}

struct bstinfo {
    u16 m_bstTotal;
    u16 m_pkmnidx;
    u8  m_pkmnForme;
    u8  m_evYield;

    constexpr auto operator<=>( const bstinfo& ) const = default;
};

const char* STAT_NAMES[] = { "HP", "Attack", "Defense", "Sp. Attack", "Sp. Defense", "Speed" };

void printPkmnData( ) {
    fs::create_directories( std::string( FSROOT "/PKMN_NAME/" ) );
    fs::create_directories( std::string( FSROOT "/PKMN_SPCS/" ) );
    fs::create_directories( std::string( FSROOT "/PKMN_DXTR/" ) );
    fs::create_directories( std::string( FSROOT "/BST_EV/" ) );
    fs::create_directories( std::string( OUT ) );

    size_t maxmovelearn = 0;

    FILE*             log = fopen( OUT "/bst_ev.log", "w" );
    std::set<bstinfo> infos[ 6 ];

    FILE* g  = fopen( OUT "/pokemonNames.h", "w" );
    FILE* gf = fopen( OUT "/pokemonFormes.h", "w" );
    fprintf( g, "#pragma once\n" );
    fprintf( gf, "#pragma once\n" );

    auto outf    = vector<FILE*>( );
    auto foutf   = vector<FILE*>( );
    auto dxtrf   = vector<FILE*>( );
    auto spcsf   = vector<FILE*>( );
    auto dataf   = fopen( FSROOT "/pkmn.datab", "wb" );
    auto fdataf  = fopen( FSROOT "/pkmnf.datab", "wb" );
    auto learnf  = fopen( FSROOT "/pkmn.learnset.datab", "wb" );
    auto flearnf = fopen( FSROOT "/pkmnf.learnset.datab", "wb" );
    auto evof    = fopen( FSROOT "/pkmn.evolve.datab", "wb" );
    auto fevof   = fopen( FSROOT "/pkmnf.evolve.datab", "wb" );
    assert( dataf );
    assert( fdataf );
    assert( learnf );
    assert( flearnf );
    assert( evof );
    assert( fevof );

    for( int j = 0; j < NUM_LANGUAGES; ++j ) {
        FILE* fo = fopen(
            ( std::string( FSROOT "/PKMN_NAME/pkmnname." ) + std::to_string( j ) + ".strb" )
                .c_str( ),
            "wb" );
        assert( fo );
        outf.push_back( fo );

        fo = fopen(
            ( std::string( FSROOT "/PKMN_NAME/pkmnfname." ) + std::to_string( j ) + ".strb" )
                .c_str( ),
            "wb" );
        assert( fo );
        foutf.push_back( fo );

        fo = fopen( ( std::string( FSROOT "/PKMN_SPCS/pkmnspcs." ) + std::to_string( j ) + ".strb" )
                        .c_str( ),
                    "wb" );
        assert( fo );
        spcsf.push_back( fo );

        fo = fopen( ( std::string( FSROOT "/PKMN_DXTR/pkmndxtr." ) + std::to_string( j ) + ".strb" )
                        .c_str( ),
                    "wb" );
        assert( fo );
        dxtrf.push_back( fo );
    }

    size_t fcnt = 0;

    fprintf( gf, "constexpr int formeIdx( unsigned short p_pkmnIdx, unsigned char p_forme ) {\n" );
    fprintf( gf, "    switch( p_pkmnIdx ) {\n" );
    fprintf( gf, "    default: return -1;\n" );
    for( size_t i = 0; i < pkmn_data.size( ); ++i ) {
        // print human-readable information
        FILE* pd = getFilePtr( OUT "/PKMN_DATA/", i, 0, ".data.yml" );
        assert( pd );
        FILE* ld = getFilePtr( OUT "/PKMN_LEARN/", i, 0, ".learnset.yml" );
        assert( ld );
        /*
           FILE* f = getFilePtr( FSROOT "/PKMN_DATA/", i, 2 );
           assert( f );
           FILE* n = getFilePtr( FSROOT "/PKMN_NAME/", i, 2, ".str" );
           assert( n );
           FILE* nn = getFilePtr( FSROOT "/PKMN_SPCS/", i, 2, ".str" );
           assert( nn );
           FILE* nd = getFilePtr( FSROOT "/PKMN_DXTR/", i, 2, ".str" );
           assert( nd );
           FILE* l = getFilePtr( FSROOT "/PKMN_LEARN/", i, 2, ".learnset.data" );
           assert( l );
           */
        fprintf( pd, "---\n" );
        fprintf( pd, "%04zu: # %s\n", i, pkmn_names[ i ].m_name[ 0 ] );
        fprintf( ld, "---\n" );
        fprintf( ld, "%04zu: # %s\n", i, pkmn_names[ i ].m_name[ 0 ] );

        assert( fwrite( &pkmn_data[ i ], sizeof( pkmnData ), 1, dataf ) );

        {
            u16 bstsum = 0;
            u8  evsum  = 0;
            for( u8 j = 0; j < 6; ++j ) {
                bstsum += pkmn_data[ i ].m_baseForme.m_bases[ j ];
                evsum += pkmn_data[ i ].m_baseForme.m_evYield[ j ];
            }
            for( u8 j = 0; j < 6; ++j ) {
                if( pkmn_data[ i ].m_baseForme.m_evYield[ j ] == evsum && evsum ) {
                    infos[ j ].insert(
                        bstinfo{ bstsum, u16( i ), 0, pkmn_data[ i ].m_baseForme.m_evYield[ j ] } );
                }
            }
        }

        fprintf( pd, "  Experience Type: %s\n",
                 LEVEL_UP_TYPE_NAMES[ pkmn_data[ i ].m_expTypeFormeCnt >> 5 ] );
        fprintf( pd, "  Egg Cycles: %d\n", pkmn_data[ i ].m_eggCycles );
        fprintf( pd, "  Catch Rate: %d\n", pkmn_data[ i ].m_catchrate );
        fprintf( pd, "  Base Friendship: %d\n", pkmn_data[ i ].m_baseFriend );
        fprintf( pd, "  Alternative Forms: %d\n", pkmn_data[ i ].m_expTypeFormeCnt & 31 );

        fprintf( pd, "  Forms:\n" );
        fprintf( pd, "  - 0:\n" );
        dumpForme( pd, pkmn_data[ i ].m_baseForme );

        for( int j = 0; j < NUM_LANGUAGES; ++j ) {
            assert( fwrite( pkmn_names[ i ].m_name[ j ], 1, 14, outf[ j ] ) );
            assert( fwrite( pkmn_species[ i ].m_name[ j ], 1, 30, spcsf[ j ] ) );
            assert( fwrite( pkmn_descrs[ i ].m_descr[ j ], 1, 200, dxtrf[ j ] ) );
        }

        maxmovelearn = max( maxmovelearn, pkmn_learnsets[ i ].size( ) );
        for( auto mvd : pkmn_learnsets[ i ] ) {
            assert( fwrite( &mvd.first, sizeof( u16 ), 1, learnf ) );
            assert( fwrite( &mvd.second, sizeof( u16 ), 1, learnf ) );
            fprintf( ld, "- %d: %s\n", mvd.first, move_names[ mvd.second ].m_name[ 0 ] );
        }

        u16 null = 0;
        for( size_t cnt = pkmn_learnsets[ i ].size( ); cnt < LEARNSET_SIZE; ++cnt ) {
            assert( fwrite( &null, sizeof( u16 ), 1, learnf ) );
            assert( fwrite( &null, sizeof( u16 ), 1, learnf ) );
        }

        auto edt = pkmnEvolveData( );
        if( pkmn_evolve.count( { i, 0 } ) ) { edt = pkmn_evolve[ { i, 0 } ]; }
        fwrite( &edt, sizeof( pkmnEvolveData ), 1, evof );

        /*
           fclose( f );
           fclose( n );
           fclose( nn );
           fclose( nd );
           fclose( l );
           */
        if( pkmn_data[ i ].m_expTypeFormeCnt & 31 ) {
            fprintf( gf, "    case %lu: {\n", i );
            fprintf( gf, "        switch( p_forme ) {\n" );
            fprintf( gf, "        default: return -1;\n" );
        }
        for( u8 forme = 1; forme <= ( pkmn_data[ i ].m_expTypeFormeCnt & 31 ); ++forme ) {
            // fprintf( stderr, "write %lu %hhu / %hhu\n", i, forme,
            //         pkmn_data[ i ].m_expTypeFormeCnt & 31);
            // FILE* f = getFilePtr( FSROOT "/PKMN_DATA/", i, 2, ".data", forme );
            // FILE* n = getFilePtr( FSROOT "/PKMN_NAME/", i, 2, ".str", forme );
            if( forme <= forme_data[ i ].size( ) ) {
                auto pdt        = pkmn_data[ i ];
                pdt.m_baseForme = forme_data[ i ][ forme - 1 ];
                assert( fwrite( &pdt, sizeof( pkmnData ), 1, fdataf ) );
                for( int j = 0; j < NUM_LANGUAGES; ++j ) {
                    assert(
                        fwrite( forme_names[ i ][ forme - 1 ].m_name[ j ], 1, 30, foutf[ j ] ) );
                }

                fprintf( pd, "  - %d: # %s\n", forme, forme_names[ i ][ forme - 1 ].m_name[ 0 ] );
                dumpForme( pd, forme_data[ i ][ forme - 1 ] );

                edt = pkmnEvolveData( );
                if( pkmn_evolve.count( { i, forme } ) ) { edt = pkmn_evolve[ { i, forme } ]; }
                fwrite( &edt, sizeof( pkmnEvolveData ), 1, fevof );

                fprintf( gf, "        case %hhu: return %lu;\n", forme, fcnt++ );

                auto ln   = pkmn_learnsets[ i ];
                bool prnt = false;
                if( forme_learnsets.count( { i, forme } ) ) {
                    ln = forme_learnsets[ { i, forme } ];
                    // printf( "Learnset %lu_%hhu (%s). %hu\n", i, forme,
                    //         forme_names[ i ][ forme - 1 ].m_name[ 0 ], fcnt - 1 );
                    //  prnt = true;
                } else {
                    printf( "Learnset %lu_%hhu (%s) does not exist.\n", i, forme,
                            forme_names[ i ][ forme - 1 ].m_name[ 0 ] );
                }

                {
                    u16 bstsum = 0;
                    u8  evsum  = 0;
                    for( u8 j = 0; j < 6; ++j ) {
                        bstsum += pdt.m_baseForme.m_bases[ j ];
                        evsum += pdt.m_baseForme.m_evYield[ j ];
                    }
                    for( u8 j = 0; j < 6; ++j ) {
                        if( pdt.m_baseForme.m_evYield[ j ] == evsum && evsum ) {
                            infos[ j ].insert( bstinfo{ bstsum, u16( i ), forme,
                                                        pdt.m_baseForme.m_evYield[ j ] } );
                        }
                    }
                }

                fprintf( ld, "---\n" );
                fprintf( ld, "%04zu-%d: # %s\n", i, forme,
                         forme_names[ i ][ forme - 1 ].m_name[ 0 ] );

                maxmovelearn = max( maxmovelearn, ln.size( ) );
                for( auto mvd : ln ) {
                    assert( fwrite( &mvd.first, sizeof( u16 ), 1, flearnf ) );
                    assert( fwrite( &mvd.second, sizeof( u16 ), 1, flearnf ) );
                    fprintf( ld, "- %d: %s\n", mvd.first, move_names[ mvd.second ].m_name[ 0 ] );
                    if( prnt ) {
                        printf( "   %s (%hx) at lv %hx\n", move_names[ mvd.second ].m_name[ 0 ],
                                mvd.second, mvd.first );
                    }
                }
                u16 null = 0;
                for( size_t cnt = ln.size( ); cnt < LEARNSET_SIZE; ++cnt ) {
                    assert( fwrite( &null, sizeof( u16 ), 1, flearnf ) );
                    assert( fwrite( &null, sizeof( u16 ), 1, flearnf ) );
                }

            } else {
                break;
                // fwrite( &pkmn_data[ i ], sizeof( pkmnData ), 1, f );
            }
            // fclose( f );
            // fclose( n );
        }
        if( pkmn_data[ i ].m_expTypeFormeCnt & 31 ) { fprintf( gf, "        }\n    }\n" ); }
        if( i && strcmp( pkmn_names[ i ].m_name[ 0 ], "???" ) ) {
            fprintf( g, "#define PKMN_" );
            char* s = pkmn_names[ i ].m_name[ 0 ];
            printNormalized( s, g );
            fprintf( g, " %lu\n", i );
        }

        fclose( pd );
        fclose( ld );
    }
    fprintf( gf, "}\n}\n" );
    fclose( g );
    fclose( gf );
    fclose( dataf );
    fclose( fdataf );
    fclose( learnf );
    fclose( flearnf );
    fclose( evof );
    fclose( fevof );

    for( u8 i = 0; i < 6; ++i ) {
        FILE* bstf = fopen(
            ( std::string( FSROOT ) + std::string( "/BST_EV/" ) + std::to_string( i ) + ".data" )
                .c_str( ),
            "w" );
        fprintf( log, "---\n" );
        fprintf( log, "%s\n", STAT_NAMES[ i ] );
        for( const auto& dt : infos[ i ] ) {
            auto [ bst, idx, fo, ev ] = dt;
            if( fo ) {
                fprintf( log, "- %s-%d # BST %d, EV %d\n", pkmn_names[ idx ].m_name[ 0 ], fo, bst,
                         ev );
            } else {
                fprintf( log, "- %s # BST %d, EV %d\n", pkmn_names[ idx ].m_name[ 0 ], bst, ev );
            }
            fwrite( &dt, 1, sizeof( bstinfo ), bstf );
        }
        fclose( bstf );
    }

    fclose( log );

    for( int j = 0; j < NUM_LANGUAGES; ++j ) {
        fclose( outf[ j ] );
        fclose( foutf[ j ] );
        fclose( dxtrf[ j ] );
        fclose( spcsf[ j ] );
    }

    fprintf( stderr, "Max learnset size %lu\n", maxmovelearn );
}

void printItemData( ) {
    FILE* g = fopen( OUT "/itemNames.h", "w" );
    fprintf( g, "#pragma once\n" );

    map<string, int> duplicates = map<string, int>( );

    fs::create_directories( std::string( FSROOT "/ITEM_NAME/" ) );
    fs::create_directories( std::string( FSROOT "/ITEM_DSCR/" ) );
    fs::create_directories( std::string( OUT ) );

    auto outf  = vector<FILE*>( );
    auto dscrf = vector<FILE*>( );
    auto dataf = fopen( FSROOT "/item.datab", "wb" );
    assert( dataf );

    for( int j = 0; j < NUM_LANGUAGES; ++j ) {
        FILE* fo = fopen(
            ( std::string( FSROOT "/ITEM_NAME/itemname." ) + std::to_string( j ) + ".strb" )
                .c_str( ),
            "wb" );
        assert( fo );
        outf.push_back( fo );

        fo = fopen( ( std::string( FSROOT "/ITEM_DSCR/itemdscr." ) + std::to_string( j ) + ".strb" )
                        .c_str( ),
                    "wb" );
        assert( fo );
        dscrf.push_back( fo );
    }

    for( size_t i = 0; i < item_names.size( ); ++i ) {
        //        if( !strcmp( item_names[ i ].m_name[ 0 ], "???" ) ) continue;

        //        FILE* f = getFilePtr( FSROOT "/ITEM_DATA/", i, 2 );
        //        assert( f );
        //        FILE* n = getFilePtr( FSROOT "/ITEM_NAME/", i, 2, ".str" );
        //        assert( n );
        //        FILE* ds = getFilePtr( FSROOT "/ITEM_DSCR/", i, 2, ".str" );
        //        assert( ds );
        assert( fwrite( &item_data[ i ], sizeof( itemData ), 1, dataf ) );
        for( int j = 0; j < NUM_LANGUAGES; ++j ) {
            assert( fwrite( item_names[ i ].m_name[ j ], 1, 20, outf[ j ] ) );
            assert( fwrite( item_descrs[ i ].m_descr[ j ], 1, 200, dscrf[ j ] ) );
        }
        //        fclose( f );
        //        fclose( n );
        //        fclose( ds );

        if( i && strcmp( item_names[ i ].m_name[ 0 ], "???" ) ) {
            fprintf( g, "#define I_" );
            char* s = item_names[ i ].m_name[ 0 ];
            printNormalized( s, g );

            if( duplicates.count( item_names[ i ].m_name[ 0 ] ) ) {
                fprintf( g, "%d %lu\n", duplicates[ item_names[ i ].m_name[ 0 ] ] + 1, i );
            } else {
                fprintf( g, " %lu\n", i );
            }
            duplicates[ item_names[ i ].m_name[ 0 ] ]++;
        }
    }
    fclose( g );
    fclose( dataf );
    for( int j = 0; j < NUM_LANGUAGES; ++j ) {
        fclose( outf[ j ] );
        fclose( dscrf[ j ] );
    }
}

void printAbilityData( ) {
    FILE* g = fopen( OUT "/abilityNames.h", "w" );
    fprintf( g, "#pragma once\n" );

    fs::create_directories( std::string( FSROOT "/ABTY_NAME/" ) );
    fs::create_directories( std::string( FSROOT "/ABTY_DSCR/" ) );
    fs::create_directories( std::string( OUT ) );

    auto outf  = vector<FILE*>( );
    auto dscrf = vector<FILE*>( );
    for( int j = 0; j < NUM_LANGUAGES; ++j ) {
        FILE* fo = fopen(
            ( std::string( FSROOT "/ABTY_NAME/abtyname." ) + std::to_string( j ) + ".strb" )
                .c_str( ),
            "wb" );
        assert( fo );
        outf.push_back( fo );

        fo = fopen( ( std::string( FSROOT "/ABTY_DSCR/abtydscr." ) + std::to_string( j ) + ".strb" )
                        .c_str( ),
                    "wb" );
        assert( fo );
        dscrf.push_back( fo );
    }

    for( size_t i = 0; i < ability_names.size( ); ++i ) {
        //        FILE* n = getFilePtr( FSROOT "/ABTY_NAME/", i, 2, ".str" );
        //        assert( n );
        //        FILE* ds = getFilePtr( FSROOT "/ABTY_DSCR/", i, 2, ".str" );
        //        assert( ds );
        for( int j = 0; j < NUM_LANGUAGES; ++j ) {
            assert( fwrite( ability_names[ i ].m_name[ j ], 1, 20, outf[ j ] ) );
            assert( fwrite( ability_descrs[ i ].m_descr[ j ], 1, 200, dscrf[ j ] ) );
        }
        //        fclose( n );
        //        fclose( ds );

        fprintf( g, "#define A_" );
        char* s = ability_names[ i ].m_name[ 0 ];
        printNormalized( s, g );
        fprintf( g, " %lu\n", i );
    }
    fclose( g );
    for( int j = 0; j < NUM_LANGUAGES; ++j ) {
        fclose( outf[ j ] );
        fclose( dscrf[ j ] );
    }
}

void printTrainerClassNames( ) {
    fs::create_directories( std::string( FSROOT "/TRNR_NAME/" ) );
    auto outf = vector<FILE*>( );
    for( int j = 0; j < NUM_LANGUAGES; ++j ) {
        FILE* fo = fopen(
            ( std::string( FSROOT "/TRNR_NAME/trnrname." ) + std::to_string( j ) + ".strb" )
                .c_str( ),
            "wb" );
        assert( fo );
        outf.push_back( fo );
    }

    for( size_t i = 0; i < class_names.size( ); ++i ) {
        //        FILE* n = getFilePtr( FSROOT "/TRNR_NAME/", i, 2, ".str" );
        //        assert( n );
        for( int j = 0; j < NUM_LANGUAGES; ++j ) {
            u8 shift = 0;
            if( class_names[ i ].m_name[ j ][ 0 ] == ' ' ) { shift = 1; }
            assert( fwrite( class_names[ i ].m_name[ j ] + shift, 1, 30, outf[ j ] ) );
        }
        //        fclose( n );
    }
    for( int j = 0; j < NUM_LANGUAGES; ++j ) { fclose( outf[ j ] ); }
}

void printMoveData( ) {
    fs::create_directories( std::string( FSROOT "/MOVE_NAME/" ) );
    fs::create_directories( std::string( FSROOT "/MOVE_DSCR/" ) );
    fs::create_directories( std::string( OUT ) );

    FILE* g = fopen( OUT "/moveNames.h", "w" );
    fprintf( g, "#pragma once\n" );
    map<string, int> duplicates = map<string, int>( );

    auto outf  = vector<FILE*>( );
    auto dscrf = vector<FILE*>( );
    auto dataf = fopen( FSROOT "/move.datab", "wb" );
    assert( dataf );
    for( int j = 0; j < NUM_LANGUAGES; ++j ) {
        FILE* fo = fopen(
            ( std::string( FSROOT "/MOVE_NAME/movename." ) + std::to_string( j ) + ".strb" )
                .c_str( ),
            "wb" );
        assert( fo );
        outf.push_back( fo );

        fo = fopen( ( std::string( FSROOT "/MOVE_DSCR/movedscr." ) + std::to_string( j ) + ".strb" )
                        .c_str( ),
                    "wb" );
        assert( fo );
        dscrf.push_back( fo );
    }

    for( size_t i = 0; i < move_names.size( ); ++i ) {
        /*
           FILE* f = getFilePtr( FSROOT "/MOVE_DATA/", i, 2 );
           assert( f );
           FILE* n = getFilePtr( FSROOT "/MOVE_NAME/", i, 2, ".str" );
           assert( n );
           FILE* ds = getFilePtr( FSROOT "/MOVE_DSCR/", i, 2, ".str" );
           assert( ds );
           */
        assert( fwrite( &move_data[ i ], sizeof( moveData ), 1, dataf ) );
        for( int j = 0; j < NUM_LANGUAGES; ++j ) {
            assert( fwrite( move_names[ i ].m_name[ j ], 1, 20, outf[ j ] ) );
            assert( fwrite( move_descrs[ i ].m_descr[ j ], 1, 200, dscrf[ j ] ) );
        }
        /*
           fclose( f );
           fclose( n );
           fclose( ds );
           */

        if( i && strcmp( move_names[ i ].m_name[ 0 ], "???" )
            && strcmp( move_names[ i ].m_name[ 0 ], "----" ) ) {
            fprintf( g, "#define M_" );
            char* s = move_names[ i ].m_name[ 0 ];
            printNormalized( s, g );
            if( duplicates.count( move_names[ i ].m_name[ 0 ] ) ) {
                fprintf( g, "%d %lu\n", duplicates[ move_names[ i ].m_name[ 0 ] ] + 1, i );
            } else {
                fprintf( g, " %lu\n", i );
            }
            duplicates[ move_names[ i ].m_name[ 0 ] ]++;
        }
    }
    fclose( g );
    fclose( dataf );
    for( int j = 0; j < NUM_LANGUAGES; ++j ) {
        fclose( outf[ j ] );
        fclose( dscrf[ j ] );
    }
}

void readMedicineData( char* p_buf, itemData& p_out ) {
    char tmp_buf[ 60 ];
    assert( sscanf( p_buf, "%*d,%[^,],%hu,%hu,%hu,", tmp_buf, &p_out.m_param1, &p_out.m_param2,
                    &p_out.m_param3 ) );
    p_out.m_effect = getMedicineEffect( tmp_buf );
}

void readItems( char* p_path, char* p_medicineData, char* p_formeChangeData, char* p_tmData,
                char* p_itemDataPath, vector<names>& p_out, vector<itemData>& p_itemData ) {
    FILE* f  = fopen( p_path, "r" );
    FILE* id = fopen( p_itemDataPath, "r" );
    FILE* m  = fopen( p_medicineData, "r" );
    FILE* fc = fopen( p_formeChangeData, "r" );
    FILE* tm = fopen( p_tmData, "r" );
    char  buffer[ 500 ];
    char* t1;

    char data_buf[ 200 ] = { 0 };
    assert( fgets( data_buf, sizeof( data_buf ), id ) );
    char med_buf[ 200 ] = { 0 };
    assert( fgets( med_buf, sizeof( med_buf ), m ) );
    char forme_buf[ 200 ] = { 0 };
    assert( fgets( forme_buf, sizeof( forme_buf ), fc ) );
    char tm_buf[ 200 ] = { 0 };
    assert( fgets( tm_buf, sizeof( tm_buf ), tm ) );
    while( fgets( buffer, sizeof( buffer ), f ) ) {
        t1 = strtok( buffer, "," );
        names n;
        for( int i = 0; i < NUM_LANGUAGES; ++i ) {
            n.m_name[ i ] = new char[ 40 ];
            std::memset( n.m_name[ i ], 0, 40 );
        }
        size_t id_a;
        sscanf( t1, "%lu", &id_a );

        t1           = strtok( NULL, "," );
        itemData t   = { 0 };
        t.m_itemType = getItemType( t1 );
        size_t id_b;
        sscanf( data_buf, "%lu,%*[^,],%hu,", &id_b, &t.m_sellPrice );
        assert( id_a == id_b );
        assert( fgets( data_buf, sizeof( data_buf ), id ) );

        if( ( t.m_itemType & 15 ) == 2 ) { // Medicine
            if( m ) {
                sscanf( med_buf, "%lu", &id_b );
                assert( id_a == id_b );

                readMedicineData( med_buf, t );
                assert( fgets( med_buf, sizeof( med_buf ), m ) );
            } else {
                fprintf( stderr, "[%lu] No medicine data\n", id_a );
            }
        } else if( t.m_itemType == 8 ) { // Forme Change
            if( fc ) {
                sscanf( forme_buf, "%lu,%*u,%hu,%hu,%*u,", &id_b, &t.m_param1,
                        &t.m_param2 ); // (unused), pkmn_id, target forme, (unused)
                assert( id_a == id_b );
                assert( fgets( forme_buf, sizeof( forme_buf ), fc ) );
            } else {
                fprintf( stderr, "[%lu] No formeChange item data\n", id_a );
            }
        } else if( t.m_itemType == 12 ) { // TM/HM
            if( fc ) {
                char movename[ 50 ] = { 0 };
                sscanf( tm_buf, "%lu,%hhu,%hu,%[^,],%*u,", &id_b, &t.m_effect, &t.m_param1,
                        movename ); // type (0: hm, 1: tm, 2: tr), number, move name, (unused)
                assert( id_a == id_b );
                if( moves.count( movename ) ) {
                    t.m_param2 = moves[ movename ];
                } else {
                    fprintf( stderr, "[%lu] Unknown move %s.\n", id_a, movename );
                }
                assert( fgets( tm_buf, sizeof( tm_buf ), tm ) );
            } else {
                fprintf( stderr, "[%lu] No tm data\n", id_a );
            }
        }

        int cnt = 0;
        while( cnt < NUM_LANGUAGES && ( t1 = strtok( NULL, "," ) ) ) {
            strncpy( n.m_name[ cnt++ ], fixEncoding( t1 ), 29 );
        }
        p_out.push_back( n );
        p_itemData.push_back( t );
    }
    fclose( f );
    fclose( m );

    FINFO.m_maxItem = p_out.size( ) - 1;
    fprintf( stderr, "read %lu objects from %s\n", p_out.size( ), p_path );
}

void readForme( char* p_buf, pkmnFormeData& p_out ) {
    char tmp_buf[ 50 ] = { 0 }, tmp_buf2[ 50 ] = { 0 }, *tmp_buf3[ 3 ] = { 0 },
                     tmp_buf5[ 50 ] = { 0 }, tmp_buf6[ 50 ] = { 0 };
    char tmp_buf7[ 50 ] = { 0 }, tmp_buf8[ 50 ] = { 0 }, tmp_buf9[ 50 ] = { 0 },
                      tmp_buf10[ 50 ] = { 0 }, *tmp_buf11[ 50 ];
    for( int j = 0; j < 3; ++j ) tmp_buf3[ j ] = new char[ 50 ];
    for( int j = 0; j < 4; ++j ) tmp_buf11[ j ] = new char[ 50 ];

    float sz, wt;
    assert( sscanf( p_buf,
                    "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%hhu,%hhu,"
                    "%hhu,%hhu,%hhu,%hhu,%hu,%[^,],%f m,%f kg,%[^,],%[^,],%hhu,%hhu,%hhu,%hhu,%hhu,"
                    "%hhu,%[^,],%[^,],%[^,],%[^,],",
                    tmp_buf5, tmp_buf, tmp_buf2, tmp_buf3[ 0 ], tmp_buf3[ 1 ], tmp_buf3[ 2 ],
                    tmp_buf6, tmp_buf7, &p_out.m_bases[ 0 ], &p_out.m_bases[ 1 ],
                    &p_out.m_bases[ 2 ], &p_out.m_bases[ 3 ], &p_out.m_bases[ 4 ],
                    &p_out.m_bases[ 5 ], &p_out.m_expYield, tmp_buf8, &sz, &wt, tmp_buf9, tmp_buf10,
                    &p_out.m_evYield[ 0 ], &p_out.m_evYield[ 1 ], &p_out.m_evYield[ 2 ],
                    &p_out.m_evYield[ 3 ], &p_out.m_evYield[ 4 ], &p_out.m_evYield[ 5 ],
                    tmp_buf11[ 0 ], tmp_buf11[ 1 ], tmp_buf11[ 2 ], tmp_buf11[ 3 ] ) );

    p_out.m_types[ 0 ] = getType( tmp_buf );
    p_out.m_types[ 1 ] = getType( tmp_buf2 );
    // printf( "%lu %s %s got %hhu\n", i, tmp_buf, tmp_buf2, cur.m_baseForme.m_types );
    for( size_t j = 0; j < 3; ++j ) {
        if( abilities.count( tmp_buf3[ j ] ) )
            p_out.m_abilities[ j ] = abilities[ tmp_buf3[ j ] ];
        else if( strcmp( tmp_buf3[ j ], "none" ) ) {
            fprintf( stderr, "[%s] ability %lu \"%s\" unknown\n", tmp_buf5, j, tmp_buf3[ j ] );
        }
        delete[] tmp_buf3[ j ];
    }
    p_out.m_eggGroups   = ( getEggGroup( tmp_buf6 ) << 4 ) | getEggGroup( tmp_buf7 );
    p_out.m_genderRatio = getGender( tmp_buf8 );
    p_out.m_size        = (u8) ( sz * 10 );
    p_out.m_weight      = (u16) ( wt * 10 );
    p_out.m_colorShape  = ( getColor( tmp_buf9 ) << 4 ) | getShape( tmp_buf10 );

    for( size_t j = 0; j < 3; ++j ) {
        if( items.count( tmp_buf11[ j ] ) )
            p_out.m_items[ j ] = items[ tmp_buf11[ j ] ];
        else if( strcmp( tmp_buf11[ j ], "none" ) )
            fprintf( stderr, "[%s] item %lu \"%s\" unknown\n", tmp_buf5, j, tmp_buf11[ j ] );
        delete[] tmp_buf11[ j ];
    }
}

void readPkmnData( char* p_pkmnData, char* p_pkmnDescr, char* p_pkmnFormeNames,
                   char* p_pkmnFormeDescr, vector<pkmnData>& p_out,
                   vector<vector<names>>&         p_formeNameOut,
                   vector<vector<pkmnFormeData>>& p_formeOut ) {
    FILE* pdata = fopen( p_pkmnData, "r" );
    FILE* pdesc = fopen( p_pkmnDescr, "r" );

    FILE* fdata             = fopen( p_pkmnFormeNames, "r" );
    FILE* fdesc             = fopen( p_pkmnFormeDescr, "r" );
    char  fdata_buf[ 1000 ] = { 0 }, fdescr_buf[ 1000 ] = { 0 };
    assert( fgets( fdata_buf, sizeof( fdata_buf ), fdata ) );
    assert( fgets( fdescr_buf, sizeof( fdescr_buf ), fdesc ) );

    for( size_t i = 0; i <= FINFO.m_maxPkmn; ++i ) {
        // fprintf( stderr, "reading data %lu\n", i );
        char data_buf[ 1000 ] = { 0 }, descr_buf[ 1000 ] = { 0 };
        assert( fgets( data_buf, sizeof( data_buf ), pdata ) );
        assert( fgets( descr_buf, sizeof( descr_buf ), pdesc ) );

        pkmnData cur    = { 0 };
        cur.m_baseForme = { 0 };
        int  id_a, id_b;
        char tmp_buf[ 50 ];
        u8   tmp1;
        assert( sscanf( data_buf, "%d,%[^,],%hhu,%hhu,%hhu,%hhu", &id_a, tmp_buf, &cur.m_eggCycles,
                        &cur.m_catchrate, &cur.m_baseFriend, &tmp1 ) );

        assert( sscanf( descr_buf, "%d", &id_b ) );
        assert( id_a == id_b );
        readForme( descr_buf, cur.m_baseForme );

        // Check for existing forms
        u8  forms_found = 0;
        int cur_formbase, cur_formid;
        sscanf( fdescr_buf, "%d_%d", &cur_formbase, &cur_formid );
        vector<names>         fnames;
        vector<pkmnFormeData> fdatas;
        while( cur_formbase == id_a ) {
            names         n  = pkmn_names[ id_a ], n2;
            pkmnFormeData pf = cur.m_baseForme;
            while( cur_formid > forms_found + 1 ) {
                fnames.push_back( n );
                fdatas.push_back( pf );
                forms_found++;
            }
            for( int i = 0; i < NUM_LANGUAGES; ++i ) {
                n2.m_name[ i ] = new char[ 40 ];
                std::memset( n2.m_name[ i ], 0, 40 );
            }

            char* t1  = strtok( fdata_buf, "," );
            int   cnt = 0;
            while( cnt < NUM_LANGUAGES && ( t1 = strtok( NULL, "," ) ) ) {
                strncpy( n2.m_name[ cnt++ ], t1, 29 );
            }

            readForme( fdescr_buf, pf );
            fnames.push_back( n2 );
            fdatas.push_back( pf );
            if( !fgets( fdata_buf, sizeof( fdata_buf ), fdata ) ) break;
            assert( fgets( fdescr_buf, sizeof( fdescr_buf ), fdesc ) );
            sscanf( fdescr_buf, "%d_%d", &cur_formbase, &cur_formid );
            ++forms_found;
        }
        while( forms_found < tmp1 ) {
            fnames.push_back( pkmn_names[ id_a ] );
            fdatas.push_back( cur.m_baseForme );
            forms_found++;
        }
        p_formeNameOut.push_back( fnames );
        p_formeOut.push_back( fdatas );

        cur.m_expTypeFormeCnt = ( getExpType( tmp_buf ) << 5 ) | max( tmp1, forms_found );
        p_out.push_back( cur );
    }
    fprintf( stderr, "read %lu pkmndata\n", p_out.size( ) );
}

int main( int p_argc, char** p_argv ) {
    if( p_argc < 24 ) {
        fprintf( stderr, "too few args." );
        return 1;
    }

    // pkmnnames abtynames movenames itemnames pkmndata pkmndescr pkmnformnames
    // pkmnformdescr

    FINFO = fsdataInfo{ };
    readNames( p_argv[ 1 ], pkmn_names );
    FINFO.m_maxPkmn = pkmn_names.size( ) - 1;

    readNames( p_argv[ 17 ], pkmn_species );
    readDescrs( p_argv[ 18 ], pkmn_descrs, 199 );
    for( size_t i = 0; i < pkmn_names.size( ); ++i ) pkmns[ pkmn_names[ i ].m_name[ 0 ] ] = i;
    readNames( p_argv[ 2 ], ability_names );
    readDescrs( p_argv[ 14 ], ability_descrs, 199 );

    for( size_t i = 0; i < ability_names.size( ); ++i )
        abilities[ ability_names[ i ].m_name[ 0 ] ] = i;
    readNames( p_argv[ 3 ], move_names );
    for( size_t i = 0; i < move_names.size( ); ++i ) moves[ move_names[ i ].m_name[ 0 ] ] = i;
    readDescrs( p_argv[ 15 ], move_descrs, 199 );

    readItems( p_argv[ 4 ], p_argv[ 9 ], p_argv[ 10 ], p_argv[ 11 ], p_argv[ 19 ], item_names,
               item_data );
    for( size_t i = 0; i < item_names.size( ); ++i ) items[ item_names[ i ].m_name[ 0 ] ] = i;
    readDescrs( p_argv[ 16 ], item_descrs, 199 );

    readNames( p_argv[ 20 ], class_names );
    for( auto i : class_names ) classes[ i.second.m_name[ 0 ] ] = i.first;

    readMoveData( p_argv[ 12 ], move_data );
    readPkmnData( p_argv[ 5 ], p_argv[ 6 ], p_argv[ 7 ], p_argv[ 8 ], pkmn_data, forme_names,
                  forme_data );
    readLearnsetData( p_argv[ 13 ], pkmn_learnsets );
    readFormeLearnsetData( p_argv[ 23 ], forme_learnsets );

    readNames( p_argv[ 22 ], location_names );
    for( auto i : location_names ) locations[ i.second.m_name[ 0 ] ] = i.first;

    readEvolutionData( p_argv[ 21 ], pkmn_evolve );

    printTrainerClassNames( );
    printPkmnData( );
    printItemData( );
    printAbilityData( );
    printMoveData( );

    FILE* f = fopen( FSROOT "/fsinfo", "wb" );
    if( f ) {
        fwrite( &FINFO, sizeof( fsdataInfo ), 1, f );
        fclose( f );
    }
}
