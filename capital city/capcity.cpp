#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
 
#define MAXN 150000
 
using namespace std;
 
int cnt = 0;
bool visited[ MAXN + 1 ];
int scc[ MAXN + 1 ],mscc[ MAXN + 1 ], degree[ MAXN + 1 ];
stack< int > cand;
 
void init()
{
	cnt = 0;
	for( int i = 0; i <= MAXN; i++ ) {
		scc[ i ] = 0;
		mscc[ i ] = 0;
		visited[ i ] = false;
	}
}
 
void dfs1( vector< int > graph[], int s )
{
	visited[ s ] = true;
	for( int i = 0; i < graph[ s ].size(); i++ ) {
		if( !visited[ graph[ s ][ i ] ] ) {
			dfs1( graph, graph[ s ][ i ] );
		}
	}
	cand.push( s );
}
 
void dfs2( vector< int > graph[], int s )
{
	visited[ s ] = false;
	mscc[ s ] = cnt;
	scc[ cnt ]++;
	for( int i = 0; i < graph[ s ].size(); i++ ) {
		if( visited[ graph[ s ][ i ] ] ) {
			dfs2( graph, graph[ s ][ i ] );
		}
	}
}

int main( void )
{
	int N,M,u,v;
	scanf("%d%d", &N, &M );
	vector< int > graph[ N + 1 ], trans[ N + 1 ],ans;
	init();
	for( int i = 1; i <= M; i++ ) {
		scanf("%d%d", &u, &v );
		graph[ u ].push_back( v );
		trans[ v ].push_back( u );
	}
	for( int i = 1; i <= N; i++ ) {
		if( !visited[ i ] ) {
			dfs1( graph, i );
		}
	}
	while( !cand.empty() ) {
		int v = cand.top();
		cand.pop();
		if( visited[ v ] ) {
			dfs2( trans, v );
			cnt++;
		}
	}
	for( int i = 1; i <= N; i++ ) {
		for( int j = 0; j < graph[ i ].size(); j++ ) {
			int v = graph[ i ][ j ];
			if( mscc[ i ] != mscc[ v ] ) {
				degree[ mscc[ i ] ]++;
			}
		}
	}
	for( int i= 1; i <= N; i++ ) {
		if( !degree[ mscc[ i ] ] ) {
			ans.push_back( i );
		}
	}
	sort( ans.begin(), ans.end() );
	printf("%d\n%d", ans.size(), ans[ 0 ] );
	for( int i = 1; i < ans.size(); i++ ) {
		printf(" %d", ans[ i ] );
	}
	printf("\n");
	return 0;
}
