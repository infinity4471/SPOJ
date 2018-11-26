#include <cstdio>
#include <algorithm>

using namespace std;

int main( void )
{
	int T;
	scanf("%d",&T );
	for( int z = 1; z <= T; z++ ) {
		int N;
		scanf("%d", &N );
		int A[ N + 1 ];
		long long dp[ N + 1 ][ 2 ];
		dp[ 0 ][ 0 ] = 0;
		dp[ 0 ][ 1 ] = 0;
		for( int i = 1; i <= N; i++ ) {
			scanf("%d", &A[ i ] );
		}
		dp[ 1 ][ 0 ] = A[ 1 ];
		dp[ 1 ][ 1 ] = 0;
		for( int i = 2; i <= N; i++ ) {
			dp[ i ][ 0 ] = A[ i ] + max( dp[ i - 2 ][ 0 ], dp[ i - 1 ][ 1 ] );
			dp[ i ][ 1 ] = max( dp[ i - 1 ][ 0 ], dp[ i - 1 ][ 1 ] );
		}
		printf("Case %d: %lld\n", z, max( dp[ N ][ 0 ], dp[ N ][ 1 ] ) );
	}
	return 0;
}
