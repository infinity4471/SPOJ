#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAXN 16

using namespace std;

char* produce( int k )
{
	int i = 0;
	char* bin = new char[ MAXN + 1 ];
	while( k > 0 ) {
		bin[ i++ ] = k % 2 + '0';
		k /= 2;
	}
	return bin;
}
		
int main( void )
{
	freopen("test.in","rt",stdin);
	freopen("test.out","wt",stdout);
	int T;
	scanf("%d",&T);
	for( int t = 1; t <= T; t++ ) {
		int N,K, ans = 0;
		scanf("%d%d",&N,&K);
		int graph[ N ][ K ];
		bool edge[ N ][ N ];
		for( int i = 0; i < N; i++ ) {
			for( int j = 0; j < N; j++ ) {
				edge[ i ][ j ] = false;
			}
		}
		for( int i = 0; i < N; i++ ) {
			for( int j = 0; j < K; j++ ) {
				scanf("%d",&graph[ i ][ j ] );
			}
		}
		for( int i = 0; i < N; i++ ) {
			for( int j = i + 1; j < N; j++ ) {
				bool status = true;
				for( int k = 1; k < K; k++ ) {
					if( graph[ i ][ k - 1 ] >= graph[ j ][ k - 1 ] && graph[ i ][ k ] <= graph[ j ][ k ] ) {
						status = false;
					}
					else if( graph[ i ][ k - 1 ] <= graph[ j ][ k - 1 ] && graph[ i ][ k ] >= graph[ j ][ k ] ) {
						status = false;
					}
				}
				if( !status ) {
					edge[ i ][ j ] = true;
					edge[ j ][ i ] = true;
				}
			}
		}
		for( int i = 0; i < 1 << N; i++ ) {
			char* mybin = new char[ MAXN + 1 ];
			mybin = produce( i );
			//printf("%s\n",mybin);
			bool status = true;
			int clique = 0;
			for( int i = 0; i < strlen( mybin ); i++ ) {
				if( mybin[ i ] != '1' ) {
					continue;
				}
				clique++;
				for( int j = i + 1; j < strlen( mybin ); j++ ) {
					if( mybin[ j ] == '1' && edge[ i ][ j ] == false ) {
						status = false;
					}
				}
			}
			if( status ) {
				ans = max( ans, clique );
			}
		}		
		printf("Case #%d: %d\n",t,ans );
	}
	return 0;
}
