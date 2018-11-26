#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXN 101001
#define pb push_back

using namespace std;

vector< int > segtree[ 4*MAXN + 1 ];
int A[ MAXN + 1 ];

void init( int n, int l, int r )
{
	segtree[ n ].resize( r - l + 1 );
	if( l == r ) {
		segtree[ n ][ 0 ] = A[ l ];
	} else {
		int mid = ( l + r ) >> 1, cnt = 0;	
		init( n << 1, l, ( l + r ) >> 1 );
		init( ( n << 1 ) + 1, ( ( l + r ) >> 1 ) + 1, r );
		int i, j, k;
		for( i = 0, j = 0, k = 0; i < segtree[ ( n << 1 ) ].size() && j < segtree[ ( n << 1 ) + 1 ].size(); ++k ) {
			if( segtree[ n << 1 ][ i ] <= segtree[ ( n << 1 ) + 1 ][ j ] ) {
				segtree[ n ][ k ] = segtree[ n << 1 ][ i++ ];
			} else {
				segtree[ n ][ k ] = segtree[ ( n << 1 ) + 1 ][ j++ ];
			}
		}
		while( i < segtree[ n << 1 ].size() ) segtree[ n ][ k++ ] = segtree[ n << 1 ][ i++ ];
		while( j < segtree[ (n << 1 ) + 1 ].size() ) segtree[ n ][ k++ ] = segtree[ ( n << 1 ) + 1 ][ j++ ];
	}
}

int query(int n, int l, int r, int i, int j, int x )
{
	int mid = ( l + r ) >> 1;
	if( l == i && r == j ) return upper_bound( segtree[ n ].begin(), segtree[ n ].end(), x ) - segtree[ n ].begin();
	else if( j <= mid ) return query( n << 1, l, mid, i, j, x );
	else if( i > mid ) return query( ( n << 1 ) | 1, mid + 1, r, i, j, x );
	else return query( n << 1, l, mid, i, mid, x ) + query( ( n << 1 ) | 1, mid + 1, r, mid + 1, j, x );
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
	int N, Q, cnt = 1, u, v, lo, hi, ans;
	while( scanf("%d", &N ) == 1 ) {
		printf("Case %d:\n", cnt++);
		for( int i = 1; i <= N; ++i ) A[ i ] = readint();
		init( 1, 1, N );
		Q = readint();
		while( Q-- ) {
			u = readint();
			v = readint();
			lo = 0, hi = N - 1, ans = 0;
			while( lo <= hi ) {
				int mid = ( lo + hi ) >> 1;
				if( query( 1, 1, N, u, v, segtree[ 1 ][ mid ] ) >= ( v - u + 3 ) >> 1 ) {
					ans = mid;					
					hi = mid - 1;
				} else {
					lo = mid + 1;
				}
			}
			printf("%d\n", segtree[ 1 ][ ans ] );
		}
	}
	return 0;
}
