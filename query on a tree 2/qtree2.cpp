#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <cmath>
#include <cstring>

#define INF 200000
#define MAX 10001
#define lg( x ) (int)log2( x ) / (int )log2( 2 )

using namespace std;

typedef pair< int ,int > pii;

vector< pii >* graph;
int* P, *depth, dp[ MAX ][ 20 ], root = 1;
long long* dist;
bool* visited;

void prep( int s,int p, int d, int h )
{
	if( visited[ s ] ) {
		return;
	}
	visited[ s ] = true;
	P[ s ] = p;
	dist[ s ] = d;
	depth[ s ] = h;
	for( int i = 0; i < graph[ s ].size(); i++ ) {
		int v = graph[ s ][ i ].first;
		prep( v, s, d + graph[ s ][ i ].second, h + 1 );
	}
}

void compute( int N )
{
	for( int i = 1; i <= N; i++ ) {
		for( int log = 2, j = 1; log <= N; j++, log*=2 ) {
			dp[ i ][ j ] = -1;
		}
	}
	for( int i = 1; i <= N; i++ ) {
		dp[ i ][ 0 ] = P[ i ];
	}
	for( int i = 1; i <= N; i++ ) {
		for( int log = 1,j = 1; log <= depth[ i ]; j++,log*=2 ) {
			dp[ i ][ j ] = dp[ dp[ i ][ j - 1 ] ][ j - 1 ];
		}
	}
}

int lca( int u, int v )
{
	int lg = 0;
	if( depth[ u ] < depth[ v ] ) {
		swap( u, v );
	}
	if( !depth[ u ] ) {
		return u;
	}
	for( lg = 0; 1 << lg <= depth[ u ]; lg++ );
	lg--;
	for( int i = lg; i >= 0; i-- ) {
		if( depth[ u ] - ( 1 << i ) >= depth[ v ] ) {
			u = dp[ u ][ i ];
		}
	}
	if( u == v ) {
		return u;
	}
	for( int i = lg; i >= 0; i-- ) {
		if( dp[ u ][ i ] != -1 && dp[ u ][ i ] != dp[ v ][ i ] ) {
			u = dp[ u ][ i ];
			v = dp[ v ][ i ];
			
		}
	}
	return P[ u ];
}

int kth( int u,int v,int k )
{
	int LCA = lca(u,v ),node;
	k--;
	if( depth[ u ] - depth[ LCA ] >= k ) {
		node = u;
		while( k ) {
			int lg = lg( k );
			k -= 1 << lg;
			node = dp[ node ][ lg ];
		}
	} else {
		node = v;
		k -= depth[ u ] - depth[ LCA ];
		k = depth[ v ] - depth[ LCA ] - k;
		while( k ) {
			int lg = lg( k );
			k -= 1 << lg;
			node = dp[ node ][ lg ];
		}
	}
	return node;
}
			
int main( void )
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int N,u,v,w;
		scanf("%d",&N);
		graph = new vector< pii >[ N + 1 ];
		visited = new bool[ N + 1 ];
		P = new int[ N + 1 ];
		dist = new long long[ N + 1 ];
		depth = new int[ N + 1 ];
		for( int i = 1; i <= N; i++ ) {
			visited[ i ] = false;
		}
		for( int i = 1; i < N; i++) {
			scanf("%d%d%d",&u,&v,&w);
			graph[ u ].push_back( make_pair( v,w ) );
			graph[ v ].push_back( make_pair( u, w ) );
		}
		prep( 1, -1 , 0, 0 );
		compute( N );
		while( true ) {
			char cmd[ 10 ];
			scanf("%s",&cmd);
			if( !strcmp( cmd, "DONE" ) ) {
				break;
			}
			else if( !strcmp( cmd, "DIST" ) ) {
				scanf("%d%d",&u,&v);
				long long d = dist[ u ] + dist[ v ] - 2*dist[ lca( u, v ) ];
				printf("%lld\n",d);
			}
			else {
				scanf("%d%d%d",&u,&v,&w);
				printf("%d\n",kth(u,v,w) );
			}	
		}
		delete [] graph;
		delete [] visited;
		delete [] P;
		delete [] dist;
		delete [] depth;
	}
	return 0;
}
