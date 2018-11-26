#include <cstdio>
#include <algorithm>
#include <vector>

#define X first
#define Y second
#define mp make_pair
#define pb push_back

#define MAXN 100100

using namespace std;

typedef pair< int, int > pii;
typedef pair< int, pii > trip;
typedef long long ll;

ll ans = 0LL;

int N, point = 0, A[ MAXN + 1 ], left[ MAXN + 1 ], right[ MAXN + 1 ];
trip stack[ MAXN + 1 ];

int main( void ) {
  while( true ) {
    scanf("%d", &N );
    if( !N ) break;
    for( int i = 1; i <= N; i++ ) scanf("%d", &A[ i ] );
    point = 0;
    for( int i = 1; i <= N; i++ ) {
      while( point > 0 && stack[ point ].X > A[ i ] ) point--;
      if( A[ i ] == stack[ point ].X ) {
        stack[ point ].Y.Y = i;
        left[ i ] = left[ stack[ point ].Y.X ];
      } else {
        left[ i ] = stack[ point ].Y.Y;
        stack[ ++point ] = mp( A[ i ], mp( i, i ) );
      }
    }
    stack[ 0 ] = mp( 1000000000, mp( N, N ) );
    for( int i = N; i > 0; i-- ) {
      while( point > 0 && stack[ point ].X > A[ i ] ) point--;
      if( A[ i ] == stack[ point ].X ) {
        stack[ point ].Y.Y = i;
        right[ i ] = stack[ point ].Y.X;
      } else {
        right[ i ] = stack[ point ].Y.Y;
        stack[ ++point ] = mp( A[ i ], mp( i, i ) );
      }
    }
    for( int i = 1; i <= N; i++ ) {
      printf("left[ %d ] = %d, right[ %d ] = %d\n", i, left[ i ], i, right[ i ] );
      ll val = ( ll )( right[ i ] - left[ i ] + 1 ) * ( ll )A[ i ];
      ans = max( ans, val );
    }
    printf("%lld\n", ans );
  }
  return 0;
}
