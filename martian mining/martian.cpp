#include <cstdio>
#include <algorithm>

using namespace std;

int main( void )
{
	do {
		int N,M,c;
		scanf("%d%d", &N, &M );
		if( !N && !M ) {
			break;
		}
		long long A[ N + 1 ][ M + 1 ], B[ N + 1 ][ M + 1 ], dp[ N + 1 ][ M + 1 ];
		for( int i = 0; i <= N; i++ ) {
			for( int j = 0; j <= M; j++ ) {
				dp[ i ][ j ] = 0;
				A[ i ][ j ] = 0;
				B[ i ][ j ] = 0;
			}
		}
		for( int i = 1; i <= N; i++ ) {
			for( int j = 1; j <= M; j++ ) {
				scanf("%d", &c );
				A[ i ][ j ] = A[ i - 1 ][ j ] + A[ i ][ j - 1 ] - A[ i - 1 ][ j - 1 ] + c;
			}
		}
		for( int i = 1; i <= N; i++ ) {
			for( int j = 1; j <= M; j++ ) {
				scanf("%d", &c );
				B[ i ][ j ] = B[ i - 1 ][ j ] + B[ i ][ j - 1 ] - B[ i - 1 ][ j - 1 ] + c;
			}
		}
		for( int i = 1; i <= N; i++ ) {
			for( int j = 1; j <= M; j++ ) {
				dp[ i ][ j ] = max( dp[ i - 1 ][ j ] + A[ i ][ j ] - A[ i - 1 ][ j ],
							dp[ i ][ j - 1 ] + B[ i ][ j ] - B[ i ][ j - 1 ] );
			}
		}
		printf("%lld\n", dp[ N ][ M ] );
	} while( true );
	return 0;
}
