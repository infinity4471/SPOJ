#include <cstdio>
#include <algorithm>

#define INF 1000000000

using namespace std;

int main( void )
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int N,M, ans = 0;
		scanf("%d%d",&N,&M);
		int A[ N ];
		for( int i = 0; i < N; i++ ) {
			scanf("%d",&A[ i ] );
		}
		sort( A, A + N );
		for( int i = A[ 0 ], j = A[ N - 1 ]; i <= j; ) {
			int mid = ( i + j ) / 2, prev = A[ 0 ],cnt = M - 1,mindist = INF;
			for( int k = 1; k < N; k++ ) {
				if( A[ k ] - prev >= mid ) {
					cnt--;
					mindist = min( mindist, A[ k ] - prev );
					prev = A[ k ];
				}
				if( !cnt ) {
					break;
				}
			}
			if( cnt ) {
				j = mid - 1;
			} else {
				ans = max( ans, mindist );
				i = mid + 1;
			}
		}
		printf("%d\n",ans );
	}
	return 0;
}
