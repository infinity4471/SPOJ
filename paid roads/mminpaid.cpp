#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

#define MAXN 10
#define INF 1 << 29

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;
typedef pair< int, pii > state;

int N, M, dist[ MAXN + 1 ][ 1 << MAXN ];
int A[ MAXN ], B[ MAXN ], C[ MAXN ], W[ MAXN ][ 2 ];

int dijkstra( int s, int t ) {
  for( int i = 0; i <= MAXN; i++ ) {
    for( int j = 0; j < ( 1 << MAXN ); j++ ) {
        dist[ i ][ j ] = INF;
    }
  }
  set< state > S;
  dist[ s ][ 1 << ( s - 1 ) ] = 0;
  S.insert( mp( 0, mp( s, ( 1 << ( s - 1 ) ) ) ) );
  while( !S.empty() ) {
    state AA = *S.begin();
    S.erase( S.begin() );
    int d = AA.X, u =  AA.Y.X, bit = AA.Y.Y;
    for( int i = 0; i < M; i++ ) {
      if( A[ i ] == u ) {
        int d1 = d + W[ i ][ 1 ], v = B[ i ];
        int bit2 = bit;
        bit2 |= ( 1 << ( v - 1 ) );
        if( ( bit2 & ( 1 << ( C[ i ] - 1 ) ) ) && d + W[ i ][ 0 ] < dist[ v ][ bit2 ] ) {
          dist[ v ][ bit2 ] = d + W[ i ][ 0 ];
          S.insert( mp( dist[ v ][ bit2 ], mp( v, bit2 ) ) );
        }
        if( d + W[ i ][ 1 ] < dist[ v ][ bit2 ] ) {
          dist[ v ][ bit2 ] = d + W[ i ][ 1 ];
          S.insert( mp( dist[ v ][ bit2 ], mp( v, bit2 ) ) );
        }
      }
    }
  }
  int ans = INF;
  for( int i = 0; i < ( 1 << N ); i++ ) {
    ans = min( ans, dist[ t ][ i ] );
  }
  return ans;
}

int main( void ) {
  scanf("%d%d", &N, &M );
  for( int i = 0; i < M; i++ ) {
    scanf("%d%d%d%d%d", &A[ i ], &B[ i ], &C[ i ], &W[ i ][ 0 ], &W[ i ][ 1 ] );
  }
  int ans = dijkstra( 1, N );
  if( ans == INF ) printf("impossible\n");
  else printf("%d\n", ans );
  return 0;
}
