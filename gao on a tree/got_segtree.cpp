#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

#define MAXN 101000
#define pb push_back

using namespace std;

struct node {
	vector< int > array;
};

int A[ MAXN + 1 ], depth[ MAXN + 1 ], subtree[ MAXN + 1 ], parent[ MAXN + 1 ];
int chain[ MAXN + 1 ], head[ MAXN + 1 ], position[ MAXN + 1 ], chain_num = 1;

vector< int > T[ MAXN + 1 ], chains[ MAXN + 1 ];

vector< node > segtree[ MAXN + 1 ];

void dfs( int u, int d, int p )
{
	subtree[ u ] = 1;
	parent[ u ] = p;
	depth[ u ] = d;
	for( int i = 0; i < T[ u ].size(); i++ ) {
		int v = T[ u ][ i ];
		if( v == p ) continue;
		dfs( v, d + 1, u );
	}
}

void HLD( int u, int d )
{
	chain[ u ] = chain_num;
	chains[ chain[ u ] ].pb( u );
	position[ u ] = d;
	if( d == 1 ) head[ chain[ u ] ] = u;
	int node = 0;
	for( int i = 0; i < T[ u ].size(); i++ ) {
		int v = T[ u ][ i ];
		if( v == parent[ u ] ) continue;
		if( subtree[ v ] > subtree[ node ] ) node = v;
	}
	if( node ) HLD( node, d + 1 );
	for( int i = 0; i < T[ u ].size(); i++ ) {
		int v = T[ u ][ i ];
		if( v == node || v == parent[ u ] ) continue;
		chain_num++;
		HLD( v, 1 );
	}
}

void initialize()
{
	for( int i = 1; i <= chain_num; i++ ) {
		segtree[ i ].resize( 4*chains[ i ].size() + 4 );
	}
}

void build( int ch, int n, int l, int r )
{
	segtree[ ch ][ n ].array.resize( r - l + 1 );
	if( l == r ) {
		segtree[ ch ][ n ].array[ 0 ] = A[ chains[ ch ][ l - 1 ] ];
	} else {
		int mid = ( l + r ) / 2, cnt = 0;
		build( ch, 2*n, l, mid );
		build( ch, 2*n + 1, mid + 1, r );
		queue< int > q1, q2, q3;
		for( int i = l; i <= mid; i++ ) q1.push( segtree[ ch ][ 2*n ].array[ i - l ] );
		for( int i = mid + 1; i <= r; i++ ) q2.push ( segtree[ ch ][ 2*n + 1 ].array[ i - mid - 1 ] );
		while( !q1.empty() && !q2.empty() ) {
			if( q1.front() < q2.front() ) {
				q3.push( q1.front() );
				q1.pop();
			} else {
				q3.push( q2.front() );
				q2.pop();
			}
		}
		while( !q1.empty() ) {
			q3.push( q1.front() );
			q1.pop();
		}
		while( !q2.empty() ) {
			q3.push( q2.front() );
			q2.pop();
		}
		while( !q3.empty() ) {
			segtree[ ch ][ n ].array[ cnt++ ] = q3.front();
			q3.pop();
		}
		/*printf("in node %d -> %d, %d array loooks like:", n, l, r );
		for( int i = 0; i < segtree[ ch ][ n ].array.size(); i++ ) {
			printf(" %d", segtree[ ch ][ n ].array[ i ] );
		}
		printf("\n");		
		*/
	}
}

bool query( int ch, int n, int l, int r, int i, int j, int val )
{
	if( r < i || l > j ) return false;
	else if( i <= l && r <= j ) {
		int lo = 0, hi = ( r - l + 1 ), idx = 0;
		while( lo <= hi ) {
			int mid = ( lo + hi ) / 2;
			if( segtree[ ch ][ n ].array[ mid ] < val ) {
				lo = mid + 1;
			} else {
				hi = mid - 1;
				idx = mid;
			}	
		}
		return segtree[ ch ][ n ].array[ idx ] == val;
	} else {
		return query( ch, 2*n, l, ( l + r ) / 2, i, j, val ) || query( ch, 2*n + 1, ( l + r ) / 2 + 1, r, i, j, val );
	}
}

int LCA( int u, int v )
{
	do {
		if( chain[ u ] == chain[ v ] ) {
			return position[ u ] < position[ v ] ? u: v;
		}
		int uu = parent[ head[ chain[ u ] ] ], vv = parent[ head[ chain[ v ] ] ];
		if( depth[ uu ] > depth[ vv ] ) u = uu;
		else v = vv;	
	} while( true );
}

bool find( int u, int v, int val )
{
	int lca = LCA( u, v );
	while( chain[ lca ] != chain[ u ] ) {
		if( query( chain[ u ], 1, 1, chains[ chain[ u ] ].size(), 1, position[ u ], val ) ) return true;
		u = parent[ head[ chain[ u ] ] ];
	}
	if( query( chain[ u ], 1, 1, chains[ chain[ u ] ].size(), position[ lca ], position[ u ], val ) ) return true;
	while( chain[ lca ] != chain[ v ] ) {
		if( query( chain[ v ], 1, 1, chains[ chain[ v ] ].size(), 1, position[ v ], val ) ) return true;
		v = parent[ head[ chain[ v ] ] ];
	}
	if( query( chain[ v ], 1, 1, chains[ chain[ v ] ].size(), position[ lca ], position[ v ], val ) ) return true;
	return false;	
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
	while( !feof( stdin ) ) {
		int N, Q;
		N = readint();
		Q = readint();
		for( int i = 1; i <= chain_num; i++ ) {
			segtree[ i ].clear();
			chains[ i ].clear();
		}
		for( int i = 1; i <= N; i++ ) T[ i ].clear();
		chain_num = 1;
		int u, v, vv;
		for( int i = 1; i <= N; i++ ) A[ i ] = readint();
		for( int i = 0; i < N - 1; i++ ) {
			u = readint();
			v = readint();
			T[ u ].pb( v );
			T[ v ].pb( u );
		}
		dfs( 1, -1, 1 );
		HLD( 1, 1 );
		initialize();
		for( int i = 1; i <= chain_num; i++ ) {
			build( i, 1, 1, chains[ i ].size() );
		}
		while( Q-- ) {
			u = readint();
			v = readint();
			vv = readint();
			if( find( u, v, vv ) ) printf("Find\n");
			else printf("NotFind\n");
		}
		printf("\n");
	}
	return 0;
}
