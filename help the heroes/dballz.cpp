#include <cstdio>
#include <algorithm>

#define MAXE 50001
#define MAXL 1001

using namespace std;

int dp[ 2 ][ MAXE + 1 ], energy[ MAXL + 1 ], time[ MAXL + 1 ];

int readint() {
  int n = 0;
  char c = getchar_unlocked();
  while ( !( '0' <= c && c <= '9' ) ) {
    c = getchar_unlocked();
  }
  while ( '0' <= c && c <= '9' ) {
    n = n * 10 + c - '0';
    c = getchar_unlocked();
  }
  return n;
}

int main( void ) {
  int T;
  T = readint();
  while( T-- ) {
    int E, L;
    E = readint();
    L = readint();
    for( int i = 1; i <= L; i++ ) {
      energy[ i ] = readint();
    }
    for( int i = 1; i <= L; i++ ) {
      time[ i ] = readint();
    }
    for( int i = 0; i <= E; i++ ){
      dp[ 0 ][ i ] = dp[ 1 ][ i ] = 0;
    }
    for( int i = 1; i <= E; i++ ) {
      for( int j = 1; j <= L; j++ ) {
        dp[ j % 2 ][ i ] = dp[ ( j - 1 ) % 2 ][ i ];
        if( i - energy[ j ] >= 0 ) dp[ j % 2 ][ i ] = max( dp[ j % 2 ][ i ], dp[ ( j - 1 ) % 2 ][ i - energy[ j ] ] + time[ j ] );
      }
    }
    printf("%d\n", dp[ L % 2 ][ E ] );
  }
  return 0;
}
