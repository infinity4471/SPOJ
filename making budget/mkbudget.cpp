#include <cstdio>
#include <algorithm>

#define INF 500
#define MAX 100000000

using namespace std;

int main( void )
{
	int cnt = 1;
	do {
		int N,f,h,s, *emp;
		scanf("%d", &N );
		if( !N ) {
			break;
		}
		emp = new int[ N + 1 ];
		int dp[ N + 1 ][ INF + 1 ];
		scanf("%d%d%d",&h,&s, &f );
		for( int i = 1; i <= N; i++ ) {
			scanf("%d", &emp[ i ] );
		}
		for( int i = 0; i <= N; i++ ) {
			for( int j = 1; j <= INF; j++ ) {
				dp[ i ][ j ] = MAX;
			}
		}
		for( int i = emp[ 1 ]; i <= INF; i++ ) {
			dp[ 1 ][ i ] = i*( h + s );
		}
		for( int i = 2; i <= N; i++ ) {
			for( int j = emp[ i ]; j <= INF; j++ ) {
				for( int k = 1; k <= INF; k++ ) {
					if( k > j ) {
						dp[ i ][ j ] = min( dp[ i - 1 ][ k ] + f*( k - j ) + s*j, dp[ i ][ j ] );
					} else {
						dp[ i ][ j ] = min( dp[ i - 1 ][ k ] + h*( j - k ) + s*j, dp[ i ][ j ] );
					}
				}
			}
		}
		printf("Case %d, cost = $%d\n", cnt++, dp[ N ][ emp[ N ] ] );
	} while( true );
	return 0;
}
