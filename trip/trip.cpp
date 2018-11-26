#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <set>

#define MAXL 85

using namespace std;

int T;
string A, B;

int dp[ MAXL + 1 ][ MAXL + 1 ];
set< string > S[ MAXL + 1 ][ MAXL + 1 ];

int main( void ) {
  scanf("%d", &T );
  while( T-- ) {
    cin >> A >> B;

    int n = A.length(), m = B.length();
    for( int i = 0; i <= MAXL; i++ ) {
      S[ i ][ 0 ].insert( "" );
      S[ 0 ][ i ].insert( "" );
    }
    for( int i = 1; i <= n; i++ ) {
      for( int j = 1; j <= m; j++ ) {
        if( A[ i - 1 ] == B[ j - 1 ] ) {
          dp[ i ][ j ] = dp[ i - 1 ][ j - 1 ] + 1;
          for( set< string >::iterator it = S[ i - 1 ][ j - 1 ].begin(); it != S[ i - 1 ][ j - 1 ].end(); it++ ) {
            string str2 = *it;
            str2.append( A.substr( i - 1, 1 ) );
            S[ i ][ j ].insert( str2 );
          }
        }
        else {
          int id1, id2;
          if( dp[ i - 1 ][ j ] >= dp[ i ][ j - 1 ] ) {
            dp[ i ][ j ] = dp[ i - 1 ][ j ];
            for( set< string >::iterator it = S[ i - 1 ][ j ].begin(); it != S[ i - 1 ][ j ].end(); it++ ) {
              S[ i ][ j ].insert( *it );
            }
          }
          if( dp[ i - 1 ][ j ] <= dp[ i ][ j - 1 ] ) {
            dp[ i ][ j ] = dp[ i ][ j - 1 ];
            for( set< string >::iterator it = S[ i ][ j - 1 ].begin(); it != S[ i ][ j - 1 ].end(); it++ ) {
              S[ i ][ j ].insert( *it );
            }
          }
        }
      }
    }
    for( set< string >::iterator it = S[ n ][ m ].begin(); it != S[ n ][ m ].end(); ++it ) {
      if( ( *it ).size() == dp[ n ][ m ] ) {
        cout << *it << endl;
      }
    }
    memset( dp, 0, sizeof( dp ) ) ;
    for( int i = 0; i <= MAXL; i++ ) {
      for( int j = 0; j <= MAXL; j++ ) {
        S[ i ][ j ].clear();
      }
    }
    cout << "\n";
  }
  return 0;
}
