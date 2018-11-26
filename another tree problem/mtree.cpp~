#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

#define MAXN 100100
#define MOD 1000000007LL
#define mp make_pair
#define X first
#define Y second

using namespace std;

typedef pair< int, int > pii;
typedef long long ll;

vector< pii > G[ MAXN + 1 ];

ll S[ MAXN + 1 ], P[ MAXN + 1 ];

void dfs( int s, int p )
{
	for( int i = 0; i < G[ s ].size(); i++ ) {
		int v = G[ s ][ i ].X;
		int w = G[ s ][ i ].Y;
		if( v == p ) continue;
		dfs( v, s );
		ll w1 = ( w + w * P[ v ] % MOD ) % MOD;
		P[ s ] = ( P[ s ] + w1 ) % MOD;
	}
}

void dfs2( int s, int p )
{
	ll total = P[ s ];
	for( int i = 0; i < G[ s ].size(); i++ ) {
		int v = G[ s ][ i ].X;
		ll w = ( ll )G[ s ][ i ].Y;
		if( v == p ) continue;
		dfs2( v, s );
		ll w1 = ( w + w * P[ v ] % MOD ) % MOD;
		total = ( total - w1 ) % MOD;
		S[ s ] = ( S[ s ] + S[ v ] + w1 ) % MOD;
		S[ s ] = ( S[ s ] + total* w1 % MOD ) % MOD;
	}
}

int main( void )
{
	int N, u, v, w;
	scanf("%d", &N );
	for( int i = 0; i < N - 1; i++ ) {
		scanf("%d%d%d", &u, &v, &w );
		G[ u ].push_back( mp( v, w ) );
		G[ v ].push_back( mp( u, w ) );
	}
	dfs( 1, -1 );
	dfs2( 1, -1 );
	printf("%lld\n", S[ 1 ] % MOD );
	return 0;
}
