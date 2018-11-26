#include <cstdio>
#include <algorithm>
 
using namespace std;
 
int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int N,M;
		scanf("%d%d",&N,&M );
		int grid[ N + 1 ][ M + 1 ], dp[ N + 1 ][ M + 1 ];
		for( int i = 1; i <= N; i++ ) {
			for( int j = 1; j <= M; j++ ) {
				scanf("%d",&grid[ i ][ j ]);
				grid[ i ][ j ] = -grid[ i ][ j ];
			}
			
		}
		dp[ N ][ M ] = 0;
		for( int i = M - 1; i > 0; i-- ) {
			dp[ N ][ i ] = max( 0, dp[ N ][ i + 1 ] + grid[ N ][ i ] );
		}
		for( int i = N - 1; i > 0; i-- ) {
			dp[ i ][ M ] = max( 0 ,dp[ i + 1 ][ M ] + grid[ i ][ M ] );
		}
		printf("\n");
		for( int i = N - 1; i > 0; i-- ) {
			for( int j = M - 1; j > 0; j-- ) {
				dp[ i ][ j ] = max( 0, grid[ i ][ j ] + min( dp[ i + 1 ][ j ], dp[ i ][ j + 1 ] ) );
			}
 
		}
		printf("%d\n", dp[ 1 ][ 1 ] + 1 );
	}
	return 0;
}	
