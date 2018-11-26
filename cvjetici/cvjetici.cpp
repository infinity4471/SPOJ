#include <cstdio>
#include <algorithm>

#define MAXN 101000

using namespace std;

struct node {
	int sum, flag;
};

node segtree[ 4*MAXN + 1 ];

void unflag( int n, int l, int r )
{
	if( segtree[ n ].flag ) {
		segtree[ n ].sum += ( r - l + 1 ) * segtree[ n ].flag;
		if( l != r ) {
			segtree[ 2*n ].flag += segtree[ n ].flag;
			segtree[ 2*n + 1 ].flag += segtree[ n ].flag;
		}
		segtree[ n ].flag = 0;
	}
}

void update( int n, int l, int r, int i, int j, int val )
{
	if( r < i || l > j ) {
		unflag( n, l, r );
	}
	else if( i <= l && r <= j ) {
		segtree[ n ].flag += val;
		unflag( n, l, r );
	} else {
		unflag( n, l, r );
		update( 2*n, l, ( l + r ) / 2, i, j, val );
		update( 2*n + 1, ( l + r ) / 2 + 1, r, i, j, val );
		if( l != r ) {
			segtree[ n ].sum = segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum;
		}
	}
}

int query( int n, int l, int r, int idx )
{
	unflag( n, l, r );
	if( l == r ) {
		return segtree[ n ].sum;
	}
	else if( idx <= ( l + r ) / 2 ) query( 2*n, l, ( l + r ) / 2, idx );
	else query( 2*n + 1, ( l + r ) / 2 + 1, r, idx );
}


int main( void )
{
	int N;
	scanf("%d", &N );
	for( int i = 1; i <= N; i++ ) {
		int u, v, qu = 0, qv = 0;
		scanf("%d%d", &u, &v );
		qu = query( 1, 1, MAXN, u );
		qv = query( 1, 1, MAXN, v );
		if( qu ) update( 1, 1, MAXN, u, u, -qu );
		if( qv ) update( 1, 1, MAXN, v, v, -qv );
		printf("%d\n", qu + qv );
		update( 1, 1, MAXN, u + 1, v - 1, 1 );
	}
	return 0;
}
