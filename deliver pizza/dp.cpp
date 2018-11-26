#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#include <cstring>

#define MAXN 501
#define INF 1234567890
#define MAXB 21

using namespace std;

typedef pair< int, int > pii;

struct node {
	int x,y;
};

int N,M;
node s;
vector< node > build;
int grid[ MAXN + 1 ][ MAXN + 1 ], isb[ MAXN + 1 ][ MAXN + 1 ], dist[ MAXN + 1 ][ MAXN + 1 ];
bool status;

bool operator<( const node& a, const node& b )
{
	return dist[ a.x ][ a.y ] > dist[ b.x ][ b.y ];
}

void init()
{
	build.clear();
	for( int i = 1; i <= MAXN; i++ ) {
		for( int j = 1; j <= MAXN; j++ ) {
			grid[ i ][ j ] = 0;
			isb[ i ][ j ] = 0;
			dist[ i ][ j ] = INF;
		}
	}
}
	
node make_node( int x, int y )
{
	node a;
	a.x = x; a.y = y;
	return a;
}

priority_queue< node > pq;

void check( int x1, int y1, int x, int y )
{
	int d;
	if( abs( grid[ x1 ][ y1 ] - grid[ x ][ y ] ) > 1 && !isb[ x1 ][ y1 ] && !isb[ x ][ y ] ) {
		return;
	} else {
		if( isb[ x1 ][ y1 ] || isb[ x ][ y ]  ) {
			d = dist[ x1 ][ y1 ] + 2;
		} else {
			d = dist[ x1 ][ y1 ] + ( abs( grid[ x1 ][ y1 ] - grid[ x ][ y ] ) == 0 ? 1 : 3 );
		}
	}
	if( x > N || y > M || x <= 0 || y <= 0 || dist[ x ][ y ] <= d ) {
		return;
	}
	dist[ x ][ y ] = d;
	pq.push( make_node( x, y ) );
}

void dijkstra()
{
	pq.push( s );
	dist[ s.x ][ s.y ] = 0;
	while( !pq.empty() ) {
		node a = pq.top();
		pq.pop();
		check( a.x, a.y, a.x + 1, a.y );
		check( a.x, a.y, a.x - 1, a.y );
		check( a.x, a.y, a.x, a.y - 1 );
		check( a.x, a.y, a.x, a.y + 1 );
	}
}

int exhaust( int i, int sum1, int sum2, int max1, int max2, int K )
{
	if( !status ) {
		return INF;
	}
	if( i == K ) {
		return max( 2*sum1 - max1, 2*sum2 - max2 );
	}
	int ans = 0, k = dist[ build[ i ].x ][ build[ i ].y ];
	if( k == INF ) {
		status = 0;
		return INF;
	}
	ans = min( INF, min( exhaust( i + 1, sum1 + k, sum2, max( max1, k ), max2, K ),
			exhaust( i + 1, sum1, sum2 + k, max1, max( max2, k ), K ) ) );
	return ans;
}

int main( void )
{
	int C;
	scanf("%d", &C );
	while( C-- ) {
		init();
		scanf("%d%d", &N, &M );
		for( int i = 1; i <= N; i++ ) {
			scanf("\n");
			for( int j = 1; j <= M; j++ ) {
				char c;
				scanf("%c", &c );
				if( '0' <= c && c <= '9' ) {
					grid[ i ][ j ] = c - '0';
				}
				else if( c == '$' ) {
					grid[ i ][ j ] = INF;
					isb[ i ][ j ] = 1;
					build.push_back( make_node( i, j ) );
				}
				else if( c == 'X' ) {
					grid[ i ][ j ] = INF;
					s = make_node( i, j );
					isb[ i ][ j ] = 1;
				}
			}
		}
		dijkstra();
		int K = build.size(), ans = INF;
		status = true;
		ans = exhaust( 0, 0, 0, 0, 0, K );
		if( ans == INF ) {
			printf("-1\n");
		} else {
			printf("%d\n", exhaust( 0, 0, 0, 0, 0, K ) );
		}
	}
	return 0;
}
