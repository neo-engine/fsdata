// Arguments
// pkmnnames.csv abtynames.csv movenames.csv itemnames.csv pkmndata.csv pkmndescr.csv
// pkmnformnames.csv pkmnformes.csv itemdata_medicine.csv

%:include <cstdio>
%:include <cstring>
%:include <string>
%:include <map>
%:include <vector>
%:include <filesystem>
%:include <cassert>
%:include <map>
%:include <algorithm>

%:include "fsdata.h"

map<string, int>    abilities;
vector<names>       ability_names;
vector<descrs>      ability_descrs;

map<string, int>    items;
vector<names>       item_names;
vector<itemData>    item_data;

map<string, int>    moves;
map<string, int>    alt_moves; // alternative move names
vector<names>       move_names;
vector<moveData>    move_data;
vector<descrs>      move_descrs;

map<string, int>    pkmns;
vector<names>       pkmn_names;
vector<vector<names>> forme_names;

vector<pkmnLearnsetData> pkmn_learnsets;
vector<pkmnLearnsetData> forme_learnsets;

vector<pkmnData> pkmn_data;
vector<vector<pkmnFormeData>> forme_data;

pair<u16, pkmnLearnsetData> parseLearnset( char* p_buffer ) {
    char* p = strtok( p_buffer, "," );
    auto res = pkmnLearnsetData( );

    if( !pkmns.count( string( fixEncoding( p ) ) ) ) {
        fprintf( stderr, "Unknown Pokémon %s\n", p );
        return { 0, res };
    }

    u16 pkmn = pkmns[ string( p ) ];

    while( ( p = strtok( NULL, "," ) ) ) {
        if( !strcmp( p, "\n" ) ) break;

        char mvname[ 50 ];
        u16 level, mid;
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

void readLearnsetData( char* p_learnsetData, vector<pkmnLearnsetData>& p_out ) {
    FILE* f = fopen( p_learnsetData, "r" );
    char buffer[ 6000 ];
    p_out.assign( pkmn_data.size( ), { } );
    while( f && fgets( buffer, sizeof( buffer ), f ) ) {
        auto tmp = parseLearnset( buffer );
        assert( tmp.first < p_out.size( ) );
        p_out[ tmp.first ] = tmp.second;
    }
    fclose( f );
}

moveData parseMoveData( char* p_buffer ) {
    // printf( "parsing %s\n", p_buffer );

    moveData res;

    u16 id; char alt_id[ 70 ];
    char type_buf[ 50 ], contesttype_buf[ 50 ];
    char cat_buf[ 50 ], defcat_buf[ 50 ];
    char weather_buf[ 50 ], pseudoWeather_buf[ 50 ], terrain_buf[ 50 ], sidecond_buf[ 50 ];
    char slotcon_buf[ 50 ], damage_buf[ 50 ], target_buf[ 50 ], prestg_buf[ 100 ];
    char heal_buf[ 50 ], recoil_buf[ 50 ], drain_buf[ 50 ], multihit_buf[ 50 ];
    char volstat_buf[ 50 ], secvolstat_buf[ 50 ];
    char boosts_buf[ 100 ], selfboosts_buf[ 100 ], secboost_buf[ 100 ], secselfboost_buf[ 100 ];
    char flags_buf[ 500 ];
    char status_buf[ 50 ], secstatus_buf[ 50 ];

    char critratio[ 20 ], secchance[ 20 ];

    sscanf( p_buffer, "%hu,%hhu,%hhu,%[^,],%[^,],%[^,],%[^,],%hhu,%hhd,%[^,],%[^,],%[^,]"
            ",%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]"
            ",%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",
            &id, &res.m_accuracy, &res.m_basePower, damage_buf, cat_buf, defcat_buf, alt_id,
            &res.m_pp, &res.m_priority, weather_buf, flags_buf, terrain_buf,
            pseudoWeather_buf, selfboosts_buf, slotcon_buf, heal_buf, sidecond_buf,
            status_buf, recoil_buf, volstat_buf, prestg_buf, boosts_buf,
            secchance, secselfboost_buf, secboost_buf, secvolstat_buf, secstatus_buf,
            multihit_buf, critratio, drain_buf, target_buf, type_buf, contesttype_buf );

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
    res.m_critRatio = getNumberOrNone( critratio );


    alt_moves[ alt_id ] = id;

    res.m_type = getType( type_buf );
    res.m_contestType = getContestType( contesttype_buf );

    res.m_category = getMoveCategory( cat_buf );
    res.m_defensiveCategory = getMoveCategory( defcat_buf, res.m_category );

    res.m_weather = getWeather( weather_buf );
    res.m_pseudoWeather = getPseudoWeather( pseudoWeather_buf );
    res.m_terrain = getTerrain( terrain_buf );
    res.m_sideCondition = getSideCondition( sidecond_buf );

    res.m_slotCondition = getSlotCondition( slotcon_buf );
    res.m_fixedDamage = getFixedDamage( damage_buf );
    res.m_target = getTarget( target_buf );
    res.m_pressureTarget = getTarget( prestg_buf );

    res.m_heal = parseFraction( heal_buf );
    res.m_recoil = parseFraction( recoil_buf );
    res.m_drain = parseFraction( drain_buf );
    res.m_multiHit = parseMultiHit( multihit_buf );

    res.m_volatileStatus = getVolatileStatus( volstat_buf );
    res.m_secondaryVolatileStatus = getVolatileStatus( secvolstat_buf );

    res.m_boosts = parseBoosts( boosts_buf );
    res.m_selfBoosts = parseBoosts( selfboosts_buf );
    res.m_secondaryBoosts = parseBoosts( secboost_buf );
    res.m_secondarySelfBoosts = parseBoosts( secselfboost_buf );

    res.m_flags = parseMoveFlags( flags_buf );

    res.m_status = getStatus( status_buf );
    res.m_secondaryStatus = getStatus( secstatus_buf );
    return res;
}

void readMoveData( char* p_moveData, vector<moveData>& p_out ) {
    FILE* f = fopen( p_moveData, "r" );
    char buffer[ 800 ];
    while( f && fgets( buffer, sizeof( buffer ), f ) )
        p_out.push_back( parseMoveData( buffer ) );
    fclose( f );
}

void printPkmnData( ) {
    size_t maxmovelearn = 0;
    fs::create_directories( FSROOT );
    FILE* g = fopen( OUT "/pokemonNames.h", "w" );
    fprintf( g, "#pragma once\n" );
    for( size_t i = 0; i < pkmn_data.size( ); ++i ) {
        FILE* f = getFilePtr( FSROOT "/PKMN_DATA/", i, 2 );
        assert( f );
        FILE* n = getFilePtr( FSROOT "/PKMN_NAME/", i, 2, ".str" );
        assert( n );
        FILE* l = getFilePtr( FSROOT "/PKMN_LEARN/", i, 2, ".learnset.data" );
        assert( l );
        assert( fwrite( &pkmn_data[ i ], sizeof( pkmnData ), 1, f ) );
        for( int j = 0; j < NUM_LANGUAGES; ++j ) {
            assert( fwrite( pkmn_names[ i ].m_name[ j ], 1, 15, n ) );
        }

        maxmovelearn = max( maxmovelearn, pkmn_learnsets[ i ].size( ) );
        for( auto mvd : pkmn_learnsets[ i ] ) {
            assert( fwrite( &mvd.first, sizeof( u16 ), 1, l ) );
            assert( fwrite( &mvd.second, sizeof( u16 ), 1, l ) );
        }
        u16 null = 0;
        for( size_t cnt = pkmn_learnsets[ i ].size( ); cnt < 340; ++cnt ) {
            assert( fwrite( &null, sizeof( u16 ), 1, l ) );
            assert( fwrite( &null, sizeof( u16 ), 1, l ) );
        }
        fclose( f );
        fclose( n );
        fclose( l );
        for( u8 forme = 1; forme <= ( pkmn_data[ i ].m_expTypeFormeCnt & 31 );
                ++forme ) {
            //fprintf( stderr, "write %lu %hhu / %hhu\n", i, forme,
            //         pkmn_data[ i ].m_expTypeFormeCnt & 31);
            f = getFilePtr( FSROOT "/PKMN_DATA/", i, 2, ".data", forme );
            n = getFilePtr( FSROOT "/PKMN_NAME/", i, 2, ".str", forme );
            if( forme <= forme_data[ i ].size( ) ) {
                fwrite( &forme_data[ i ][ forme - 1 ], sizeof( pkmnFormeData ), 1, f );
                for( int j = 0; j < NUM_LANGUAGES; ++j ) {
                    assert( fwrite( forme_names[ i ][ forme - 1 ].m_name[ j ], 1, 30, n ) );
                }
            } else {
                fwrite( &pkmn_data[ i ], sizeof( pkmnData ), 1, f );
            }
            fclose( f );
            fclose( n );
        }
        if( i && strcmp( pkmn_names[ i ].m_name[ 0 ], "???" ) ) {
            fprintf( g, "#define PKMN_" );
            char* s = pkmn_names[ i ].m_name[ 0 ];
            printNormalized( s, g );
            fprintf( g, " %lu\n", i );
        }
    }
    fclose( g );
    fprintf( stderr, "Max learnset size %lu\n", maxmovelearn );
}

void printItemData( ) {
    FILE* g = fopen( OUT "/itemNames.h", "w" );
    fprintf( g, "#pragma once\n" );

    map<string, int> duplicates = map<string, int>();

    for( size_t i = 0; i < item_names.size( ); ++i ) {
        if( !strcmp( item_names[ i ].m_name[ 0 ], "???" ) ) continue;

        FILE* f = getFilePtr( FSROOT "/ITEM_DATA/", i, 2 );
        assert( f );
        FILE* n = getFilePtr( FSROOT "/ITEM_NAME/", i, 2, ".str" );
        assert( n );
        assert( fwrite( &item_data[ i ], sizeof( itemData ), 1, f ) );
        for( int j = 0; j < NUM_LANGUAGES; ++j ) {
            assert( fwrite( item_names[ i ].m_name[ j ], 1, 20, n ) );
        }
        fclose( f );
        fclose( n );

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
}

void printAbilityData( ) {
    FILE* g = fopen( OUT "/abilityNames.h", "w" );
    fprintf( g, "#pragma once\n" );

    for( size_t i = 0; i < ability_names.size( ); ++i ) {
        // FILE* f = getFilePtr( FSROOT "/ABTY_DATA/", i, 2 );
        // assert( f );
        FILE* n = getFilePtr( FSROOT "/ABTY_NAME/", i, 2, ".str" );
        assert( n );
        FILE* ds = getFilePtr( FSROOT "/ABTY_DSCR/", i, 2, ".str" );
        assert( ds );
        // assert( fwrite( &item_data[ i ], sizeof( itemData ), 1, f ) );
        for( int j = 0; j < NUM_LANGUAGES; ++j ) {
            assert( fwrite( ability_names[ i ].m_name[ j ], 1, 20, n ) );
            assert( fwrite( ability_descrs[ i ].m_descr[ j ], 1, 200, ds ) );
        }
        // fclose( f );
        fclose( n );
        fclose( ds );

        fprintf( g, "#define A_" );
        char* s = ability_names[ i ].m_name[ 0 ];
        printNormalized( s, g );
        fprintf( g, " %lu\n", i );
    }
    fclose( g );
}

void printMoveData( ) {
    FILE* g = fopen( OUT "/moveNames.h", "w" );
    fprintf( g, "#pragma once\n" );
    map<string, int> duplicates = map<string, int>();

    for( size_t i = 0; i < move_names.size( ); ++i ) {
        FILE* f = getFilePtr( FSROOT "/MOVE_DATA/", i, 2 );
        assert( f );
        FILE* n = getFilePtr( FSROOT "/MOVE_NAME/", i, 2, ".str" );
        assert( n );
        FILE* ds = getFilePtr( FSROOT "/MOVE_DSCR/", i, 2, ".str" );
        assert( ds );
        assert( fwrite( &move_data[ i ], sizeof( moveData ), 1, f ) );
        for( int j = 0; j < NUM_LANGUAGES; ++j ) {
            assert( fwrite( move_names[ i ].m_name[ j ], 1, 20, n ) );
            assert( fwrite( move_descrs[ i ].m_descr[ j ], 1, 200, ds ) );
        }
        fclose( f );
        fclose( n );
        fclose( ds );

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
}

void readMedicineData( char* p_buf, itemData& p_out ) {
    char tmp_buf[ 60 ];
    assert( sscanf( p_buf, "%*d,%[^,],%hu,%hu,%hu,", tmp_buf, &p_out.m_param1,
                &p_out.m_param2, &p_out.m_param3 ) );
    p_out.m_effect = getMedicineEffect( tmp_buf );
}

void readItems( char* p_path, char* p_medicineData, char* p_formeChangeData, char* p_tmData,
        vector<names>& p_out, vector<itemData>& p_itemData ) {
    FILE* f = fopen( p_path, "r" );
    FILE* m = fopen( p_medicineData, "r" );
    FILE* fc = fopen( p_formeChangeData, "r" );
    FILE* tm = fopen( p_tmData, "r" );
    char buffer[ 500 ];
    char* t1;

    char med_buf[ 200 ];
    assert( fgets( med_buf, sizeof( med_buf ), m ) );
    char forme_buf[ 200 ];
    assert( fgets( forme_buf, sizeof( forme_buf ), fc ) );
    char tm_buf[ 200 ];
    assert( fgets( tm_buf, sizeof( tm_buf ), tm ) );
    while( fgets( buffer, sizeof( buffer ), f ) ) {
        t1 = strtok( buffer, "," );
        names n;
        for( int i = 0; i < NUM_LANGUAGES; ++i ) {
            n.m_name[ i ] = new char[ 30 ];
        }
        size_t id_a;
        sscanf( t1, "%lu", &id_a );

        t1 = strtok( NULL, "," );
        itemData t = { 0 };
        t.m_itemType = getItemType( t1 );

        if( ( t.m_itemType & 15 ) == 2 ) { // Medicine
            if( m ) {
                size_t id_b;
                sscanf( med_buf, "%lu", &id_b );
                assert( id_a == id_b );

                readMedicineData( med_buf, t );
                assert( fgets( med_buf, sizeof( med_buf ), m ) );
            } else {
                fprintf( stderr, "[%lu] No medicine data\n", id_a );
            }
        } else if( t.m_itemType == 8 ) { // Forme Change
            if( fc ) {
                size_t id_b;
                sscanf( forme_buf, "%lu,%*u,%hu,%hu,%*u,", &id_b, &t.m_param1, &t.m_param2 ); // (unused), pkmn_id, target forme, (unused)
                assert( id_a == id_b );
                assert( fgets( forme_buf, sizeof( forme_buf ), fc ) );
            } else {
                fprintf( stderr, "[%lu] No formeChange item data\n", id_a );
            }
        } else if( t.m_itemType == 12 ) { // TM/HM
            if( fc ) {
                char movename[ 50 ];
                size_t id_b;
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
    fprintf( stderr, "read %lu objects from %s\n", p_out.size( ), p_path );
}

void readForme( char* p_buf, pkmnFormeData& p_out ) {
    char tmp_buf[ 50 ], tmp_buf2[ 50 ], *tmp_buf3[ 3 ], tmp_buf5[ 50 ], tmp_buf6[ 50 ];
    char tmp_buf7[ 50 ], tmp_buf8[ 50 ], tmp_buf9[ 50 ], tmp_buf10[ 50 ], *tmp_buf11[ 50 ];
    for( int j = 0; j < 3; ++j ) tmp_buf3[ j ] = new char[ 50 ];
    for( int j = 0; j < 4; ++j ) tmp_buf11[ j ] = new char[ 50 ];

    float sz, wt;
    assert( sscanf( p_buf, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%hhu,%hhu,"
                "%hhu,%hhu,%hhu,%hhu,%hu,%[^,],%f m,%f kg,%[^,],%[^,],%hhu,%hhu,%hhu,%hhu,%hhu,"
                "%hhu,%[^,],%[^,],%[^,],%[^,],",
                tmp_buf5, tmp_buf, tmp_buf2, tmp_buf3[ 0 ], tmp_buf3[ 1 ], tmp_buf3[ 2 ],
                tmp_buf6, tmp_buf7, &p_out.m_bases[ 0 ], &p_out.m_bases[ 1 ],
                &p_out.m_bases[ 2 ], &p_out.m_bases[ 3 ], &p_out.m_bases[ 4 ], &p_out.m_bases[ 5 ],
                &p_out.m_expYield, tmp_buf8, &sz, &wt, tmp_buf9, tmp_buf10,
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
    p_out.m_eggGroups = ( getEggGroup( tmp_buf6 ) << 4 ) | getEggGroup( tmp_buf7 );
    p_out.m_genderRatio = getGender( tmp_buf8 );
    p_out.m_size = (u8) ( sz * 10 );
    p_out.m_weight = (u16) ( wt * 10 );
    p_out.m_colorShape = ( getColor( tmp_buf9 ) << 4 ) | getShape( tmp_buf10 );

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
                   vector<vector<names>>& p_formeNameOut,
                   vector<vector<pkmnFormeData>>& p_formeOut ) {
    FILE* pdata = fopen( p_pkmnData, "r" );
    FILE* pdesc = fopen( p_pkmnDescr, "r" );

    FILE* fdata = fopen( p_pkmnFormeNames, "r" );
    FILE* fdesc = fopen( p_pkmnFormeDescr, "r" );
    char fdata_buf[ 1000 ], fdescr_buf[ 1000 ];
    assert( fgets( fdata_buf, sizeof( fdata_buf ), fdata ) );
    assert( fgets( fdescr_buf, sizeof( fdescr_buf ), fdesc ) );

    for( size_t i = 0; i <= MAX_PKMN; ++i ) {
        // fprintf( stderr, "reading data %lu\n", i );
        char data_buf[ 1000 ], descr_buf[ 1000 ];
        assert( fgets( data_buf, sizeof( data_buf ), pdata ) );
        assert( fgets( descr_buf, sizeof( descr_buf ), pdesc ) );

        pkmnData cur = { 0 };
        cur.m_baseForme = { 0 };
        int id_a, id_b;
        char tmp_buf[ 50 ];
        u8 tmp1;
        assert( sscanf( data_buf, "%d,%[^,],%hhu,%hhu,%hhu,%hhu",
                &id_a, tmp_buf, &cur.m_eggCycles, &cur.m_catchrate, &cur.m_baseFriend, &tmp1 ) );

        assert( sscanf( descr_buf, "%d", &id_b ) );
        assert( id_a == id_b );
        readForme( descr_buf, cur.m_baseForme );

        // Check for existing forms
        u8 forms_found = 0;
        int cur_formbase, cur_formid;
        sscanf( fdescr_buf, "%d_%d", &cur_formbase, &cur_formid );
        vector<names> fnames;
        vector<pkmnFormeData> fdatas;
        while( cur_formbase == id_a ) {
            names n = pkmn_names[ id_a ], n2;
            pkmnFormeData pf = cur.m_baseForme;
            while( cur_formid > forms_found + 1 ) {
                fnames.push_back( n );
                fdatas.push_back( pf );
                forms_found++;
            }
            for( int i = 0; i < NUM_LANGUAGES; ++i ) {
                n2.m_name[ i ] = new char[ 30 ];
            }

            char* t1 = strtok( fdata_buf, "," );
            int cnt = 0;
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


        cur.m_expTypeFormeCnt = ( getExpType( tmp_buf ) << 5 )
            |  max( tmp1, forms_found );
        p_out.push_back( cur );
    }
    fprintf( stderr, "read %lu pkmndata\n", p_out.size( ) );
}

int main( int p_argc, char** p_argv ) {
    if( p_argc < 15 ) {
        fprintf( stderr, "too few args." );
        return 1;
    }

    // pkmnnames abtynames movenames itemnames pkmndata pkmndescr pkmnformnames
    // pkmnformdescr

    readNames( p_argv[ 1 ], pkmn_names );
    for( size_t i = 0; i < pkmn_names.size( ); ++i )
        pkmns[ pkmn_names[ i ].m_name[ 0 ] ] = i;
    readNames( p_argv[ 2 ], ability_names );
    readDescrs( p_argv[ 14 ], ability_descrs, 199 );

    for( size_t i = 0; i < ability_names.size( ); ++i )
        abilities[ ability_names[ i ].m_name[ 0 ] ] = i;
    readNames( p_argv[ 3 ], move_names );
    for( size_t i = 0; i < move_names.size( ); ++i )
        moves[ move_names[ i ].m_name[ 0 ] ] = i;
    readDescrs( p_argv[ 15 ], move_descrs, 199 );

    readItems( p_argv[ 4 ], p_argv[ 9 ], p_argv[ 10 ], p_argv[ 11 ], item_names, item_data );
    for( size_t i = 0; i < item_names.size( ); ++i )
        items[ item_names[ i ].m_name[ 0 ] ] = i;

    readMoveData( p_argv[ 12 ], move_data );
    readPkmnData( p_argv[ 5 ], p_argv[ 6 ], p_argv[ 7 ], p_argv[ 8 ], pkmn_data, forme_names,
                  forme_data );
    readLearnsetData( p_argv[ 13 ], pkmn_learnsets );

    printPkmnData( );
    printItemData( );
    printAbilityData( );
    printMoveData( );
}
