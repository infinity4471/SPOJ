#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
 
#define MAX 100000
 
using namespace std;
 
typedef pair< int ,int > pii;
 
vector< pii > graph[ MAX + 1 ];
int P[ MAX + 1 ], depth[ MAX + 1 ], dp[ 20 ][ MAX + 1  ];
long long rmq[ 20 ][ MAX + 1 ] = { 0 };
 
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
 
void prep( int N )
{
	bool visited[ N + 1 ];
	for( int i = 1; i <= N; i++ ) {
		visited[ i ] = false;
	}
	queue< int > q;
	q.push( 1 );
	P[ 1 ] = -1;
	depth[ 1 ] = 0;
	while( !q.empty() ) {
		int v = q.front();
		q.pop();
		visited[ v ] = true;
		for( int i = 0; i < graph[ v ].size(); i++ ) {
			int u = graph[ v ][ i ].first,w = graph[ v ][ i ].second;
			if( !visited[ u ] ) {
				depth[ u ] = depth[ v ] + 1;
				rmq[ 0 ][ u ] = w;
				P[ u ] = v;
				q.push( u );
			}
		}
	}
}
 
void compute( int N )
{
	for( int i = 1; i <= N; i++ ) {
		dp[ 0 ][ i ] = P[ i ];
		for( int j = 1; 1 << j <= N; j++ ) {
			dp[ j ][ i ] = -1;
		}
	}
	for( int j = 1;  1 << j <= N; j++ ) {
		for( int i = 1; i <= N; i++ ) {
			dp[ j ][ i ] = dp[ j - 1 ][ dp[ j - 1 ][ i ] ];
			rmq[ j ][ i ] = max( rmq[ j - 1 ][ i ], rmq[ j - 1  ][ dp[ j - 1 ][ i ] ] );
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
			u = dp[ i ][ u ];
		}
	}
	if( u == v ) {
		return u;
	}
	for( int i = lg; i >= 0; i-- ) {
		if( dp[ i ][ u ] != -1 && dp[ i ][ u ] != dp[ i ][ v ] ) {
			u = dp[ i ][ u ];
			v = dp[ i ][ v ];
		}
	}
	return P[ u ];
}
 
long long query( int u, int v )
{
	int LCA = lca( u, v ),uv,uu;
	long long maxi = 0;
	for( uv = 0; 1 << uv <= depth[ v ]; uv++ );
	uv--;
	for( uu = 0; 1 << uu <= depth[ u ]; uu++ );
	uu--;
	if( !depth[ u ] && !depth[ v ] ) {
		return maxi;
	}
	for( int  i = uu; i >= 0; i-- ) {
		if( depth[ u ] - (1 << i) >= depth[ LCA ] ) {
			maxi = max( maxi, rmq[ i ][ u ] );
			u = dp[ i ][ u ];
		}
	}
	for( int i = uv; i >= 0; i-- ) {
		if( depth[ v ] - (1 << i) >= depth[ LCA ] ) {
			maxi = max( maxi, rmq[ i ][ v ] );
			v = dp[ i ][ v ];
		}
	}
	return maxi;
}
 
int main( void )
{
	while( true ) {
		int N,Q,u,v,w;
		N = readint();
		if( !N ) {
			break;
		}
		for( int i = 0; i <= MAX; i++ ) {
			graph[ i ].clear();
			P[ i ] = -1;
			depth[ i ] = 0;
			for( int j = 0; j < 20; j++ ) {
				rmq[ j ][ i ] = 0;
			}
		}
		for( int i = 1; i < N; i++ ) {
			u = readint();
			v = readint();
			w = readint();
			graph[ u ].push_back( make_pair( v,w ) );
			graph[ v ].push_back( make_pair( u,w ) );
		}
		prep( N );
		compute( N );
		Q = readint();
		while( Q-- ) {
			u = readint();
			v = readint();
			printf("%lld\n",query( u , v ) );
		}
	}
	return 0;
}
