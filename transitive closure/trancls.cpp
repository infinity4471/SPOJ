#include <cstdio>
#include <algorithm>
 
using namespace std;
 
int main( void )
{
	int T;
	scanf("%d",&T);
	for( int z = 1; z <= T; z++ ) {
		int N,u,v, ans = 0;
		scanf("%d",&N);
		bool G[ N ][ N ], givenin[ N ][ N ];
		for( int i = 0; i < N; i++ ) {
			for( int j = 0; j < N; j++ ) {
				G[ i ][ j ] = 0;
				givenin[ i ][ j ] = 0;
			}			
		}
		for( int i = 0; i < N; i++ ) {
			scanf("%d%d",&u,&v);
			G[ u ][ v ] = true;
			givenin[ u ][ v ] = true;
		}
		for( int k = 0; k < N; k++ ) {
			for( int i = 0; i < N; i++ ) {
				for( int j = 0; j < N; j++ ) {
					G[ i ][ j ] = G[ i ][ j ] || ( G[ i ][ k ] && G[ k ][ j ] );
				}
			}
		}
		for( int i = 0; i < N; i++ ) {
			for( int j = 0; j < N; j++ ) {
				if( G[ i ][ j ] && !givenin[ i ][ j ] ) {
					ans++;
				}
			}
		}
		printf("Case #%d: %d\n", z, ans);
	}
	return 0;
}
