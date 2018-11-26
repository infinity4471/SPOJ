#include <cstdio>
#include <algorithm>

#define MAXN 20
#define INF 1234567890

using namespace std;

typedef long long ll;

ll memo[ 2*MAXN + 1 ][ 2*MAXN + 1 ];

ll dp( bool* A, int i, int o, int N )
{
	//printf("inside dp\n");
	if( memo[ i ][ o ] != -INF ) {
		return memo[ i ][ o ];
	}
	if( i == 2*N ) {
		if( !o ) {
			return 1;
		}
		return 0;
	}
	if( o < 0 ) {
		return 0;
	}
	if( A[ i ] ) {
		return memo[ i ][ o ] = dp( A, i + 1, o + 1, N );
	} else {
		return memo[ i ][ o ] = dp( A, i + 1, o + 1, N ) + dp( A, i + 1, o - 1, N );
	}
}

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int N,K;
		scanf("%d%d", &N, &K );
		bool A[ 2*MAXN + 1 ] = {0};
		for( int i = 1; i <= K; i++ ) {
			int u;
			scanf("%d", &u );
			A[ u - 1 ] = true;
		}
		for( int i = 0; i <= 2*MAXN; i++ ) {
			for( int j = 0; j <= 2*MAXN; j++ ) {
				memo[ i ][ j ] = -INF;
			}
		}
		dp( A, 0, 0, N );
		printf("%lld\n", memo[ 0 ][ 0 ]  );
	}
	return 0;
}
