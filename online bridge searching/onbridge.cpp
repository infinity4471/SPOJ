#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define X first
#define Y second
#define pb push_back
#define mp make_pair

#define MAXN 100100

using namespace std;

typedef pair< int, int > pii;

struct nod {
	int val, flag, isup;
    nod() {
        val = flag = isup = 0;
    }
};

int par[ MAXN + 1 ], depth[ MAXN + 1 ], chain[ MAXN + 1 ], head[ MAXN + 1 ], subtree[ MAXN + 1 ], chaind[ MAXN + 1 ], size[ MAXN + 1 ];
int chain_num = 1;

nod* segtree[ MAXN + 1 ];
vector< int > tree[ MAXN + 1 ];
vector< pii > edges;

int rep[ MAXN + 1 ], rank[ MAXN + 1 ], crucial[ MAXN + 1 ]; // dsu

int find( int u ) {
    if( u == rep[ u ] ) return u;
    else return rep[ u ] = find( rep[ u ] );
}

void Union( int u, int v ) {
    u = find( u );
    v = find( v );
    if( rank[ u ] < rank[ v ] ) {
        rep[ u ] = v;
    } else {
        rep[ v ] = u;
        if( rank[ u ] == rank[ v ] ) rank[ u ]++;
    }
}

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
		segtree[ i ] = new nod[ 4*( size[ i ] + 1 ) ];
    }
}

void unflag( int ch, int n, int l, int r )
{
	if( segtree[ ch ][ n ].isup ) {
		segtree[ ch ][ n ].val = ( r - l + 1 ) * segtree[ ch ][ n ].flag;
		if( l != r ) {
			segtree[ ch ][ n << 1 ].flag = segtree[ ch ][ n ].flag;
			segtree[ ch ][ ( n << 1 ) | 1 ].flag = segtree[ ch ][ n ].flag;
		    segtree[ ch ][ n << 1 ].isup = segtree[ ch ][ ( n << 1 ) | 1 ].isup = true;
        }
		segtree[ ch ][ n ].flag = 0;
        segtree[ ch ][ n ].isup = false;
	}
}

void update( int ch, int n, int l, int r, int i, int j, int val )
{
	if( r < i || l > j ) {
		unflag( ch, n, l, r );
	}
	else if( i <= l && r <= j ) {
        segtree[ ch ][ n ].isup = true;
		segtree[ ch ][ n ].flag = val;
		unflag( ch, n, l, r );
	} else {
		unflag( ch, n, l, r );
		update( ch, n << 1, l, ( l + r ) >> 1, i, j, val );
		update( ch, ( n << 1 ) | 1, ( ( l + r ) >> 1 ) + 1, r, i, j, val );
		if( l != r ) {
			segtree[ ch ][ n ].val = segtree[ ch ][ n << 1 ].val + segtree[ ch ][ ( n << 1 ) | 1 ].val;
		}
	}
}

int query( int ch, int n, int l, int r, int i, int j )
{
	if( r < i || l > j ) {
		return 0;
	}
	unflag( ch, n, l, r );
	if( i <= l && r <= j ) {
		return r - l + 1 - segtree[ ch ][ n ].val;
	} else {
		return query( ch, n << 1, l, ( l + r ) >> 1, i, j ) + query( ch, ( n << 1 ) | 1, ( ( l + r ) >> 1 )  + 1, r, i, j );
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

int doit( int u, int v ) {
    int ans = 0;
    while( chain[ u ] != chain[ v ] ) {
        int H = head[ chain[ u ] ];
        ans += query( chain[ u ], 1, 1, size[ chain[ u ] ], 1, chaind[ u ] );
        update( chain[ u ], 1, 1, size[ chain[ u ] ], 1, chaind[ u ], 1 );
        u = par[ H ];
    }
    if( u == v ) return ans;
    ans += query( chain[ u ], 1, 1, size[ chain[ u ] ], chaind[ v ] + 1, chaind[ u ] );
    update( chain[ u ], 1, 1, size[ chain[ u ] ], chaind[ v ] + 1, chaind[ u ], 1 );
    return ans;
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

int main( void ) {
    int T;
    T = readint();
    while( T-- ) {
        int N, M, u, v, ans = 0;
        N = readint();
        M = readint();
        for( int i = 1; i <= N; i++ ) {
            tree[ i ].clear();
            rank[ i ] = 1;
            rep[ i ] = i;
        }
        for( int i = 1; i <= M; i++ ) {
            u = readint();
            v = readint();
            u++, v++;
            edges.pb( mp( u, v ) );
            if( find( u ) != find( v ) ) {
                tree[ u ].pb( v );
                tree[ v ].pb( u );
                Union( u, v );
                crucial[ i ] = false;
            } else {
                crucial[ i ] = true;
            }
        }
        init( 1, -1, 1 );
        heavy_light( 1, 1 );
        init_segtree();
        for( int i = 0; i < M; i++ ) {
            int u = edges[ i ].X, v = edges[ i ].Y;
            if( !crucial[ i + 1 ] ) {
                ans++;
            } else {
                int lca = LCA( u, v );
                ans -= doit( u, lca );
                ans -= doit( v, lca );
            }
            printf("%d\n", ans );
        }
        chain_num = 1;
        edges.clear();
    }
    return 0;
}
