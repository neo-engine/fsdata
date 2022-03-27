// Arguments
// pkmnnames.csv abtynames.csv movenames.csv itemnames.csv pkmndata.csv pkmndescr.csv
// pkmnformnames.csv pkmnformes.csv itemdata_medicine.csv

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <map>
#include <string>
#include <vector>
#include "fsdata.h"

struct locationData {
    u16 m_bgmNameIdx = 0;
    u8  m_frameType  = 0;
    u8  m_mugType    = 0;
};

constexpr u8 MAX_SAMPLES_PER_SSEQ = 4;
struct sseqData {
    u16 m_bank; // bank used for sseq
    u16 m_sseqId;
    u16 m_sampleCnt;
    u16 m_samplesId[ MAX_SAMPLES_PER_SSEQ ];
};

map<u16, names>        location_names;
map<u16, locationData> location_data;

map<u16, sseqData>            sseq_data;        // bgmid -> sseq data
map<u16, string>              bgm_macro_names;  // bgmid -> macro name
map<string, pair<u16, names>> bgm_names;        // macro name -> { bgmId, localized names }
vector<u16>                   bgm_names_sorted; // bgm data id -> bgm id
map<u16, u16>                 data_ids;         // bgm id -> bgm data id
map<string, u16>              sseq_names;       // sseq macro name -> sseq id
map<string, u16>              sbnk_names;       // sbnk macro name -> sbnk id
map<string, u16>              swar_names;       // swar macro name -> swar id

void printLocationData( ) {
    fs::create_directories( std::string( OUT ) );
    FILE* g = fopen( OUT "/locationNames.h", "w" );
    fprintf( g, "#pragma once\n" );

    auto outf = vector<FILE*>( );
    fs::create_directories( std::string( FSROOT ) );
    fs::create_directories( std::string( FSROOT "/LOC_NAME/" ) );
    auto dataf = fopen( FSROOT "/location.datab", "wb" );
    assert( dataf );
    for( int j = 0; j < NUM_LANGUAGES; ++j ) {
        FILE* fo = fopen(
            ( std::string( FSROOT "/LOC_NAME/locname." ) + std::to_string( j ) + ".strb" ).c_str( ),
            "wb" );
        assert( fo );
        outf.push_back( fo );
    }

    map<string, int> duplicates = map<string, int>( );
    u16              mx         = 0;
    for( auto i = location_names.begin( ); i != location_names.end( ); ++i ) {
        mx = max( mx, i->first );
        if( i->first && strcmp( i->second.m_name[ 0 ], "???" ) ) {
            fprintf( g, "#define L_" );
            char* s = i->second.m_name[ 0 ];
            printNormalized( s, g );
            if( duplicates.count( i->second.m_name[ 0 ] ) ) {
                fprintf( g, "%d %hu\n", duplicates[ i->second.m_name[ 0 ] ] + 1, i->first );
            } else {
                fprintf( g, " %hu\n", i->first );
            }
            duplicates[ i->second.m_name[ 0 ] ]++;
        }
    }

    for( u16 i = 0; i <= mx; ++i ) {
        names n;
        for( int i = 0; i < NUM_LANGUAGES; ++i ) {
            n.m_name[ i ] = new char[ 40 ];
            std::memset( n.m_name[ i ], 0, 40 );
        }

        locationData l = locationData( );

        if( location_names.count( i ) ) { n = location_names[ i ]; }
        if( location_data.count( i ) ) { l = location_data[ i ]; }

        assert( fwrite( &l, sizeof( locationData ), 1, dataf ) );
        for( int j = 0; j < NUM_LANGUAGES; ++j ) {
            assert( fwrite( n.m_name[ j ], 1, 25, outf[ j ] ) );
        }
    }

    fclose( g );
    fclose( dataf );
    for( int j = 0; j < NUM_LANGUAGES; ++j ) { fclose( outf[ j ] ); }
}

