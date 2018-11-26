#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

#define MAXN 250

using namespace std;

int visited[ MAXN + 1 ], par[ MAXN + 1 ], flow[ MAXN + 1 ][ MAXN + 1 ], cap[ MAXN + 1 ][ MAXN + 1 ];

bool bfs( int s, int t ) {
  memset( par, 0, sizeof( par ) );
  memset( visited, 0, sizeof( visited ) );
  queue< int > Q;
  Q.push( s );
  visited[ s ] = true;
  par[ s ] = -1;
  while( !Q.empty() ) {
    int u = Q.front();
    Q.pop();
    for( int i = 0; i < MAXN; i++ ) {
      if( !visited[ i ] && cap[ u ][ i ] - flow[ u ][ i ] > 0 ) {
        visited[ i ] = true;
        par[ i ] = u;
        Q.push( i );
      }
    }
  }
  return visited[ t ];
}

int maxflow( int s, int t ) {
  int ans = 0;
  while( bfs( s, t ) ) {
    int aug = 2500000;
    for( int i = t; i != s; i = par[ i ] ) {
      aug = min( aug, cap[ par[ i ] ][ i ] - flow[ par[ i ] ][ i ] );
    }
    ans += aug;
    for( int i = t; i != s; i = par[ i ] ) {
      flow[ par[ i ] ][ i ] += aug;
      flow[ i ][ par[ i ] ] -= aug;
    }
  }
  return ans;
}

int main( void ) {
  int T;
  scanf("%d", &T );
  while( T-- ) {
    int N, x, y;
    scanf("%d", &N );
    for( int i = 1; i <= N; i++ ) {
      scanf("%d%d", &x, &y );
      cap[ x ][ y + 120 ] = 1;
    }
    for( int i = 0; i < 120; i++ ) {
      cap[ 240 ][ i ] = 1;
      cap[ i + 120 ][ 241 ] = 1;
    }
    printf("%d\n", maxflow( 240, 241 ) );
    memset( flow, 0, sizeof( flow ) );
    memset( cap, 0, sizeof( cap ) );
  }
  return 0;
}
