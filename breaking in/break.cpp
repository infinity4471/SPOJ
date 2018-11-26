#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
 
#define MAXN 9001
 
using namespace std;
 
typedef pair< int ,int > pii;
 
int cnt = 0, keepcount = 0;
bool visited[ MAXN + 1 ];
int scc[ MAXN + 1 ],mscc[ MAXN + 1 ], indegree[ MAXN + 1 ],depth[ MAXN + 1 ];

stack< int > cand;
 
void init()
{
	cnt = 0;
	for( int i = 0; i <= MAXN; i++ ) {
		scc[ i ] = 0;
		mscc[ i ] = 0;
		visited[ i ] = false;
		indegree[ i ] = 0;
		depth[ i ] = 0;
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
 
void explore( vector< int > graph[], int s )
{
	if( visited[ s ] ) {
		return;
	}
	keepcount++;
	visited[ s ] = true;
	for( int i = 0; i < graph[ s ].size(); i++ ) {
		explore( graph, graph[ s ][ i ] );
	}
}
 
int main( void )
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int N,M,u,v,maxreach = -1;
		scanf("%d%d",&N,&M);
		init();
		vector< int > graph[ N + 1 ],trans[ N + 1 ],newgraph[ N + 1 ], ans;
		pii edges[ M ];
		for( int i = 0; i < M; i++ ) {
			scanf("%d%d",&v,&u);
			graph[ u ].push_back( v );
			trans[ v ].push_back( u );
			edges[ i ] = make_pair( u , v );
		}
		for( int i = 1; i <= N ; i++ ) {
			if( !visited[ i ] ) {
				dfs1( graph, i );
			}
		}
		while( !cand.empty() ) {
			if( visited[ cand.top() ] ) {
				dfs2( trans, cand.top() );
				cnt++;
			}
			cand.pop();
		}
		for( int i = 0; i < M; i++ ) {
			if( mscc[ edges[ i ].first ] != mscc[ edges[ i ].second ] ) {
				indegree[ mscc[ edges[ i ].second ] ]++;
			}
		}
		bool visited2[ cnt + 1 ];
		for( int i = 0; i <= N; i++ ) {
			visited2[ mscc[ i ] ] = false;
		}
		for( int i = 1; i <= N; i++ ) {
			if( !indegree[ mscc[ i ] ] ) {
				if( !visited2[ mscc[ i ] ] ) {
					keepcount = 0;
					for( int k = 1; k <= N; k++ ) {
						visited[ k ] = false;
					}
					explore( graph, i );
					depth[ mscc[ i ] ] = keepcount;
				}
			}
		}
		for( int i = 0; i < cnt; i++ ) {
			maxreach = max( depth[ i ], maxreach );
		}
		for( int i = 1; i <= N; i++ ) {	
			if( depth[ mscc[ i ] ] == maxreach ) {
				ans.push_back( i );
			}
		}
		if( ans.size() ) {
			printf("%d",ans[ 0 ] );
			for( int i = 1; i < ans.size(); i++ ) {
				printf(" %d",ans[ i]  );
			}
			printf("\n");
		}
	}
	return 0;
}
