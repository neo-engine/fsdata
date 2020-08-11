#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include "fsdata.h"

map<pair<u16, u8>, pkmnEvolveData> pkmn_evolve;

map<u16, names>  location_names;
map<string, int> locations;

map<string, int> abilities;
vector<names>    ability_names;

map<string, int> items;
vector<names>    item_names;

map<string, int> moves;
map<string, int> alt_moves; // alternative move names
vector<names>    move_names;

map<string, int>      pkmns;
vector<names>         pkmn_names;
vector<vector<names>> forme_names;

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

        // Compute pre-evo (it's slow, but I'm lazy)

        cur.m_preEvolution = 0;
        for( auto q : edata ) {
            for( auto j : q.second ) {
                if( pair( j.m_target, j.m_targetForme ) == i.first ) {
                    cur.m_preEvolution = q.first.first;
                    break;
                }
            }
        }

        p_out[ i.first ] = cur;
    }

    // Check for pkmn with a pre-evo but no evo
    for( u16 i = 0; i <= MAX_PKMN; ++i ) {
        if( !p_out.count( pair( i, 0 ) ) ) {
            pkmnEvolveData cur   = pkmnEvolveData( );
            cur.m_evolutionCount = 0;
            cur.m_preEvolution   = 0;
            for( auto q : edata ) {
                for( auto j : q.second ) {
                    if( j.m_target == i && !j.m_targetForme ) {
                        cur.m_preEvolution = q.first.first;
                        break;
                    }
                }
            }
            if( cur.m_preEvolution ) { p_out[ pair( i, 0 ) ] = cur; }
        }
    }

    fprintf( stderr, "read %lu objects from %s\n", p_out.size( ), p_path );
}

void printEvolutionData( ) {
    for( auto i : pkmn_evolve ) {
        FILE* f = getFilePtr( FSROOT "/PKMN_EVOS/", i.first.first, 2, ".evo.data", i.first.second );
        assert( f );
        fwrite( &i.second, sizeof( pkmnEvolveData ), 1, f );
        fclose( f );
    }
}

int main( int p_argc, char** p_argv ) {
    if( p_argc < 7 ) {
        fprintf( stderr, "too few args." );
        return 1;
    }
    readNames( p_argv[ 1 ], pkmn_names );
    for( size_t i = 0; i < pkmn_names.size( ); ++i ) pkmns[ pkmn_names[ i ].m_name[ 0 ] ] = i;
    readNames( p_argv[ 2 ], ability_names );
    for( size_t i = 0; i < ability_names.size( ); ++i )
        abilities[ ability_names[ i ].m_name[ 0 ] ] = i;
    readNames( p_argv[ 3 ], move_names );
    for( size_t i = 0; i < move_names.size( ); ++i ) moves[ move_names[ i ].m_name[ 0 ] ] = i;

    readNames( p_argv[ 4 ], item_names, 29, 1 );
    for( size_t i = 0; i < item_names.size( ); ++i ) { items[ item_names[ i ].m_name[ 0 ] ] = i; }

    readNames( p_argv[ 5 ], location_names );
    for( auto i : location_names ) locations[ i.second.m_name[ 0 ] ] = i.first;

    readEvolutionData( p_argv[ 6 ], pkmn_evolve );

    printEvolutionData( );
}
