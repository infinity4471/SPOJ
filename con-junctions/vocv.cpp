#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAXN 101000
#define MOD 10007

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

int dp[ MAXN + 1 ][ 2 ], C[ MAXN + 1 ][ 2 ];

vector< int > G[ MAXN + 1 ];

void dfs( int u, int p )
{
	int in = 1, out = 0, pr_in = 1, pr_out = 1;
	for( int i = 0; i < G[ u ].size(); i++ ) {
		int v = G[ u ][ i ];
		if( v == p ) continue;
		dfs( v, u );
		in += dp[ v ][ 1 ];
		out += dp[ v ][ 0 ];
		pr_in = ( pr_in * C[ v ][ 1 ] ) % MOD;
		pr_out = ( pr_out * C[ v ][ 0 ] ) % MOD;
	}
	dp[ u ][ 1 ] = min( in, out );
	dp[ u ][ 0 ] = in;
	C[ u ][ 0 ] = pr_in;
	if( in < out ) C[ u ][ 1 ] = pr_in;
	else if( out < in ) C[ u ][ 1 ] = pr_out;
	else C[ u ][ 1 ] = ( pr_in + pr_out ) % MOD;
}

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int N, u, v;
		memset( dp, 0, sizeof( dp ) );
		memset( C, 0, sizeof( C ) );
		scanf("%d", &N );
		for( int i = 0; i <= N; i++ ) G[ i ].clear();
		for( int i = 0; i < N - 1; i++ ) {
			scanf("%d%d", &u, &v );
			G[ u ].pb( v );
			G[ v ].pb( u );
		}
		dfs( 1, -1 );
		printf("%d %d\n", min( dp[ 1 ][ 1 ], dp[ 1 ][ 0 ] ), C[ 1 ][ 1 ] % MOD );
	}
	return 0;
}
