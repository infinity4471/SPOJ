#include <cstdio>
#include <algorithm>
#include <vector>

#define INF 1234567890
#define MAXN 100100
#define mp make_pair
#define MIN first
#define MAX second
#define SQRT 320
#define LOG 20

using namespace std;

typedef pair< int, int > pii;

int spar[ MAXN + 1 ], par[ MAXN + 1 ], depth[ MAXN + 1 ], val[ MAXN + 1 ], dp[ MAXN ][ 20 ], N;
pii rmq[ MAXN + 1 ];
vector< int > T[ MAXN + 1 ];

void init()
{
	for( int i = 0; i <= MAXN; i++ ) {
		rmq[ i ] = mp( INF, 0 );
		depth[ i ] = 0;
		spar[ i ] = i;
	}
}

int LCA( int u, int v )
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
	return par[ u ];
}

void compute()
{
	for( int i = 1; i <= N; i++ ) {
		for( int log = 2, j = 1; log <= N; j++, log*=2 ) {
			dp[ i ][ j ] = -1;
		}
	}
	for( int i = 1; i <= N; i++ ) {
		dp[ i ][ 0 ] = par[ i ];
	}
	for( int i = 1; i <= N; i++ ) {
		for( int log = 1,j = 1; log <= depth[ i ]; j++,log*=2 ) {
			dp[ i ][ j ] = dp[ dp[ i ][ j - 1 ] ][ j - 1 ];
		}
	}
}

void dfs( int s, int p, int d )
{
	depth[ s ] = d;
	par[ s ] = p;
	for( int i = 0; i < T[ s ].size(); i++ ) {
		int v = T[ s ][ i ];
		if( v != p ) {
			dfs( v, s, d + 1 );
		}
	}
}

void determine( )
{
	for( int i = 1; i <= N; i++ ) {
		int node = i;
		for( int j = SQRT; j > 0 && node != 1; j-- ) {
			node = par[ node ];
		}
		spar[ i ] = node;
	}
}

void update( int u, int value )
{
	val[ u ] = value;
	for( int i = SQRT; i > 0 && u != -1; i-- ) {
		rmq[ u ].MIN = min( rmq[ u ].MIN, value );
		rmq[ u ].MAX = max( rmq[ u ].MAX, value );
		u = par[ u ];
	}
}

bool query( int u, int lca )
{
	int value = val[ u ];
	while( u != spar[ u ] ) {
		if( val[ u ] != value ) {
			return false;
		}
		u = par[ u ];
	}
	u = par[ u ];
	while( depth[ u ] > depth[ lca ] && u != -1) {
		if( depth[ spar[ u ] ] >= depth[ lca ] ) {
			u = spar[ u ];
			pii q = rmq[ u ];
			if( q.MIN != value || q.MAX != value ) {
				return false;
			}
		}
	}
	while( u != lca && u != -1 ) {
		if( val[ u ] != value ) {
			return false;
		}
		u = par[ u ];
	}
	if( value ) {
		return true;
	}
	return false;
}

int main( void )
{
	int M, u, v;
	scanf("%d", &N );
	for( int i = 1; i < N; i++ ) {
		scanf("%d%d", &u, &v );
		u++;
		v++;
		T[ u ].push_back( v );
		T[ v ].push_back( u );
	}
	scanf("%d", &M );
	init();
	dfs( 1, -1, 1 );
	determine();
	compute();

	while( M-- ) {
		int q, u, v;
		scanf("%d%d%d", &q, &u, &v );
		if( q == 1 ) {
			u++;
			val[ u ] = v;
			update( u, v );
		} else {
			u++;
			v++;
			if( query( u, LCA( u, v ) ) && query( v, LCA( u, v ) ) ) {
				printf("YES\n");
			} else {
				printf("NO\n");
			}
		}
	}
	return 0;
}
