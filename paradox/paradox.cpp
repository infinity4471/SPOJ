#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

struct edge {
	int v,w;
};

vector< edge >* graph;
int *visited, *state;
bool status;

inline bool mylog( int w, int v )
{
	if( w == v ) {
		return true;
	} else {
		return false;
	}
}

void dfs1( int s )
{
	visited[ s ] = true;
	for( int i = 0; i < graph[ s ].size(); i++ ) {
		int v = graph[ s ][ i ].v, w = graph[ s ][ i ].w;
		if( !visited[ v ] ) {
			state[ v ] = mylog( state[ s ] , w );
			dfs1( v );
		}
	}
}

void dfs2( int s )
{
	visited[ s ] = false;
	for( int i = 0; i < graph[ s ].size(); i++ ) {
		int v = graph[ s ][ i ].v, w = graph[ s ][ i ].w;
		if( !visited[ v ] && mylog( state[ s ] , w ) != state[ v ] ) {
			status = true;
		} else  if( visited[ v ] ) {
			dfs2( v );
		}
	}
}

int main( void )
{
	while( true ) {
		status = false;
		int N, u;
		char cmd[ 10 ];
		scanf("%d",&N);
		if( !N ) {
			break;
		}
		graph = new vector< edge >[ N + 1 ];
		visited = new int[ N + 1 ];
		state = new int[ N + 1 ];
		for( int i = 1; i <= N; i++ ) {
			scanf("%d%s", &u, &cmd );
			edge a;
			a.w = !strcmp( cmd, "true" );
			a.v = u;
			graph[ i ].push_back( a );
			visited[ i ] = false;
		}
		for( int node = 1; node <= N; node++ ) {
			for( int s = 0; s < 2; s++ ) {
				for( int i = 1; i <= N; i++ ) {
					visited[ i ] = false;
				}
				state[ node ] = s;
				dfs1( node );
				dfs2( node );
			}
		}
		if( !status ) {
			printf("NOT PARADOX\n");
		} else {
			printf("PARADOX\n");
		}
		delete [] graph;
		delete [] visited;
		delete [] state;
	}
	return 0;
}
