#include <cstdio>
#include <algorithm>
#include <vector>

#define X first
#define Y second

using namespace std;

typedef pair< int, int > pii;

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int N, u, ans = 1;
		scanf("%d", &N );
		pii A[ N + 10 ];
		int dp[ N + 10 ];
		for( int i = 1; i <= N; i++ ) {
			scanf("%d", &u );
			A[ i ].X = u + 1001;
		}
		for( int i = 1; i <= N; i++ ) {
			scanf("%d", &u );
			A[ i ].Y = u + 1001;
		}
		sort( A + 1, A + N + 1 );
		dp[ 1 ] = 1;
		for( int i = 2; i <= N; i++ ) {
			dp[ i ] = 1;
			for( int j = i - 1; j > 0; j-- ) {
				if( A[ j ].Y <= A[ i ].Y ) {
					dp[ i ] = max( dp[ i ], dp[ j ] + 1 );
				}
			}
			ans = max( ans, dp[ i ] );
		}
		printf("%d\n", ans );
	}
	return 0;
}
