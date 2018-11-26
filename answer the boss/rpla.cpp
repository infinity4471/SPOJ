#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <utility>

using namespace std;

typedef pair< int, int > pii;

stack< int > tt;

void topo( int s, vector< int > graph[], bool visited[] )
{
	if( visited[ s ] ) {
		return;
	}
	visited[ s ] = true;
	for( int i = 0; i < graph[ s ].size(); i++ ) {
		topo( graph[ s ][ i ], graph, visited );
	}
	tt.push( s );
}

int main( void )
{
	int T, cnt = 1;
	scanf("%d", &T );
	while( T-- ) {
		int V,E, u , v;
		scanf("%d%d", &V,&E );
		int indeg[ V + 1 ], dp[ V + 1 ];
		bool visited[ V + 1 ];
		vector< int > graph[ V + 1 ], topod, rank[ V + 1 ];
		vector< pii > sol;
		for( int i = 0; i <= V; i++ ) {
			indeg[ i ] = 0;
			visited[ i ] = false;
			dp[ i ] = 0;
		}
		for( int i = 0; i < E; i++ ) {
			scanf("%d%d", &v, &u );
			graph[ u ].push_back( v );
			indeg[ v ]++;
		}
		for( int i = 0; i < V; i++ ) {
			if( !indeg[ i ] ) {
				topo( i, graph, visited );
				dp[ i ] = 1;
			}
		}
		while( !tt.empty() ) {
			topod.push_back( tt.top() );
			tt.pop();
		}
		for( int i = 0; i < topod.size(); i++ ) {
			for( int j = 0; j < graph[ topod[ i ] ].size(); j++ ) {
				int v = graph[ topod[ i ] ][ j ];
				dp[ v ] = max( dp[ v ], dp[ topod[ i ] ] + 1 );
			}
			sol.push_back( make_pair( dp[ topod[ i ] ], topod[ i ] ) );
		}
		printf("Scenario #%d:\n", cnt++ );
		sort( sol.begin(), sol.end() );
		for( int i = 0; i < sol.size(); i++ ) {
			printf("%d %d\n", sol[ i ].first, sol[ i ].second );
		}
	}
	return 0;
}
