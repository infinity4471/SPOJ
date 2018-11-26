#include <cstdio>
#include <algorithm>
#include <vector>

#define mp make_pair
#define MAXN 100100

using namespace std;

typedef pair< int, int > pii;
typedef long long ll;

struct nod {
	ll val;
	int flag;
};

int par[ MAXN + 1 ], depth[ MAXN + 1 ], chain[ MAXN + 1 ], head[ MAXN + 1 ], subtree[ MAXN + 1 ], chaind[ MAXN + 1 ], size[ MAXN + 1 ];
int chain_num = 1;
vector< nod > segtree[ MAXN + 1 ];
vector< int > tree[ MAXN + 1 ];

void init( int s, int p, int d )
{
	depth[ s ] = d;
	subtree[ s ] = 1;
	par[ s ] = p;
	for( int i = 0; i < tree[ s ].size(); i++ ) {
		int v = tree[ s ][ i ];
		if( v != p ) {
			init( v, s, d + 1 );
			subtree[ s ] += subtree[ v ];
		}
	}
}

void init_segtree()
{
	for( int i = 1; i <= chain_num; i++ ) {
		segtree[ i ].resize( 4*( size[ i ] + 1 ) );
	}
}

void unflag( int ch, int n, int l, int r )
{
	if( segtree[ ch ][ n ].flag ) {
		segtree[ ch ][ n ].val += ( r - l + 1 ) * segtree[ ch ][ n ].flag;
		if( l != r ) {
			segtree[ ch ][ 2*n ].flag += segtree[ ch ][ n ].flag;
			segtree[ ch ][ 2*n + 1 ].flag += segtree[ ch ][ n ].flag;
		}
		segtree[ ch ][ n ].flag = 0;
	}
}

void update( int ch, int n, int l, int r, int i, int j, int val )
{
	if( r < i || l > j ) {
		unflag( ch, n, l, r );
	}
	else if( i <= l && r <= j ) {
		segtree[ ch ][ n ].flag += val;
		unflag( ch, n, l, r );
	} else {
		unflag( ch, n, l, r );
		update( ch, 2*n, l, ( l + r ) / 2, i, j, val );
		update( ch, 2*n + 1, ( l + r ) / 2 + 1, r, i, j, val );
		if( l != r ) {
			segtree[ ch ][ n ].val = segtree[ ch ][ 2*n ].val + segtree[ ch ][ 2*n + 1 ].val;
		}
	}
}

ll query( int ch, int n, int l, int r, int i, int j )
{
	if( r < i || l > j ) {
		return 0;
	}
	unflag( ch, n, l, r );
	if( i <= l && r <= j ) {
		return segtree[ ch ][ n ].val;
	} else {
		return query( ch, 2*n, l, ( l + r ) / 2, i, j ) + query( ch, 2*n + 1, ( l + r ) / 2 + 1, r, i, j );
	}
}

void heavy_light( int s, int d )
{
	chain[ s ] = chain_num;
	chaind[ s ] = d;
	if( d == 1 ) {
		head[ chain_num ] = s;
	}
	size[ chain_num ] = d;
	int node = 0;
	for( int i = 0; i < tree[ s ].size(); i++ ) {
		int v = tree[ s ][ i ];
		if( v == par[ s ] ) continue;
		if( subtree[ v ] >= subtree[ node ] ) {
			node = v;
		}
	}
	if( node ) {
		heavy_light( node, d + 1 );
	}
	for( int i = 0; i < tree[ s ].size(); i++ ) {
		int v = tree[ s ][ i ];
		if( v == par[ s ] || node == v ) continue;
		chain_num++;
		heavy_light( v, 1 );
	}
}

int LCA( int u, int v )
{
	do {
		if( chain[ u ] == chain[ v ] ) {
			if( depth[ u ] < depth[ v ] ) {
				return u;
			}
			return v;
		}
		int newu = par[ head[ chain[ u ] ] ], newv = par[ head[ chain[ v ] ] ];
		if( depth[ newu ] >= depth[ newv ] ) {
			u = newu;
		} else {
			v = newv;
		}
	} while( true );
}

ll Q( int u, int v )
{
	int lca = LCA( u, v );
	ll ans = 0;
	while( u != -1 ) {
		ans += query( chain[ u ], 1, 1, size[ chain[ u ] ], 1, chaind[ u ] );
		u = par[ head[ chain[ u ] ] ];
	}
	while( v != -1 ) {
		ans += query( chain[ v ], 1, 1, size[ chain[ v ] ], 1, chaind[ v ] );
		v = par[ head[ chain[ v ] ] ];
	}
	while( lca != -1 ) {
		ans -= 2*query( chain[ lca ], 1, 1, size[ chain[ lca ] ], 1, chaind[ lca ] );
		lca = par[ head[ chain[ lca ] ] ];
	}
	return ans;
}

void U( int u, int v )
{
	int lca = LCA( u, v );
	while( u != -1 ) {
		update( chain[ u ], 1, 1, size[ chain[ u ] ], 1, chaind[ u ], 1 );
		u = par[ head[ chain[ u ] ] ];
	}
	while( v != -1 ) {
		update( chain[ v ], 1, 1, size[ chain[ v ] ], 1, chaind[ v ], 1 );
		v = par[ head[ chain[ v ] ] ];
	}
	while( lca != -1 ) {
		update( chain[ lca ], 1, 1, size[ chain[ lca ] ], 1, chaind[ lca ], -2 );
		lca = par[ head[ chain[ lca ] ] ];
	}
}

int main( void )
{
	int N,M, u, v;
	scanf("%d%d", &N, &M );
	for( int i = 0; i < N - 1; i++ ) {
		scanf("%d%d", &u, &v );
		tree[ u ].push_back( v );
		tree[ v ].push_back( u );
	}
	init( 1, -1, 1 );
	heavy_light( 1, 1 );
	init_segtree();
	while( M-- ) {
		char q;
		int u,v;
		scanf("\n%c%d%d", &q, &u, &v );
		if( q == 'Q' ) {
			printf("%d\n", Q( u, v ) );
		} else {
			U( u, v );
		}
	}
	return 0;
}
