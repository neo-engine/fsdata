#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include "fsdata.h"
#include "wonderCard.h"

string FILENAME;

map<pair<u16, u8>, pkmnEvolveData> pkmn_evolve;

map<u16, names>  class_names;
map<string, int> classes;

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

map<string, int> known_keys = {
    { "description id", 1 },
    { "target game version", 2 },
    { "type", 3 },
    { "id", 4 },
    { "title", 5 },
    { "item1 name", 6 },
    { "item1 count", 7 },
    { "item2 name", 8 },
    { "item2 count", 9 },
    { "item3 name", 10 },
    { "item3 count", 11 },
    { "pkmn move1", 12 },
    { "pkmn move2", 13 },
    { "pkmn move3", 14 },
    { "pkmn move4", 15 },
    { "pkmn species", 16 },
    { "pkmn name", 17 },
    { "pkmn level", 18 },
    { "pkmn id", 19 },
    { "pkmn sid", 20 },
    { "pkmn ot", 21 },
    { "pkmn shiny", 22 },
    { "pkmn hidden ability", 23 },
    { "pkmn fateful", 24 },
    { "pkmn is egg", 25 },
    { "pkmn got place", 26 },
    { "pkmn gender", 27 },
    { "pkmn ball", 28 },
    { "pkmn poke ball", 28 },
    { "pkmn pokerus", 29 },
    { "pkmn form", 30 },
    { "pkmn forme", 30 },
    { "pkmn ribbons", 31 },
    { "pkmn ribbon", 31 },
    { "pkmn items", 32 },
    { "pkmn item", 32 },
};

std::string types[ 3 ] = {
    "none",
    "item",
    "pkmn",
};

wcEventType parseType( char* p_buffer ) {
    if( !strcmp( p_buffer, "item" ) ) { return WCTYPE_ITEM; }
    if( !strcmp( p_buffer, "pkmn" ) ) { return WCTYPE_PKMN; }

    return WCTYPE_NONE;
}

