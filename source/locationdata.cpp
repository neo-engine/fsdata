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

map<u16, names> location_names;

void printLocationData( ) {
    FILE* g = fopen( OUT "/locationNames.h", "w" );
    fprintf( g, "#pragma once\n" );

    map<string, int> duplicates = map<string, int>();
    for( auto i = location_names.begin( ); i != location_names.end( ); ++i ) {
        // FILE* f = getFilePtr( FSROOT "/LOC_DATA/", i, 2 );
        // assert( f );
        FILE* n = getFilePtr( FSROOT "/LOC_NAME/", i->first, 3, ".str" );
        assert( n );
        // assert( fwrite( &item_data[ i ], sizeof( itemData ), 1, f ) );
        for( int j = 0; j < NUM_LANGUAGES; ++j ) {
            assert( fwrite( i->second.m_name[ j ], 1, 25, n ) );
        }
        // fclose( f );
        fclose( n );

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
    fclose( g );
}

int main( int p_argc, char** p_argv ) {
    if( p_argc < 2 ) {
        fprintf( stderr, "too few args." );
        return 1;
    }

    readNames( p_argv[ 1 ], location_names );
    printLocationData( );
}
