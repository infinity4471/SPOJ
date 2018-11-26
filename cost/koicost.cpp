#include <cstdio>
#include <algorithm>

#define MAXN 100100
#define MOD 1000000000LL

using namespace std;

struct edge {
	int u,v,w;
};

int p[ MAXN + 1 ], rank[ MAXN + 1 ];
long long cnt[ MAXN + 1 ];
unsigned long long ans = 0, total = 0;

void makenode( int u )
{
	p[ u ] = u;
	cnt[ u ] = 1;
}

int find( int u )
{
	if( p[ u ] == u ) {
		return u;
	} else {
		return p[ u ] = find( p[ u ] );
	}
}

void Union( int u, int v )
{
	u = find( u );
	v = find( v );
	p[ u ] = v;
	ans += total*cnt[ v ]*cnt[ u ];
	ans %= (int)MOD;
	cnt[ v ] += cnt[ u ];
}

bool cmp( edge a, edge b )
{
	return a.w > b.w;
}

int main( void )
{
	int N,M;
	scanf("%d%d", &N, &M );
	edge E[ M + 1 ];
	for( int i = 1; i <= N; i++ ) {
		makenode( i );
	}
	for( int i = 1; i <= M; i++ ) {
		scanf("%d%d%d", &E[ i ].u, &E[ i ].v, &E[ i ].w );
		total += E[ i ].w;
	}
	sort( E + 1, E + M + 1, cmp );
	for( int i = 1; i <= M; i++ ) {
		if( find( E[ i ].u ) != find( E[ i ].v ) ) {
			Union( E[ i ].u, E[ i ].v );
		}
		total -= E[ i ].w;
	}
	printf("%llu\n", ans );
	return 0;
}
