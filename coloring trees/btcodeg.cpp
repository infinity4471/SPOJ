#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXN 100100
#define MIN first
#define MAX second
#define mp make_pair

using namespace std;

typedef pair< int, int > pii;

int depth[ MAXN + 1 ], chain[ MAXN + 1 ], chaind[ MAXN + 1 ], head[ MAXN + 1 ], subtree[ MAXN + 1 ], size[ MAXN + 1 ], par[ MAXN + 1 ]; 
int val[ MAXN + 1 ], chain_num = 1;
vector< int > T[ MAXN + 1 ];
vector< pii > segtree[ MAXN + 1 ];

void init( int s, int p, int d )
{
	par[ s ] = p;
	subtree[ s ] = 1;
	depth[ s ] = d;
	for( int i = 0; i < T[ s ].size(); i++ ) {
		int v = T[ s ][ i ];
		if( v != p ) {
			init( v, s, d + 1 );
			subtree[ s ] += subtree[ v ];
		}
	}
}

void init_segtree()
{
	for( int i = 1; i <= chain_num; i++ ) {
		segtree[ i ].resize( 4*( size[ i ] ) + 9 );
	}
}

void heavy_light( int s, int d )
{
	chain[ s ] = chain_num;
	chaind[ s ] = d;
	size[ chain_num ] = d;
	if( d == 1 ) {
		head[ chain_num ] = s;
	}
	int node = 0;
	for( int i = 0; i < T[ s ].size(); i++ ) {
		int v = T[ s ][ i ];
		if( v == par[ s ] ) continue;
		if( subtree[ v ] >= subtree[ node ] ) {
			node = v;
		}
	}
	if( node ) {
		heavy_light( node, d + 1 );
	}
	for( int i = 0; i < T[ s ].size(); i++ ) {
		int v = T[ s ][ i ];
		if( v == par[ s ] || v == node ) continue;
		chain_num++;
		heavy_light( v, 1 );
	}
}

void update( int ch, int n, int l, int r, int idx, int col )
{
	if( l == r ) {
		segtree[ ch ][ n ].MIN = col;
		segtree[ ch ][ n ].MAX = col;
		return;
	}
	if( idx <= ( l + r ) / 2 ) {
		update( ch, 2*n, l, ( l + r ) / 2, idx, col );
	} else {
		update( ch, 2*n + 1, ( l + r ) / 2 + 1, r, idx, col );
	}
	segtree[ ch ][ n ].MIN = min( segtree[ ch ][ 2*n ].MIN, segtree[ ch ][ 2*n + 1 ].MIN );
	segtree[ ch ][ n ].MAX = max( segtree[ ch ][ 2*n ].MAX, segtree[ ch ][ 2*n + 1 ].MAX );
}

pii query( int ch, int n, int l, int r, int i, int j )
{
	if( l == i && r == j ) {
		return segtree[ ch ][ n ];
	}
	else if( j <= ( l + r ) / 2 ) {
		return query( ch, 2*n, l, ( l + r ) / 2, i, j );
	}
	else if( i > ( l + r ) / 2 ) {
		return query( ch, 2*n + 1, ( l + r ) / 2 + 1, r, i, j );
	} else {
		pii A = query( ch, 2*n, l, ( l + r ) / 2, i, ( l + r ) / 2 );
		pii B = query( ch, 2*n + 1, ( l + r ) / 2 + 1, r, ( l + r ) / 2 + 1, j );
		return mp( min( A.MIN, B.MIN ), max( A.MAX, B.MAX ) );
	}
}

int LCA( int u, int v )
{
	do {
		if( chain[ u ] == chain[ v ] ) {
			if( depth[ u ] < depth[ v ] ) {
				return u;
			} else {
				return v;
			}
		}
		int newu = par[ head[ chain[ u ] ] ], newv = par[ head[ chain[ v ] ] ];
		if( depth[ newu ] >= depth[ newv ] ) {
			u = newu;
		} else {
			v = newv;
		}
	} while( true );
}

bool Q( int u, int v )
{
	int lca = LCA( u, v ), value = val[ u ];
	while( depth[ u ] >= depth[ lca ] && u != -1 ) {
		pii q;
		if( chain[ u ] == chain[ lca ] ) {
			q = query( chain[ u ], 1, 1, size[ chain[ u ] ], chaind[ lca ], chaind[ u ] );
		} else {
			q = query( chain[ u ], 1, 1, size[ chain[ u ] ], 1, chaind[ u ] );
		}
		if( q.MIN != value || q.MAX != value ) {
			return false;
		}
		u = par[ head[ chain[ u ] ] ];
	}
	while( depth[ v ] >= depth[ lca ] && v != -1 ) {
		pii q;
		if( chain[ v ] == chain[ lca ] ) {
			q = query( chain[ v ], 1, 1, size[ chain[ v ] ], chaind[ lca ], chaind[ v ] );
		} else {
			q = query( chain[ v ], 1, 1, size[ chain[ v ] ], 1, chaind[ v ] );
		}
		if( q.MIN != value || q.MAX != value ) {
			return false;
		}
		v = par[ head[ chain[ v ] ] ];
	}
	if( value == 0 ) {
		return false;
	}
	return true;
}	

int main( void )
{
	int N, M, u, v;
	scanf("%d", &N );
	for( int i = 1; i < N; i++ ) {
		scanf("%d%d", &u, &v );
		u++;
		v++;
		T[ u ].push_back( v );
		T[ v ].push_back( u );
	}
	scanf("%d", &M );
	init( 1, -1, 1 );
	heavy_light( 1, 1 );
	init_segtree();
	while( M-- ) {
		int q, u, v;
		scanf("%d%d%d", &q, &u, &v );
		if( q == 1 ) {
			u++;
			val[ u ] = v;
			update( chain[ u ], 1, 1, size[ chain[ u ] ], chaind[ u ], v );
		} else {
			u++;
			v++;
			printf("%s\n", Q( u,v ) ? "YES" : "NO " );
		}
	}
	return 0;
}