void printBGMData( ) {
    fs::create_directories( std::string( OUT ) );
    fs::create_directories( std::string( FSROOT "/BGM_NAME/" ) );
    FILE* n    = fopen( OUT "/bgmNames.h", "w" );
    FILE* g    = fopen( OUT "/bgmTranslation.h", "w" );
    FILE* s2   = fopen( OUT "/sseqData.cpp", "w" );
    auto  outf = vector<FILE*>( );
    for( int j = 0; j < NUM_LANGUAGES; ++j ) {
        FILE* fo
            = fopen( ( std::string( FSROOT "/BGM_NAME/bgmnames." ) + std::to_string( j ) + ".strb" )
                         .c_str( ),
                     "wb" );
        assert( fo );
        outf.push_back( fo );
    }

    fprintf( g, "#pragma once\n"
                "#ifndef NO_SOUND\n"
                "#include \"bgmNames.h\"\n"
                "namespace SOUND::SSEQ {\n"
                "    constexpr int BGMIndexForName( unsigned p_name ) {\n"
                "        switch( p_name ) {\n"
                "        default: return -1;\n" );
    fprintf( n, "#pragma once\n\n" );

    fprintf( s2, "#ifndef NO_SOUND\n"
                 "#include \"sound/sseqData.h\"\n"
                 "\n"
                 "namespace SOUND::SSEQ {\n"
                 "    const sseqData SSEQ_LIST[ NUM_SSEQ ] = {\n" );

    /*
    fprintf( s, "#pragma once\n"
                "#ifndef NO_SOUND\n"
                "\n" );

    fprintf( s,
             ( "#define MAX_SSEQ "s + std::to_string( sseq_names.size( ) - 1 ) + "\n" ).c_str( ) );
    for( const auto& [ name, id ] : sseq_names ) {
        fprintf( s, ( "#define "s + name + " " + std::to_string( id ) + "\n" ).c_str( ) );
    }
    fprintf( s, "\n" );
    fprintf( s,
             ( "#define MAX_BNK "s + std::to_string( sbnk_names.size( ) - 1 ) + "\n" ).c_str( ) );
    for( const auto& [ name, id ] : sbnk_names ) {
        fprintf( s, ( "#define "s + name + " " + std::to_string( id ) + "\n" ).c_str( ) );
    }
    fprintf( s, "\n" );
    fprintf( s,
             ( "#define MAX_BNK "s + std::to_string( swar_names.size( ) - 1 ) + "\n" ).c_str( ) );
    for( const auto& [ name, id ] : swar_names ) {
        fprintf( s, ( "#define "s + name + " " + std::to_string( id ) + "\n" ).c_str( ) );
    }
    fprintf( s, "#endif\n" );
    fclose( s );
    */

    fprintf(
        n, ( "#define NUM_SSEQ "s + std::to_string( bgm_names_sorted.size( ) ) + "\n" ).c_str( ) );
    fprintf(
        n,
        ( "#define MAX_BGM "s + std::to_string( bgm_names_sorted.size( ) - 1 ) + "\n" ).c_str( ) );

    fprintf( n, "#define BGM_NONE 0\n" );
    for( size_t i = 0; i < bgm_names_sorted.size( ); ++i ) {
        auto        curId         = bgm_names_sorted[ i ];
        const auto& curMacroName  = bgm_macro_names[ curId ];
        const auto& [ id, names ] = bgm_names[ curMacroName ];
        assert( curId == id );

        for( auto j = 0; j < NUM_LANGUAGES; ++j ) {
            assert( fwrite( names.m_name[ j ], 1, 25, outf[ j ] ) );
        }

        const auto& dt = sseq_data[ curId ];
        fprintf( s2, "        { %hu, %hu, %hu, { %hu, %hu, %hu, %hu } }, // %s\n", dt.m_bank,
                 dt.m_sseqId, dt.m_sampleCnt, dt.m_samplesId[ 0 ], dt.m_samplesId[ 1 ],
                 dt.m_samplesId[ 2 ], dt.m_samplesId[ 3 ], curMacroName.c_str( ) );

        fprintf( n,
                 ( "#define "s + curMacroName + " " + std::to_string( curId ) + "\n" ).c_str( ) );

        fprintf(
            g,
            ( "        case "s + curMacroName + ": return " + to_string( i ) + ";\n" ).c_str( ) );
    }
    fprintf( s2, "    }\n"
                 "} // namespace SOUND::SSEQ\n"
                 "#endif\n" );

    fprintf( g, "        }\n"
                "    }\n"
                "} // namespace SOUND::SSEQ\n"
                "#endif\n" );

    fclose( g );
    fclose( n );
    for( int j = 0; j < NUM_LANGUAGES; ++j ) { fclose( outf[ j ] ); }
}

