#include <cstdio>
#include <algorithm>
 
#define MAX 200001
 
using namespace std;
 
int main( void )
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int N;
		scanf("%d",&N);
		int idx[ N + 1 ], move[ N + 1 ];
		for( int i = 1; i <= N; i++ ) {
			scanf("%d",&move[ i ] );
			idx[ i ] = i;
		}
		for( int i = 1; i <= N; i++ ) {
			for( int j = 1; j <= N; j++ ) {
				if( idx[ j ] < idx[ i ] && idx[ j ] >= idx[ i ] - move[ i ] ) {
					idx[ j ]++;
				}
			}
			idx[ i ] -= move[ i ];
		}
		printf("%d",idx[ 1 ] );
		for( int i = 2; i <= N; i++ ) {
			printf(" %d",idx[ i ] );
		}
		printf("\n");
		
	}
	return 0;
}
