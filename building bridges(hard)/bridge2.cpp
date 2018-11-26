#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXN 100100
#define X first
#define Y second
#define mp make_pair

using namespace std;

typedef pair< int, int > pii;

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int N, u, sol = 1;
		scanf("%d", &N );
		pii A[ N + 10 ];
		int dp[ N + 10 ], M[ N + 10 ];
		A[ 0 ] = mp( 0, 0 );
		M[ 0 ] = 0;
		for( int i = 1; i <= N; i++ ) {
			scanf("%d", &u );
			M[ i ] = -1;
			A[ i ].X = u + 1001;
		}
		for( int i = 1; i <= N; i++ ) {
			scanf("%d", &u );
			A[ i ].Y = u + 1001;
		}
		sort( A + 1, A + N + 1 );
		M[ 1 ] = 1;
		for( int i = 2; i <= N; i++ ) {
			int lo = 0, hi = i, ans = 0;
			while( lo <= hi ) {
				int mid = ( lo + hi ) / 2;
				if( M[ mid ] == -1 || A[ M[ mid ] ].Y > A[ i ].Y ) {
					hi = mid - 1;
				} else {
					ans = mid;
					lo = mid + 1;
				}
			}
			dp[ i ] = ans + 1;
			if( M[ dp[ i ] ] == -1 || A[ M[ dp[ i ] ] ].Y > A[ i ].Y ) {
				M[ dp[ i ] ] = i;
			}
			sol = max( sol, dp[ i ] );
		}
		printf("%d\n", sol );
	}	
	return 0;
}