void parseLine( wonderCard& p_out, char* p_buffer ) {
    if( p_buffer[ 0 ] == '#' || !p_buffer[ 0 ] || p_buffer[ 0 ] == '\n' ) { return; }

    char* t1 = strrchr( p_buffer, '\n' );
    *t1      = 0;
    // split line at first colon
    t1  = strrchr( p_buffer, ':' );
    *t1 = 0;
    ++t1;
    while( *t1 == ' ' ) { ++t1; }

    switch( known_keys[ string( p_buffer ) ] ) {
    case 1: {
        sscanf( t1, "%hhu", &p_out.m_descriptionId );
        printf( "description id: %i\n", p_out.m_descriptionId );
        return;
    }
    case 2: {
        sscanf( t1, "%hhu", &p_out.m_targetGameVersion );
        printf( "target game version: %i\n", p_out.m_targetGameVersion );
        return;
    }
    case 3: {
        p_out.m_type = parseType( t1 );
        printf( "type: %s\n", types[ p_out.m_type ].c_str( ) );
        return;
    }
    case 4: {
        sscanf( t1, "%hhu", &p_out.m_id );
        printf( "id: %i\n", p_out.m_id );
        return;
    }
    case 5: {
        strncpy( p_out.m_title, t1, 95 );
        printf( "title: %s\n", p_out.m_title );
        return;
    }
    case 6: {
        p_out.m_data.m_item.m_itemId[ 0 ] = items[ std::string( t1 ) ];
        printf( "item1 name: %s\n", item_names[ p_out.m_data.m_item.m_itemId[ 0 ] ].m_name[ 0 ] );
        return;
    }
    case 7: {
        sscanf( t1, "%hu", &p_out.m_data.m_item.m_itemCount[ 0 ] );
        printf( "item1 count: %i\n", p_out.m_data.m_item.m_itemCount[ 0 ] );
        return;
    }
    case 8: {
        p_out.m_data.m_item.m_itemId[ 1 ] = items[ std::string( t1 ) ];
        printf( "item2 name: %s\n", item_names[ p_out.m_data.m_item.m_itemId[ 1 ] ].m_name[ 0 ] );
        return;
    }
    case 9: {
        sscanf( t1, "%hu", &p_out.m_data.m_item.m_itemCount[ 1 ] );
        printf( "item2 count: %i\n", p_out.m_data.m_item.m_itemCount[ 1 ] );
        return;
    }
    case 10: {
        p_out.m_data.m_item.m_itemId[ 2 ] = items[ std::string( t1 ) ];
        printf( "item3 name: %s\n", item_names[ p_out.m_data.m_item.m_itemId[ 2 ] ].m_name[ 0 ] );
        return;
    }
    case 11: {
        sscanf( t1, "%hu", &p_out.m_data.m_item.m_itemCount[ 2 ] );
        printf( "item3 count: %i\n", p_out.m_data.m_item.m_itemCount[ 2 ] );
        return;
    }
    case 12: {
        p_out.m_data.m_pkmn.m_moves[ 0 ] = moves[ std::string( t1 ) ];
        printf( "pkmn move1: %s\n", move_names[ p_out.m_data.m_pkmn.m_moves[ 0 ] ].m_name[ 0 ] );
        return;
    }
    case 13: {
        p_out.m_data.m_pkmn.m_moves[ 1 ] = moves[ std::string( t1 ) ];
        printf( "pkmn move2: %s\n", move_names[ p_out.m_data.m_pkmn.m_moves[ 1 ] ].m_name[ 0 ] );
        return;
    }
    case 14: {
        p_out.m_data.m_pkmn.m_moves[ 2 ] = moves[ std::string( t1 ) ];
        printf( "pkmn move3: %s\n", move_names[ p_out.m_data.m_pkmn.m_moves[ 2 ] ].m_name[ 0 ] );
        return;
    }
    case 15: {
        p_out.m_data.m_pkmn.m_moves[ 3 ] = moves[ std::string( t1 ) ];
        printf( "pkmn move4: %s\n", move_names[ p_out.m_data.m_pkmn.m_moves[ 3 ] ].m_name[ 0 ] );
        return;
    }
    case 16: {
        p_out.m_data.m_pkmn.m_species = pkmns[ std::string( t1 ) ];
        printf( "pkmn species: %s\n", pkmn_names[ p_out.m_data.m_pkmn.m_species ].m_name[ 0 ] );
        return;
    }
    case 17: {
        if( !strcmp( t1, "none" ) ) {
            p_out.m_data.m_pkmn.m_name[ 0 ] = 0;
            printf( "pkmn name: none\n" );
        } else {
            strncpy( p_out.m_data.m_pkmn.m_name, t1, 13 );
            printf( "pkmn name: %s\n", p_out.m_data.m_pkmn.m_name );
        }
        return;
    }
    case 18: {
        sscanf( t1, "%hu", &p_out.m_data.m_pkmn.m_level );
        if( p_out.m_data.m_pkmn.m_level > 100 ) { p_out.m_data.m_pkmn.m_level = 100; }
        printf( "pkmn level: %i\n", p_out.m_data.m_pkmn.m_level );
        return;
    }
    case 19: {
        sscanf( t1, "%hu", &p_out.m_data.m_pkmn.m_id );
        printf( "pkmn id: %i\n", p_out.m_data.m_pkmn.m_id );
        return;
    }
    case 20: {
        sscanf( t1, "%hu", &p_out.m_data.m_pkmn.m_sid );
        printf( "pkmn sid: %i\n", p_out.m_data.m_pkmn.m_sid );
        return;
    }
    case 21: {
        if( !strcmp( t1, "none" ) ) {
            p_out.m_data.m_pkmn.m_oT[ 0 ] = 0;
            printf( "pkmn ot: none\n" );
        } else {
            strncpy( p_out.m_data.m_pkmn.m_oT, t1, 7 );
            printf( "pkmn ot: %s\n", p_out.m_data.m_pkmn.m_oT );
        }
        return;
    }
    case 22: {
        sscanf( t1, "%hhu", &p_out.m_data.m_pkmn.m_shiny );
        printf( "pkmn shiny: %i\n", p_out.m_data.m_pkmn.m_shiny );
        return;
    }
    case 23: {
        sscanf( t1, "%hhu", &p_out.m_data.m_pkmn.m_hiddenAbility );
        printf( "pkmn hidden ability: %i\n", p_out.m_data.m_pkmn.m_hiddenAbility );
        return;
    }
    case 24: {
        sscanf( t1, "%hhu", &p_out.m_data.m_pkmn.m_fatefulEncounter );
        p_out.m_data.m_pkmn.m_fatefulEncounter = !!p_out.m_data.m_pkmn.m_fatefulEncounter;
        printf( "pkmn fateful: %i\n", p_out.m_data.m_pkmn.m_fatefulEncounter );
        return;
    }
    case 25: {
        sscanf( t1, "%hhu", &p_out.m_data.m_pkmn.m_isEgg );
        p_out.m_data.m_pkmn.m_isEgg = !!p_out.m_data.m_pkmn.m_isEgg;
        printf( "pkmn is egg: %i\n", p_out.m_data.m_pkmn.m_isEgg );
        return;
    }
    case 26: {
        p_out.m_data.m_pkmn.m_gotPlace = 0;
        return;
    }
    case 27: {
        p_out.m_data.m_pkmn.m_female = 0;
        return;
    }
    case 28: {
        p_out.m_data.m_pkmn.m_ball = 0;
        return;
    }
    case 29: {
        sscanf( t1, "%hhu", &p_out.m_data.m_pkmn.m_pokerus );
        p_out.m_data.m_pkmn.m_pokerus = !!p_out.m_data.m_pkmn.m_pokerus;
        printf( "pkmn pokerus: %i\n", p_out.m_data.m_pkmn.m_pokerus );
        return;
    }
    case 30: {
        sscanf( t1, "%hhu", &p_out.m_data.m_pkmn.m_forme );
        p_out.m_data.m_pkmn.m_forme = !!p_out.m_data.m_pkmn.m_forme;
        printf( "pkmn form: %i\n", p_out.m_data.m_pkmn.m_forme );
        return;
    }
    case 31: {
        p_out.m_data.m_pkmn.m_ribbons[ 0 ] = 0;
        return;
    }
    case 32: {
        char* t2  = strtok( t1, "," );
        auto  cnt = 0;
        printf( "pkmn items:" );
        do {
            p_out.m_data.m_pkmn.m_items[ cnt ] = items[ std::string( t2 ) ];
            printf( " %s,", item_names[ p_out.m_data.m_pkmn.m_items[ cnt ] ].m_name[ 0 ] );
            t2 = strtok( NULL, "," );
            cnt++;
        } while( cnt < 4 && t2 );
        printf( "\n" );
        return;
    }

    default: return;
    }
}

