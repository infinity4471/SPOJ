#include <cstdio>
#include <algorithm>
#include <map>

#define MAXN 101000

using namespace std;

int BIT[ MAXN + 1 ], val[ MAXN + 1 ], demand[ MAXN + 1 ], ans[ MAXN + 1 ];
map< int, int > index;

void add( int u, int v )
{
	while( u <= MAXN ) {
		BIT[ u ] += v;
		u += ( u & -u );
	}
}

int get( int u )
{
	int S = 0;
	while( u > 0 ) {
		S += BIT[ u ];
		u -= ( u & -u );
	}
	return S;
}

int find( int k )
{
	int lo = 0, hi = MAXN, idx = 0;
	while( lo <= hi ) {
		int mid = ( lo + hi ) / 2;
		if( get( mid ) >= k ) {
			idx = mid;
			hi = mid - 1;
		} else {
			lo = mid + 1;
		}
	}
	return idx;
}

int main( void )
{
	int N, u;
	scanf("%d", &N );
	for( int i = 1; i <= N; i++ ) {
		scanf("%d", &val[ i ] );
	}
	sort( val + 1, val + N + 1 );
	for( int i = 1; i <= N; i++ ) {
		if( !index[ val[ i ] ] ) index[ val[ i ] ] = i;
		add( index[ val[ i ] ], 1 );
		scanf("%d", &demand[ i ] );
	}
	for( int i = N; i > 0; i-- ) {
		int idx = find( demand[ i ] + 1 );
		ans[ i ] = val[ idx ];
		add( index[ val[ idx ] ], -1 );
	}
	for( int i = 1; i <= N; i++ ) {
		printf("%d\n", ans[ i ] );
	}
	return 0;
}