void copyBGMFiles( const char* p_bgmpath ) {
    fs::create_directories( std::string( FSROOT "BGM/SSEQ/" ) );
    fs::create_directories( std::string( FSROOT "BGM/SWAR/" ) );
    fs::create_directories( std::string( FSROOT "BGM/SBNK/" ) );

    for( const auto& [ name, id ] : sseq_names ) {
        if( !id ) { continue; }
        fs::path from = string( p_bgmpath ) + "sseq/" + name.substr( 5 ) + ".sseq";
        fs::path to   = std::string( FSROOT "BGM/SSEQ/" ) + to_string( id ) + ".sseq";

        error_code ec;
        if( !fs::copy_file( from, to, fs::copy_options::overwrite_existing, ec ) ) {
            fprintf( stderr, "Failed to copy %s to %s. (%s)\n", from.c_str( ), to.c_str( ),
                     ec.message( ).c_str( ) );
        }
    }

    for( const auto& [ name, id ] : swar_names ) {
        if( !id ) { continue; }
        fs::path from = string( p_bgmpath ) + "swar/" + name.substr( 5 ) + ".swar";
        fs::path to   = std::string( FSROOT "BGM/SWAR/" ) + to_string( id ) + ".swar";

        error_code ec;
        if( !fs::copy_file( from, to, fs::copy_options::overwrite_existing, ec ) ) {
            fprintf( stderr, "Failed to copy %s to %s. (%s)\n", from.c_str( ), to.c_str( ),
                     ec.message( ).c_str( ) );
        }
    }

    for( const auto& [ name, id ] : sbnk_names ) {
        if( !id ) { continue; }
        fs::path from = string( p_bgmpath ) + "sbnk/" + name.substr( 5 ) + ".sbnk";
        fs::path to   = std::string( FSROOT "BGM/SBNK/" ) + to_string( id ) + ".sbnk";

        error_code ec;
        if( !fs::copy_file( from, to, fs::copy_options::overwrite_existing, ec ) ) {
            fprintf( stderr, "Failed to copy %s to %s. (%s)\n", from.c_str( ), to.c_str( ),
                     ec.message( ).c_str( ) );
        }
    }
}

void readLocationData( char* p_path, map<u16, locationData>& p_out ) {
    FILE* f             = fopen( p_path, "r" );
    char  buffer[ 500 ] = { 0 };
    while( fgets( buffer, sizeof( buffer ), f ) ) {
        u16          id;
        locationData n = locationData( );

        char b1[ 50 ] = { 0 }, b2[ 50 ] = { 0 };
        sscanf( buffer, "%hu;%*[^;];%[^;];%[^;];%hhu;", &id, b1, b2, &n.m_mugType );
        n.m_bgmNameIdx = bgm_names[ string( b1 ) ].first;
        if( !n.m_bgmNameIdx ) { printf( "%s Unknown BGM \"%s\"\n", buffer, b1 ); }
        n.m_frameType = getFrameType( b2 );

        p_out[ id ] = n;
    }
    // fprintf( stderr, "read %lu objects from %s\n", p_out.size( ), p_path );
    fclose( f );
}

