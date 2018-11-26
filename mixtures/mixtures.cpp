#include <cstdio>
#include <algorithm>

#define INF 9876543210LL

using namespace std;

int main( void )
{
	int N;
	while( scanf("%d", &N ) != EOF ) {
		int A[ N + 1 ];
		long long S[ N + 1 ], dp[ N + 1 ][ N + 1 ];
		S[ 0 ] = 0;
		for( int i = 1; i <= N; i++ ) {
			scanf("%d", &A[ i ] );
			S[ i ] = S[ i - 1 ] + A[ i ];
			dp[ i ][ i ] = 0;
		}
		for( int l = 2; l <= N; l++ ) {
			for( int i = 1; i <= N - l + 1; i++ ) {
				int j = i + l - 1;
				dp[ i ][ j ] = INF;
				for( int k = i; k < j; k++ ) {
					dp[ i ][ j ] = min( dp[ i ][ j ], dp[ i ][ k ] + dp[ k + 1 ][ j ] + 
								( ( S[ k ] - S[ i - 1 ] ) % 100 ) * ( ( S[ j ] - S[ k ] ) % 100 ) );
				}
			}
		}
		printf("%lld\n", dp[ 1 ][ N ] );
	}
	return 0;
}
