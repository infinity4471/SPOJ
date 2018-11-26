#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
 
#define MAXN 150000
 
using namespace std;
 
int cnt = 0;
bool visited[ MAXN + 1 ];
int scc[ MAXN + 1 ],mscc[ MAXN + 1 ];
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
	int T;
	scanf( "%d",&T );
	while( T-- ) {
		int N,M,K,u,v, pos = -1,ans = -1;
		scanf("%d%d%d",&N,&M,&K);
		init();
		vector< int > graph[ MAXN + 1 ],trans[ MAXN + 1 ];
		for( int i = 0; i < K; ++i ) {
			scanf("%d%d",&u,&v);
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
			scc[ mscc[ i ] ]--;
		}
		for( int i = 1; i <= N; i++ ) {
			if( scc[ mscc[ i ] ] > ans ) {
				ans = scc[ mscc[ i ] ];
				pos = i;
			}
		}
		printf("%d %d\n",pos, ans );
	}
	return 0;
}
