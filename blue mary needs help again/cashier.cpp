#include <cstdio>
#include <algorithm>
#include <cassert>

#define MAXN 500110
#define INF 1234567890
#define BASE 200000

using namespace std;

typedef long long ll;

struct node {
	int sum, flag1, flag2;
	bool isup1, isup2;
};

node segtree[ 4*MAXN + 1 ];

void init( int n, int l, int r )
{
	if( l == r ) {
		segtree[ n ].sum = 0;
		segtree[ n ].flag1 = 0;
		segtree[ n ].flag2 = 0;
		segtree[ n ].isup1 = 0;
		segtree[ n ].isup2 = 0;
	} else {
		init( 2*n, l, ( l + r ) / 2 );
		init( 2*n + 1, ( l + r ) / 2 + 1, r );
		segtree[ n ].sum = 0;
		segtree[ n ].flag1 = 0;
		segtree[ n ].flag2 = 0;
		segtree[ n ].isup1 = 0;
		segtree[ n ].isup2 = 0;
	}
}

void unflag1( int n, int l, int r )
{
	if( segtree[ n ].isup1 ) {
		segtree[ n ].sum = ( r - l + 1 ) * segtree[ n ].flag1;
		if( l != r ) {
			segtree[ 2*n ].isup1 = true;
			segtree[ 2*n + 1 ].isup1 = true;
			segtree[ 2*n ].flag1 = segtree[ n ].flag1;
			segtree[ 2*n + 1 ].flag1 = segtree[ n ].flag1;
		}
		segtree[ n ].isup1 = false;
		segtree[ n ].flag1 = 0;
	}
}

void unflag2( int n, int l, int r )
{
	unflag1( n, l, r );
	if( segtree[ n ].isup2 ) {
		segtree[ n ].sum += ( r - l + 1 ) * segtree[ n ].flag2;
		if( l != r ) {
			segtree[ 2*n ].isup2 = true;
			segtree[ 2*n + 1 ].isup2 = true;
			segtree[ 2*n ].flag2 = segtree[ n ].flag2;
			segtree[ 2*n + 1 ].flag2 = segtree[ n ].flag2;
		}
		segtree[ n ].isup2 = false;
		segtree[ n ].flag2 = 0;
	}
}
void update1( int n, int l, int r, int i, int j, int val )
{
	if( l > j || r < i ) {
		unflag1( n, l, r );
	}
	else if( i <= l && r <= j ) {
		segtree[ n ].isup1 = true;
		segtree[ n ].flag1 = val;
		unflag1( n, l, r );
	} else {
		unflag1( n, l, r );
		update1( 2*n, l, ( l + r ) / 2, i, j, val );
		update1( 2*n + 1, ( l + r ) / 2 + 1, r, i, j, val );
		if( l != r ) {
			segtree[ n ].sum = segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum;
		}
	}
}

void update2( int n, int l, int r, int i, int j, int val )
{
	if( l > j || r < i ) {
		unflag2( n, l, r );
	}
	else if( i <= l && r <= j ) {
		segtree[ n ].isup2 = true;
		segtree[ n ].flag2 = val;
		unflag2( n, l, r );
	} else {
		unflag2( n, l, r );
		update2( 2*n, l, ( l + r ) / 2, i, j, val );
		update2( 2*n + 1, ( l + r ) / 2 + 1, r, i, j, val );
		if( l != r ) {
			segtree[ n ].sum = segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum;
		}
	}
}
int kth( int n, int l, int r, int k )
{
	if( l == r ) {
		return l;
	}
	unflag2( 2*n, l, ( l + r ) / 2 );
	unflag2( 2*n + 1, ( l + r ) / 2 + 1, r );
	if( segtree[ 2*n ].sum < k ) {
		return kth( 2*n + 1, ( l + r ) / 2 + 1, r, k - segtree[ 2*n ].sum );
	} else {
		return kth( 2*n, l, ( l + r ) / 2, k );
	}
}

int query( int n, int l, int r, int i, int j )
{
	if( l > j || r < i ) {
		return 0;
	}
	unflag2( n, l, r );
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
		int Q,minim, aftermin, leave = 0;
		scanf("%d%d", &Q, &minim );
		minim += BASE;
		aftermin = minim;
		init( 1, 1, MAXN );
		while( Q-- ) {
			scanf("\n");
			char c;
			int val;
			c = getchar_unlocked();
			scanf("%d", &val );
			if( c == 'I' ) {
				if( val + BASE >= minim ) {
					update2( 1, 1, MAXN, val + aftermin - minim + BASE, val + aftermin - minim + BASE, 1 );
				}
			}
			else if( c == 'A' ) {
				aftermin -= val;
			}
			else if( c == 'S' ) {
				aftermin += val;
				leave += query( 1, 1, MAXN, 1, aftermin - 1 );
				update1( 1, 1, MAXN, 1, aftermin - 1, 0 );
			} else {
				val = segtree[ 1 ].sum - val + 1;
				if( val <= 0 ) {
					printf("-1\n");
				} else {
					int k = kth( 1, 1, MAXN, val ) - aftermin + minim- BASE;
					printf("%d\n", k );
				}
			}
		}
		printf("%d\n", leave );
	}
	return 0;
}
