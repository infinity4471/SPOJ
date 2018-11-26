#include <cstdio>
#include <algorithm>

using namespace std;

struct node {
	int sum;
	bool flag;
};

node* segtree;

void init( int n, int l, int r )
{
	if( l == r ) {
		segtree[ n ].sum = 1;
		segtree[ n ].flag = false;
	} else {
		init( 2*n, l, ( l + r ) / 2 );
		init( 2*n + 1, ( l + r ) / 2 + 1, r );
		segtree[ n ].sum = segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum;
		segtree[ n ].flag = false;
	}
}

void unflag( int n, int l, int r )
{
	if( segtree[ n ].flag ) {
		segtree[ n ].sum = r - l + 1 - segtree[ n ].sum;
		if( l != r ) {
			segtree[ 2*n ].flag = !segtree[ 2*n ].flag;
			segtree[ 2*n + 1 ].flag = !segtree[ 2*n + 1 ].flag;
		}
		segtree[ n ].flag = 0;
	}
}

void update( int n, int l, int r, int i, int j )
{
	if( l > j || r < i ) {
		unflag( n, l, r );
	}
	else if( i <= l && r <= j ) {
		segtree[ n ].flag = !segtree[ n ].flag;
		unflag( n, l, r );
	} else {
		unflag( n, l, r );
		update( 2*n, l, ( l + r ) / 2, i, j );
		update( 2*n + 1, ( l + r ) / 2 + 1, r, i, j );
		if( l != r ) {
			segtree[ n ].sum = segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum;
		}
	}
}

int query( int n, int l, int r, int L )
{
	if( l == r ) {
		if( L - segtree[ n ].sum == 0 ) {
			return l;
		} else {
			return -1;
		}
	}
	unflag( 2*n, l, ( l + r ) / 2 );
	unflag( 2*n + 1, ( l + r ) / 2 + 1, r );
	if( segtree[ 2*n ].sum >= L ) {
		return query( 2*n, l, ( l + r ) / 2, L );
	} else {
		return query( 2*n + 1, ( l + r ) / 2 + 1, r, L - segtree[ 2*n ].sum );
	}
}

int main( void )
{
	int N,M,L;
	scanf("%d%d%d", &N, &M, &L );
	segtree = new node[ 4*N + 1 ];
	init( 1, 1, N );
	while( M-- ) {
		int u,v;
		scanf("%d%d", &u, &v );
		update( 1, 1, N, u, v );
		unflag( 1, 1, N );
		int q = query( 1, 1, N, L );
		if( q == -1 ) {
			printf("AC?\n");
		} else {
			printf("%d\n", q );
		}
	}
	delete [] segtree;
	return 0;
}
