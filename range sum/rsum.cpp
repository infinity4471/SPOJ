#include <cstdio>
#include <algorithm>

#define MAX 200001
#define INF 1000000000

using namespace std;

long long segtree[ 4*MAX + 1 ];
int start;

void init( int i, int l, int r, long long* A )
{
	if( l == r ) {
		segtree[ i ] = A[ l ];
	} else {
		init( 2*i, l, ( l + r ) / 2, A );
		init( 2*i + 1 , (l + r ) / 2 + 1, r , A );
		segtree[ i ] = segtree[ 2*i ] + segtree[ 2*i + 1 ];
	}
}

long long query( int n, int l, int r, int i, int j )
{
	if( r < i || l > j ) {
		return 0;
	}
	else if( i <= l && r <= j ) {
		return segtree[ n ];
	} else {
		return query( 2*n, l, ( l + r ) / 2, i, j ) + query( 2*n + 1 , ( l + r ) / 2 + 1, r, i, j );
	}
}

void update( int n, int l, int r, int idx, int val )
{
	if( l == r && r == idx ) {
		segtree[ n ] = val;
		return;
	}
	else if( idx <= ( l + r ) / 2 ) {
		update( 2*n, l, ( l + r ) / 2, idx, val );
	}
	else if( idx > ( l + r ) / 2 ) {
		update( 2*n + 1 , ( l + r ) / 2 + 1, r, idx ,val );
	}
	segtree[ n ] = segtree[ 2*n ] + segtree[ 2*n + 1 ];
}

int main( void )
{
	int N,Q,u,v,w;
	scanf("%d",&N);
	long long A[ 200002 ] = { 0 };
	for( int i = 100001; i <= 100000 + N; i++ ) {
		scanf("%d",&A[ i ] );
	}
	start = 100000;
	init( 1, 1 , N + start, A );
	scanf("%d",&Q);
	while( Q-- ) {
		long long val;
		scanf("%d",&u );
		if( u == 1 ) {
			scanf("%d%d",&v,&w);
			printf("%lld\n", query( 1, 1, N + 100000, start + v, start + w ) );
		} else {
			scanf("%lld",&val);
			update( 1, 1, N + 100000, start, val );
			--start;
		}
	}
	return 0;
}
