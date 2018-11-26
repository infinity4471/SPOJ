#include <cstdio>
#include <algorithm>

#define MAXN 100001

using namespace std;

int BIT[ MAXN + 1 ], N;

void init()
{
	BIT[ 1 ] = 1;
	for( int i = 2; i <= N; i++ ) {
		BIT[ i ] = 0;
	}
}

void add( int i, int x )
{
	while( i <= N ) {
		BIT[ i ] = max( BIT[ i ], x );
		i += ( i & -i );
	}
}

int maxq( int i )
{
	int maxim = 0;
	while( i > 0 ) {
		maxim = max( maxim, BIT[ i ] );
		i -= ( i & -i );
	}
	return maxim;
}

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		scanf("%d", &N );
		init();
		int A[ N + 1 ], B[ N + 1 ], C[ N + 1 ], dp[ N + 1 ], m[ N + 1 ], ans = 1;
		for( int i = 1; i <= N; i++ ) {
			scanf("%d", &B[ i ] );
			m[ B[ i ] ] = i;
		}
		for( int i = 1; i <= N; i++ ) {
			scanf("%d", &C[ i ] );
			A[ i ] = m[ C[ i ] ];
		}
		dp[ 1 ] = 1;
		for( int i = 2; i <= N; i++ ) {
			dp[ i ] = maxq( A[ i ] - 1 ) + 1;
			add( A[ i ], dp[ i ] );
			ans = max( ans, dp[ i ] );
		}
		printf("%d\n", ans );
	}
	return 0;
}
