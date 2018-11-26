#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 1024

using namespace std;

int N, segtree[ 4*MAXN + 1 ][ 4*MAXN + 1 ];

void build_y( int nx, int lx, int rx, int n, int l, int r )
{
	if( l != r ) {
		build_y( nx, lx, rx, 2*n, l, ( l + r ) / 2 );
		build_y( nx, lx, rx, 2*n + 1, ( l + r ) / 2 + 1, r );
	}
	segtree[ nx ][ n ] = 0;
}

void build_x( int n, int l, int r )
{
	if( l != r ) {
		build_x( 2*n, l, ( l + r ) / 2 );
		build_x( 2*n + 1, ( l + r ) / 2 + 1, r );
	}
	build_y( n, l, r, 1, 0, N - 1 );
}

int sum_y( int nx, int n, int l, int r, int y1, int y2 )
{
	if( r < y1 || l > y2 ) return 0;
	else if( y1 <= l && r <= y2 ) return segtree[ nx ][ n ];
	else return sum_y( nx, 2*n, l, ( l + r ) / 2, y1, y2 ) + sum_y( nx, 2*n + 1, ( l + r ) / 2 + 1, r, y1, y2 );
}

int sum_x( int n, int l, int r, int x1, int x2, int y1, int y2 )
{
	if( r < x1 || l > x2 ) return 0;
	else if( x1 <= l && r <= x2 ) return sum_y( n, 1, 0, N - 1, y1, y2 );
	else return sum_x( 2*n, l, ( l + r ) / 2, x1, x2, y1, y2 ) + sum_x( 2*n + 1, ( l + r ) / 2 + 1, r, x1, x2, y1, y2 );
}

void update_y( int nx, int lx, int rx, int n, int l, int r, int x, int y, int val )
{
	if( l == r ) {
		if( lx == rx ) segtree[ nx ][ n ] = val;
		else segtree[ nx ][ n ] = segtree[ 2*nx ][ n ] + segtree[ 2*nx + 1 ][ n ];
		return;
	}
	else if( y <= ( l + r ) / 2 ) update_y( nx, lx, rx, 2*n, l, ( l + r ) / 2, x, y, val );
	else update_y( nx, lx, rx, 2*n + 1, ( l + r ) / 2 + 1, r, x, y, val );
	segtree[ nx ][ n ] = segtree[ nx ][ 2*n ] + segtree[ nx ][ 2*n + 1 ];
}

void update_x( int n, int l, int r, int x, int y, int val )
{
	if( l != r ) {
		if( x <= ( l + r ) / 2 ) update_x( 2*n, l, ( l + r ) / 2, x, y, val );
		else update_x( 2*n + 1, ( l + r ) / 2 + 1, r, x, y, val );
	}
	update_y( n, l, r, 1, 0, N - 1, x, y, val );
}

int readint() {
    int n = 0;
    char c = getchar_unlocked();
    while ( !( '0' <= c && c <= '9' ) ) {
        c = getchar_unlocked();
    }
    while ( '0' <= c && c <= '9' ) {
        n = n * 10 + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

int main( void )
{
	int T;
	T = readint();
	while( T-- ) {
		N = readint();
		build_x( 1, 0, N - 1 );
		do {
			int x1, y1, x2, y2, v;
			char cmd[ 10 ];
			scanf("%s", cmd );
			if( !strcmp( cmd, "END" ) ) break;
			if( !strcmp( cmd, "SET" ) ) {
				x1 = readint();
				y1 = readint();
				v = readint();
				update_x( 1, 0, N - 1, x1, y1, v );
			} else {
				x1 = readint();
				y1 = readint();
				x2 = readint();
				y2 = readint();
				printf("%d\n", sum_x( 1, 0, N - 1, x1, x2, y1, y2 ) );
			}
		} while( true );
	}
	return 0;
}
