#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

#define MAXN 60
#define INF 1234567890

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

pii destination, start;
vector< pii > fire;

int R, C, grid[ MAXN + 1 ][ MAXN + 1 ], dist[ MAXN + 1 ][ MAXN + 1 ][ 2 ]; // 0 for fire, 1 for start
bool visited[ MAXN + 1] [ MAXN + 1 ];
queue< pii > Q;
priority_queue< pii > pq;

bool operator<( pii A, pii B )
{
    return dist[ A.X ][ A.Y ][ 0 ] < dist[ B.X ][ B.Y ][ 0 ];
}

void check1( pii A, int d )
{
	if( A.X > R || A.X <= 0 || A.Y > C || A.Y <= 0 || grid[ A.X ][ A.Y ] || dist[ A.X ][ A.Y ][ 0 ] <= d + 1 ) return;
	pq.push( A );
	dist[ A.X ][ A.Y ][ 0 ] = d + 1;
}

void dijkstra()
{
	for( int i = 0; i < fire.size(); i++ ) {
        dist[ fire[ i ].X ][ fire[ i ].Y ][ 0 ] = 0;
	    pq.push( fire[ i ] );
    }
    while( !pq.empty() ) {
		pii A = pq.top();
		pq.pop();
		int x = A.X, y = A.Y;
		check1( mp( x + 1, y ), dist[ x ][ y ][ 0 ] );
		check1( mp( x - 1, y ), dist[ x ][ y ][ 0 ] );
		check1( mp( x, y + 1 ), dist[ x ][ y ][ 0 ] );
		check1( mp( x, y - 1 ), dist[ x ][ y ][ 0 ] );
	}
}

void check2( pii A, int d )
{ 
    if( A.X > R || A.X <= 0 || A.Y > C || A.Y <= 0 || visited[ A.X ][ A.Y ] || 
		 dist[ A.X ][ A.Y ][ 0 ] <= d + 1 || ( grid[ A.X ][ A.Y ] && A != destination ) ) return;
    Q.push( A );
	visited[ A.X ][ A.Y ] = true;
	dist[ A.X ][ A.Y ][ 1 ] = d + 1;
}

void bfs2()
{
	Q.push( start );
	dist[ start.X ][ start.Y ][ 1 ] = 0;
	visited[ start.X ][ start.Y ] = true;
	while( !Q.empty() ) {
		pii A = Q.front();
		Q.pop();
		int x = A.X, y = A.Y;
		if( mp( x, y ) == destination ) break;
		check2( mp( x + 1, y ), dist[ x ][ y ][ 1 ] );
		check2( mp( x - 1, y ), dist[ x ][ y ][ 1 ] );
		check2( mp( x, y + 1 ), dist[ x ][ y ][ 1 ] );
		check2( mp( x, y - 1 ), dist[ x ][ y ][ 1 ] );
	}
}

int main( void )
{
	scanf("%d%d\n", &R, &C );
	for( int i = 1; i <= R; i++ ) {
		for( int j = 1; j <= C; j++ ) {
			char c;
			scanf("%c", &c );
			if( c == '*' ) fire.pb( mp( i, j ) );
			else if( c == 'X' ) grid[ i ][ j ] = true;
			else if( c == 'D' ) {
				destination = mp( i, j );
				grid[ i ][ j ] = true;
			}
			else if( c == 'S' ) {
				start = mp( i, j );
				grid[ i ][ j ] = true;
			}
		}
		if( i != R ) scanf("\n");
	}
	for( int i = 0; i <= MAXN; i++ ) {
		for( int j = 0; j <= MAXN; j++ ) {
			dist[ i ][ j ][ 0 ] = dist[ i ][ j ][ 1 ] = INF;
		}
	}
	if( !fire.empty() ) dijkstra();
    bfs2();
	int ans = dist[ destination.X ][ destination.Y ][ 1 ];
	if( ans == INF ) printf("KAKTUS\n");
	else printf("%d\n", ans );
	return 0;
}
