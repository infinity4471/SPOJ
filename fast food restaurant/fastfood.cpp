#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

#define MAXN 1010000
#define INF 1234567890

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;
typedef pair< pii, pii > city;

vector< pii > G[ MAXN + 1 ];

int N, dist[ MAXN + 1 ][ 3 ];

vector< int > compress;
map< int, int > CR;

void dijkstra( int s, int id )
{
	priority_queue< pii, vector< pii >, greater< pii > > Q;
	for( int i = 0; i <= N; i++ ) dist[ i ][ id ] = INF;
	dist[ s ][ id ] = 0;
	Q.push( mp( 0, s ) );
	while( !Q.empty() ) {
		pii u = Q.top();
		Q.pop();
		for( int i = 0; i < G[ u.Y ].size(); i++ ) {
			pii v = G[ u.Y ][ i ];
			if( dist[ v.Y ][ id ] > u.X + v.X ) {
				dist[ v.Y ][ id ] = u.X + v.X;
				Q.push( mp( dist[ v.Y ][ id ], v.Y ) );
			}
		}
	}
}

int state[ MAXN + 1 ], ans[ MAXN + 1 ], BIT[ MAXN + 1 ], query[ MAXN + 1 ];
vector< city > cities;

void init()
{
	for( int i = 0; i <= MAXN; i++ ) BIT[ i ] = INF;
}

void add( int u, int val )
{
	while( u <= MAXN ) {
		BIT[ u ] = min( BIT[ u ], val );
		u += ( u & -u );
	}
}

int get( int u )
{
	int rmq = INF;
	while( u > 0 ) {
		rmq = min( rmq, BIT[ u ] );
		u -= ( u & -u );
	}
	return rmq;
}

int main( void )
{
	init();
	int Q, A, B, C, M, u, v, w, cnt = 0;
	scanf("%d%d%d%d%d", &N, &A, &B, &C, &M );
	for( int i = 0; i < M; i++ ) {
		scanf("%d%d%d", &u, &v, &w );
		G[ u ].pb( mp( w, v ) );
		G[ v ].pb( mp( w, u ) );
	}
	scanf("%d", &Q );
	dijkstra( A, 0 );
	dijkstra( B, 1 );
	dijkstra( C, 2 );
	for( int i = 1; i <= N; i++ ) {
		compress.pb( dist[ i ][ 0 ] );
		compress.pb( dist[ i ][ 1 ] );
		compress.pb( dist[ i ][ 2 ] );
	}
	sort( compress.begin(), compress.end() );
	for( int i = 0; i < ( int )compress.size(); i++ ) {
		if( !CR[ compress[ i ] ] ) CR[ compress[ i ] ] = cnt++;
	}
	for( int i = 1; i <= N; i++ ) {
		dist[ i ][ 0 ] = CR[ dist[ i ][ 0 ] ] + 10;
		dist[ i ][ 1 ] = CR[ dist[ i ][ 1 ] ] + 10;
		dist[ i ][ 2 ] = CR[ dist[ i ][ 2 ] ] + 10;
		cities.pb( mp( mp( dist[ i ][ 0 ], dist[ i ][ 1 ] ), mp( dist[ i ][ 2 ], i ) ) );
	}
	sort( cities.begin(), cities.end() );
	for( int i = 1; i <= Q; i++ ) {
		scanf("%d", &u );
		query[ i ] = u;
	}
	for( int i = 0; i < N; ) {
		int j = i + 1;
		if( get( cities[ i ].X.Y - 1 ) >= cities[ i ].Y.X ) state[ cities[ i ].Y.Y ] = true;
		while( j < N && cities[ j ].X.X == cities[ j - 1 ].X.X ) {
			if( get( cities[ j ].X.Y - 1 ) >= cities[ j ].Y.X ) state[ cities[ j ].Y.Y ] = true;
			j++;
		}
		while( i < j ) {
			add( cities[ i ].X.Y, cities[ i ].Y.X );
			i++;
		}
	}
	for( int i = 1; i <= Q; i++ ) {
		printf("%s\n", state[ query[ i ] ] ? "YES": "NO" );
	}
	return 0;
}
