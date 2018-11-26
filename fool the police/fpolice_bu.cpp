#include <cstdio>
#include <algorithm>
#include <vector>
 
#define MAXN 1100
#define INF 1234567890
#define mp make_pair
#define C first
#define TT second
 
using namespace std;
 
typedef pair< int, int > state;
 
state dp[ MAXN + 1 ][ MAXN + 1 ]; // destination and time
 
int tt[ MAXN + 1 ][ MAXN + 1 ], cost[ MAXN + 1 ][ MAXN + 1 ], N, T;
 
int main( void )
{
	int tests;
	scanf("%d", &tests );
	while( tests-- ) {
		scanf("%d%d", &N, &T );
		if( !N && !T ) break;
		for( int i = 1; i <= N; i++ ) {
			for( int j = 1; j <= N; j++ ) {
				scanf("%d", &tt[ i ][ j ] );
			}
		}
		for( int i = 1; i <= N; i++ ) {
			for( int j = 1; j <= N; j++ ) {
				scanf("%d", &cost[ i ][ j ] );
			}
		}
		for( int i = 0; i <= MAXN; i++ ) {
			for( int j = 0; j <= MAXN; j++ ) {
				dp[ i ][ j ] = mp( INF, INF );
			}
		}
		for( int i = 0; i <= T; i++ ) {
			dp[ i ][ 1 ] = mp( 0, 0 );
		}
		for( int i = 1; i <= T; i++ ) {
			for( int j = 1; j <= N; j++ ) {
				for( int k = 1; k <= N; k++ ) {
					if( k == j || i < tt[ k ][ j ] ) continue;
					state mys = mp( cost[ k ][ j ] + dp[ i - tt[ k ][ j ] ][ k ].C, 
								tt[ k ][ j ] + dp[ i - tt[ k ][ j ] ][ k ].TT );
					if( mys < dp[ i ][ j ] ) dp[ i ][ j ] = mys;
				}
			}
		}
		state current = dp[ T ][ N ];
		for( int i = T; i >= 0; i-- ) {
			if( dp[ i ][ N ] < current ) current = dp[ i ][ N ];
		}
		if( current.TT > T ) printf("-1\n");
		else printf("%d %d\n", current.C, current.TT );
	}
	return 0;
}
