#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
 
#define MAXN 101000
#define pb push_back
 
using namespace std;
 
int A[ MAXN + 1 ], depth[ MAXN + 1 ], subtree[ MAXN + 1 ], parent[ MAXN + 1 ];
int chain[ MAXN + 1 ], head[ MAXN + 1 ], position[ MAXN + 1 ], chain_num = 1;
 
vector< int > T[ MAXN + 1 ];
map< int, set< int > > S[ MAXN + 1 ];
 
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
	position[ u ] = d;
	S[ chain[ u ] ][ A[ u ] ].insert( d );
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
		if( !S[ chain[ u ] ][ val ].empty() && *( S[ chain[ u ] ][ val ].begin() ) <= position[ u ] ) return true;
		u = parent[ head[ chain[ u ] ] ];
	}
	set< int >::iterator it = S[ chain[ u ] ][ val ].lower_bound( position[ lca ] );
	if( it != S[ chain[ u ] ][ val ].end() && *it <= position[ u ] ) return true;
	while( chain[ lca ] != chain[ v ] ) {
		if( !S[ chain[ v ] ][ val ].empty() && *( S[ chain[ v ] ][ val ].begin() ) <= position[ v ] ) return true;
		v = parent[ head[ chain[ v ] ] ];
	}
	it = S[ chain[ v ] ][ val ].lower_bound( position[ lca ] );
	if( it != S[ chain[ v ] ][ val ].end() && *it <= position[ v ] ) return true;
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
	int N, Q;
	while( scanf("%d%d", &N, &Q ) != EOF ) {
		for( int i = 1; i <= N; i++ ) {
			T[ i ].clear();
			S[ i ].clear();
		}
		chain_num = 1;
		int u, v, vv;
		for( int i = 1; i <= N; i++ ) A[ i ] = readint();
		for( int i = 0; i < N - 1; i++ ) {
			u = readint();
			v = readint();
			T[ u ].pb( v );
			T[ v ].pb( u );
		}
		dfs( 1, 1, -1 );
		HLD( 1, 1 );
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
