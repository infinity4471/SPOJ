#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

#define MAXN 1100
#define INF 1234567890

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

int N, K, B;
int dp[ 100100 ][ 11 ][ 5 ];
int map[ 3 ][ 1500000 ];

int min5( int a, int b, int c, int d, int e )
{
	return min( min( min( a, b ), min( c, d ) ), e );
} 

int memo( int n, int k, int bit )
{
	if( dp[ n ][ k ][ bit ] != -1 ) return dp[ n ][ k ][ bit ];
	if( k < 0 ) return INF;
	if( n > B ) return dp[ n ][ k ][ bit ] = k == 0 ? 0: INF;
	if( bit == 0 && ( map[ 1 ][ n ] || map[ 2 ][ n ] ) ) return dp[ n ][ k ][ bit ] = INF;
	if( bit == 1 && map[ 1 ][ n ] ) return dp[ n ][ k ][ bit ] = INF;
	if( bit == 2 && map[ 2 ][ n ] ) return dp[ n ][ k ][ bit ] = INF;
	if( bit == 0 ) {
		dp[ n ][ k ][ bit ] = min5( memo( n + 1, k, 0 ), memo( n + 1, k - 1, 1 ), 
					memo( n + 1, k - 1, 2 ), memo( n + 1, k - 1, 3 ), memo( n + 1, k - 2, 4 ) );
	}
	if( bit == 1 ) {
		dp[ n ][ k ][ bit ] = 1 + min5( memo( n + 1, k, 0 ), memo( n + 1, k, 1 ), 
					memo( n + 1, k - 1, 2 ), memo( n + 1, k - 1, 3 ), memo( n + 1, k - 1, 4 ) );
	}
	if( bit == 2 ) {
		dp[ n ][ k ][ bit ] = 1 + min5( memo( n + 1, k, 0 ), memo( n + 1, k - 1, 1 ), 
					memo( n + 1, k, 2 ), memo( n + 1, k - 1, 3 ), memo( n + 1, k - 1, 4 ) );
	}
	if( bit == 3 ) {
		dp[ n ][ k ][ bit ] = 2 + min5( memo( n + 1, k, 0 ), memo( n + 1, k - 1, 1 ), 
					memo( n + 1, k - 1, 2 ), memo( n + 1, k, 3 ), memo( n + 1, k - 2, 4 ) );
	}
	if( bit == 4 ) {
		dp[ n ][ k ][ bit ] = 2 + min5( memo( n + 1, k, 0 ), memo( n + 1, k, 1 ), 
					memo( n + 1, k, 2 ), memo( n + 1, k - 1, 3 ), memo( n + 1, k, 4 ) );
	}
	return dp[ n ][ k ][ bit ];
}

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		memset( map, 0, sizeof( map ) );
		memset( dp, -1, sizeof( dp ) );
		scanf("%d%d%d", &N, &K, &B );
		for( int i = 0; i < N; i++ ) {
			int x,y;
			scanf("%d%d", &x, &y );
			map[ x ][ y ] = 1;
		}
		printf("%d\n", memo( 0, K, 0 ) );
	}
	return 0;
}
