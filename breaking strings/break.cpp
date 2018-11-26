#include <cstdio>
#include <algorithm>

#define INF 1234567890

using namespace std;

int main( void )
{
	int N, M;
	while( scanf("%d%d", &N, &M ) != EOF ) {
		int dp[ M + 2 ][ M + 2 ], A[ M + 2 ], mid[ M + 2 ][ M + 2 ];
		A[ 0 ] = 0;
		A[ M + 1 ] = N;
		dp[ 0 ][ 0 ] = 0;
		dp[ M + 1 ][ M + 1 ] = 0;
		mid[ 0 ][ 0 ] = 0;
		mid[ M + 1 ][ M + 1 ] = M + 1;
		for( int i = 1; i <= M; i++ ) {
			scanf("%d", &A[ i ] );
			dp[ i ][ i ] = 0;
			mid[ i ][ i ] = i;
		}
		for( int i = 0; i <= M; i++ ) {
			dp[ i ][ i + 1 ] = 0;
			mid[ i ][ i + 1 ] = i;
		}
		sort( A, A + M + 2 );
		for( int l = 3; l <= M + 2; l++ ) {
			for( int i = 0; i <= M - l + 2; i++ ) {
				int j = i + l - 1;
				dp[ i ][ j ] = INF;
				int l = mid[ i ][ j - 1 ], r = mid[ i + 1 ][ j ];
				for( int k = l; k <= r; k++ ) {
					if( dp[ i ][ k ] + dp[ k ][ j ] + A[ j ] - A[ i ] < dp[ i ][ j ] ) {
						dp[ i ][ j ] = dp[ i ][ k ] + dp[ k ][ j ] + A[ j ] - A[ i ];
						mid[ i ][ j ] = k;
					}
				}
			}
		}
		printf("%d\n", dp[ 0 ][ M + 1 ] );
	}
	return 0;
}
