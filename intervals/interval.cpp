#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXN 50100

using namespace std;

struct node {
	int flag, sum;
};

struct inter {
	int l, r, c;
};

node segtree[ 4*MAXN + 1 ];

bool operator<( inter a, inter b )
{
	return a.r < b.r;
}

void init()
{
	for( int i = 0; i <= 4*MAXN; i++ ) {
		segtree[ i ].flag = 0;
		segtree[ i ].sum = 0;
	}
}

inter make( int l, int r, int c )
{
	inter a;
	a.l = l;
	a.r = r;
	a.c = c;
	return a;
}

void unflag( int n, int l, int r )
{
	if( segtree[ n ].flag ) {
		segtree[ n ].sum = ( r - l + 1 ) * segtree[ n ].flag;
		if( l != r ) {
			segtree[ 2*n ].flag = segtree[ n ].flag;
			segtree[ 2*n + 1 ].flag = segtree[ n ].flag;
		}
		segtree[ n ].flag = 0;
	}
}

void update( int n, int l, int r, int i, int j, int v )
{
	if( r < i || l > j ) {
		unflag( n, l, r );
	}
	else if( i <= l && r <= j ) {
		segtree[ n ].flag = v;
		unflag( n, l, r );
	} else {
		unflag( n, l, r );
		update( 2*n, l, ( l + r ) / 2, i, j, v );
		update( 2*n + 1, ( l + r ) / 2 + 1, r, i, j, v );
		if( l != r ) {
			segtree[ n ].sum = segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum;
		}
	}
}

int query( int n, int l, int r, int i, int j )
{
	if( r < i || l > j ) {
		return 0;
	}
	unflag( n, l, r );
	if( i <= l && r <= j ) {
		return segtree[ n ].sum;
	} else {
		return query( 2*n, l, ( l + r ) / 2, i, j ) + query( 2*n + 1, ( l + r ) / 2 + 1, r, i, j );
	}
}

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		init();
		int N, u, v, w, ans = 0;
		scanf("%d", &N );
		inter A[ N + 1 ];
		for( int i = 1; i <= N; i++ ) {
			scanf("%d%d%d", &u, &v, &w );
			A[ i ] = make( u, v, w );
		}
		sort( A + 1, A + N + 1 );
		for( int i = 1; i <= N; i++ ) {
			int total = A[ i ].c;
			//printf("interval -> %d,%d\n", A[ i ].l, A[ i ].r );
			total -= query( 1, 1, MAXN, A[ i ].l, A[ i ].r );
			if( total <= 0 ) continue;
			int lo = A[ i ].l, hi = A[ i ].r, fin;
			while( lo <= hi ) {
				int mid = ( lo + hi ) / 2;
				int qq = A[ i ].r - mid + 1 - query( 1, 1, MAXN, mid, A[ i ].r );
				if( qq >= total ) {
					fin = mid;
					lo = mid + 1;
				} else {
					hi = mid - 1;
				}
			}
			ans += A[ i ].r - fin + 1 - query( 1, 1, MAXN, fin, A[ i ].r );
			update( 1, 1, MAXN, fin, A[ i ].r, 1 );
		} 			
		printf("%d\n", ans );
	}
	return 0;
}
