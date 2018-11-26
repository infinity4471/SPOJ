#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 2100
#define MAXQ 150100

using namespace std;

int N, M, Q;
int ans = 0, sumstrip = 0, sumcycle = 0, strip[ MAXN + 1 ], cycle[ MAXN + 1 ];
int dp[ 2 ][ MAXQ + 1 ];

void computeA() {
  ans = sumcycle;
  Q -= sumcycle;
  sort( strip + 1, strip + N + 1 );
  for( int i = N; i > 0; i-- ) {
    if( Q - strip[ i ] >= 0 ) {
      Q -= strip[ i ];
      ans += strip[ i ] - 1;
    } else {
      ans += Q - 1;
      Q = 0;
      break;
    }
  }
}

void computeB() {
  for( int i = 1; i <= N; i++ ) {
    for( int j = 0; j <= Q; j++ ) {
      dp[ i % 2 ][ j ] = dp[ ( i - 1 ) % 2 ][ j ];
      if( j - cycle[ i ] >= 0 ) dp[ i % 2 ][ j ] = max( dp[ i % 2 ][ j ], dp[ ( i - 1 ) % 2 ][ j - cycle[ i ] ] + cycle[ i ] );
    }
  }
  ans = max( ans, dp[ N % 2 ][ Q ] );
  for( int i = 0; i < Q; i++ ) {
    int val = Q - i - 1;
    ans = max( ans, dp[ N % 2 ][ i ] + val );
  }
}

int main( void ) {
  int T;
  scanf("%d", &T );
  while( T-- ) {
    scanf("%d%d%d", &Q, &N, &M );
    for( int i = 1; i <= N; i++ ) {
      scanf("%d", &cycle[ i ] );
      sumcycle += cycle[ i ];
    }
    for( int i = 1; i <= M; i++ ) {
      scanf("%d", &strip[ i ] );
      sumstrip += strip[ i ];
    }
    if( sumcycle <= Q ) computeA();
    else computeB();
    printf("%d\n", ans );

    sumstrip = sumcycle = ans = 0;
    memset( cycle, 0, sizeof( cycle ) );
    memset( strip, 0, sizeof( strip ) );
    memset( dp, 0, sizeof( dp ) );
  }
  return 0;
}