void readBGMData( char* p_path, vector<u16>& p_dataIds, map<string, pair<u16, names>>& p_bgmId,
                  map<u16, string>& p_bgmMacroNames, map<string, u16>& p_sseqNames,
                  map<string, u16>& p_swarNames, map<string, u16>& p_sbnkNames,
                  map<u16, sseqData>& p_bgmNames ) {

    FILE*  f             = fopen( p_path, "r" );
    char   buffer[ 800 ] = { 0 };
    u16    lstrec        = 0;
    u16    bgmcnt        = 0;
    string curname       = "BGM_NONE";

    p_swarNames[ "SWAR_NONE" ] = 0;
    p_sseqNames[ "SSEQ_NONE" ] = 0;
    p_sbnkNames[ "SBNK_NONE" ] = 0;

    while( fgets( buffer, sizeof( buffer ), f ) ) {
        u16  id;
        char b1[ 50 ] = { 0 }, b2[ 50 ] = { 0 }, b3[ 50 ] = { 0 }, b4[ 50 ] = { 0 },
                    b5[ 50 ] = { 0 }, b6[ 50 ] = { 0 }, b7[ 50 ] = { 0 }, bn[ 500 ] = { 0 };

        if( sscanf( buffer, "%hu;%45[^;];%450[^\n]", &id, b1, bn ) ) {
            // record name
            curname = string( "REC_" ) + string( b1 );
            bgmcnt = lstrec = id;
            p_dataIds.push_back( bgmcnt );
        } else if( sscanf( buffer, "%45[^;];%45[^;];%45[^;];%45[^;];%45[^;];%45[^;];%45[^;];%490[^\n]",
                           b1, b2, b3, b4, b5, b6, b7, bn ) ) {
            ++bgmcnt;

            // BGM name
            curname                  = string( "BGM_" ) + string( b1 );
            string         sbnkname  = string( "SBNK_" ) + string( b2 );
            string         sseqname  = string( "SSEQ_" ) + string( b3 );
            vector<string> swarnames = {
                string( "SWAR_" ) + string( b4 ),
                string( "SWAR_" ) + string( b5 ),
                string( "SWAR_" ) + string( b6 ),
                string( "SWAR_" ) + string( b7 ),
            };

            sseqData d = sseqData( );
            if( !p_sseqNames.count( sseqname ) ) { p_sseqNames[ sseqname ] = p_sseqNames.size( ); }
            d.m_sseqId = p_sseqNames[ sseqname ];
            if( !p_sbnkNames.count( sbnkname ) ) { p_sbnkNames[ sbnkname ] = p_sbnkNames.size( ); }
            d.m_bank = p_sbnkNames[ sbnkname ];
            for( u8 i = 0; i < MAX_SAMPLES_PER_SSEQ; ++i ) {
                if( !p_swarNames.count( swarnames[ i ] ) ) {
                    p_swarNames[ swarnames[ i ] ] = p_swarNames.size( );
                }
                if( p_swarNames[ swarnames[ i ] ] ) {
                    d.m_samplesId[ d.m_sampleCnt++ ] = p_swarNames[ swarnames[ i ] ];
                }
            }
            p_bgmNames[ bgmcnt ] = d;
            p_dataIds.push_back( bgmcnt );
        }

        // parse record name
        char* t1 = strtok( bn, ";" );
        names n;
        for( int i = 0; i < NUM_LANGUAGES; ++i ) {
            n.m_name[ i ] = new char[ 40 ];
            std::memset( n.m_name[ i ], 0, 40 );
        }
        int cnt = 0;
        strncpy( n.m_name[ cnt++ ], fixEncoding( t1 ), 29 );
        while( cnt < NUM_LANGUAGES && ( t1 = strtok( NULL, ";" ) ) ) {
            strncpy( n.m_name[ cnt++ ], fixEncoding( t1 ), 29 );
        }

        p_bgmMacroNames[ bgmcnt ] = curname;
        p_bgmId[ curname ]        = { bgmcnt, n };
    }
    // fprintf( stderr, "read %lu objects from %s\n", p_out.size( ), p_path );
    fclose( f );
}

int main( int p_argc, char** p_argv ) {
    if( p_argc < 5 ) {
        fprintf( stderr, "too few args." );
        return 1;
    }

    readBGMData( p_argv[ 1 ], bgm_names_sorted, bgm_names, bgm_macro_names, sseq_names, swar_names,
                 sbnk_names, sseq_data );

    readNames( p_argv[ 2 ], location_names );
    readLocationData( p_argv[ 3 ], location_data );
    printLocationData( );
    printBGMData( );

    copyBGMFiles( p_argv[ 4 ] );
}
