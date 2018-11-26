#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX 100001

using namespace std;

int N,dp[ MAX + 1 ][ 2 ],ans = 0;

void traverse(vector< int > graph[],bool visited[],int s)
{
	int in = 1, out = 0;
	visited[ s ] = true;
	dp[ s ][ 0 ] = 0;
	dp[ s ][ 1 ] = 1;
	for(int i = 0; i < graph[ s ].size(); i++ ) {
		int v = graph[ s ][ i ];
		if( !visited[ v ] ) {
			traverse(graph,visited,v);
			in += dp[ v ][ 1 ];
			out += dp[ v ][ 0 ];
		}
	}
	dp[ s ][ 1 ] = min( in, out );
	dp[ s ][ 0 ] = in;
}

void dfs(vector< int > graph[])
{
	bool visited[ N + 1 ];
	for(int i = 0; i <= N; i++ ) {
		visited[ i ] = false;
	}
	for(int i = 1; i <= N; i++ ) {
		if( !visited[ i ] ) {
			traverse(graph,visited,i);
			ans += min(dp[ i ][ 0 ],dp[ i ][ 1 ]);
		}
	}
}

int main( void )
{
	int u ,v;
	scanf("%d",&N);
	vector< int > graph[ N + 1 ];
	for(int i = 0; i < N - 1; i++ ) {
		scanf("%d%d",&u,&v);
		graph[ u ].push_back( v );
		graph[ v ].push_back( u );
	}
	dfs(graph);
	printf("%d\n",ans);
	return 0;
}	
