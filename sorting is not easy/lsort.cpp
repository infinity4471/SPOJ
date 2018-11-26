#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAXN 1100

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

int N, BIT[ MAXN + 1 ], dp[ MAXN + 1 ][ MAXN + 1 ];
pii A[ MAXN + 1 ];

void update( int i, int val )
{
	while( i <= N ) {
		BIT[ i ] += val;
		i += i & -i;
	}
}

int get( int i )
{
	int S = 0;
	while( i > 0 ) {
		S += BIT[ i ];
		i -= i & -i;
	}
	return S;
}

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int u;
		scanf("%d", &N );
		for( int i = 1; i <= N; i++ ) {
			scanf("%d", &u );
			A[ i ] = mp( u, i );
		}
		sort( A + 1, A + N + 1 );
		for( int i = 1; i <= N; i++ ) dp[ i ][ i ] = A[ i ].Y;
		for( int l = 2; l <= N; l++ ) {
			memset( BIT, 0, sizeof( BIT ) );
			for( int i = 1; i < l; i++ ) update( A[ i ].Y, 1 );
			for( int i = 1; i <= N - l + 1; i++ ) {
				int j = i + l - 1;
				update( A[ j ].Y, 1 );
				int rank1 = A[ i ].Y - get( A[ i ].Y - 1 ), rank2 = A[ j ].Y - get( A[ j ].Y - 1 );
				update( A[ i ].Y, - 1 );
				dp[ i ][ j ] = min( rank1 * l + dp[ i + 1 ][ j ], rank2 * l + dp[ i ][ j - 1 ] );
			}
		}
		printf("%d\n", dp[ 1 ][ N ] );
	}
	return 0;
}