int main( int p_argc, char** p_argv ) {
    FILENAME = string( p_argv[ 0 ] );

    if( p_argc < 6 ) {
        fprintf( stderr, "too few args." );
        return 1;
    }
    readNames( p_argv[ 1 ], pkmn_names );
    for( size_t i = 0; i < pkmn_names.size( ); ++i ) pkmns[ pkmn_names[ i ].m_name[ 0 ] ] = i;

    readNames( p_argv[ 2 ], move_names );
    for( size_t i = 0; i < move_names.size( ); ++i ) moves[ move_names[ i ].m_name[ 0 ] ] = i;

    readNames( p_argv[ 3 ], item_names, 29, 1 );
    for( size_t i = 0; i < item_names.size( ); ++i ) { items[ item_names[ i ].m_name[ 0 ] ] = i; }

    items[ "Cherish Ball" ] = items[ "Infinity Ball" ];

    FILE* f = fopen( p_argv[ 4 ], "r" );
    if( !f ) {
        fprintf( stderr, "input file unreadable" );
        return 1;
    }

    // fs::create_directories( std::string( p_argv[ 5 ] ) );

    wonderCard result{ };

    char buffer[ 200 ];
    while( f && fgets( buffer, sizeof( buffer ), f ) ) { parseLine( result, buffer ); }
    fclose( f );

    auto outf = fopen( p_argv[ 5 ], "wb" );
    assert( outf );
    fwrite( &result, 1, sizeof( wonderCard ), outf );
    fclose( outf );
}
