#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
 
#define X first
#define Y second
#define mp make_pair
#define pb push_back
 
#define MAXN 1001000
#define INF 0xf3f3f3f3f3LL
 
using namespace std;
 
typedef long long ll;
 
stack< int > nodes;
vector< int > G[ MAXN + 1 ], T[ MAXN + 1 ], S[ MAXN + 1 ];
int R[ MAXN + 1 ];
 
int SCC[ MAXN + 1 ], c_size[ MAXN + 1 ], val[ MAXN + 1 ], cnt = 0;
bool visited[ MAXN + 1 ];
 
ll dp[ MAXN + 1 ];
vector< int > topo;
 
void dfs1( int s )
{
	visited[ s ] = true;
	for( int i = 0; i < ( int )G[ s ].size(); i++ ) {
		int u = G[ s ][ i ];
		if( visited[ u ] ) continue;
		dfs1( u );
	}
	nodes.push( s );
}
 
void dfs2( int s )
{
	SCC[ s ] = cnt;
	c_size[ cnt ]++;
	val[ cnt ] += R[ s ];
	visited[ s ] = false;
	for( int i = 0; i < ( int )T[ s ].size(); i++ ) {
		int u = T[ s ][ i ];
		if( !visited[ u ] ) continue;
		dfs2( u );
	}
}
 
void toposort( int s )
{
	visited[ s ] = true;
	for( int i = 0; i < ( int )S[ s ].size(); i++ ) {
		int u = S[ s ][ i ];
		if( visited[ u ] ) continue;
		toposort( u );
	}
	topo.pb( s );
}
 
ll longest_path( int s, int e )
{
	for( int i = 0; i < ( int )topo.size(); i++ ) dp[ topo[ i ] ] = ( ll )INF;
	dp[ s ] = -val[ s ];
	for( int i = ( int )topo.size() - 1; i >= 0; i-- ) {
		int u = topo[ i ];
		for( int j = 0; j < ( int )S[ u ].size(); j++ ) {
			int v = S[ u ][ j ];
			dp[ v ] = min( dp[ v ], dp[ u ] - val[ v ] );
		}
	}
	return -dp[ e ];
}
 
int main( void )
{
	int N, M, s, e, u, v;
	scanf("%d%d%d%d", &N, &M, &s, &e );
	for( int i = 1; i <= N; i++ ) {
		scanf("%d", &R[ i ] );
	}
	for( int i = 0; i < M; i++ ) {
		scanf("%d%d", &u, &v );
		G[ u ].pb( v );
		T[ v ].pb( u );
	}
	for( int i = 1; i <= N; i++ ) {
		if( !visited[ i ] ) dfs1( i );
	}
	while( !nodes.empty() ) {
		int u = nodes.top();
		nodes.pop();
		if( visited[ u ] ) {
			cnt++;
			dfs2( u );
		}
	}
	for( int i = 1; i <= N; i++ ) {
		for( int j = 0; j < ( int )G[ i ].size(); j++ ) {
			int u = i, v = G[ i ][ j ];
			if( SCC[ u ] != SCC[ v ] ) {
				S[ SCC[ u ] ].pb( SCC[ v ] );
			}
		}
	}
	memset( visited, 0, sizeof( visited ) );
	for( int i = 1; i <= cnt; i++ ) {
		if( !visited[ i ] ) toposort( i );
	}
	printf("%lld\n", longest_path( SCC[ s ], SCC[ e ] ) );
	return 0;
}
