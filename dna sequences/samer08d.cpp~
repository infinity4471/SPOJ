#include <cstdio>
#include <algorithm>
#include <cstring>
 
#define MAXN 1010
 
using namespace std;
 
static int dp[ MAXN + 1 ][ MAXN + 1 ][ 2 ], suf[ MAXN + 1 ][ MAXN + 1 ];
 
int main( void )
{
	while( true ) {
		int K, N, M;
		scanf("%d", &K );
		if( !K ) {
			break;
		}
		char A[ MAXN + 1 ], B[ MAXN + 1 ];
		scanf("%s%s", &A, &B );
		N = strlen( A );
		M = strlen( B );
		for( int i = 0; i <= N; i++ ) {
			for( int j = 0; j <= M; j++ ) {
				dp[ i ][ j ][ 0 ] = dp[ i ][ j ][ 1 ] = 0;
				suf[ i ][ j ] = 0;
			}
		}
		for( int i = 1; i <= N; i++ ) {
			for( int j = 1; j <= M; j++ ) {
				bool status = true;
				int len = 0;
				dp[ i ][ j ][ 1 ] = dp[ i ][ j ][ 0 ] = max( dp[ i - 1 ][ j ][ 0 ], dp[ i ][ j - 1 ][ 0 ] );
				if( A[ i - 1 ] == B[ j - 1 ] ) {
					suf[ i ][ j ] = suf[ i - 1 ][ j - 1 ] + 1;
					dp[ i ][ j ][ 1 ] = max( dp[ i ][ j ][ 1 ], dp[ i - 1 ][ j - 1 ][ 1 ] + 1 );
					if( suf[ i ][ j ] >= K ) {
						dp[ i ][ j ][ 0 ] = max( dp[ i - K ][ j - K ][ 1 ] + K,dp[ i ][ j ][ 0 ] );
					}
				} 
			}
		}
		printf("%d\n", dp[ N ][ M ][ 0 ] );
	}
	return 0;
}
