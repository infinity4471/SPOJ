#include <cstdio>
#include <algorithm>
#include <utility>
#include <queue>
#include <vector>

#define MAX 100
#define PPL 13
#define INF 1000000000

using namespace std;

typedef pair< int ,int > pii;

int ans = INF;
bool grid[ MAX + 1 ][ MAX + 1 ];
int dist[ MAX + 1 ][ MAX + 1 ][ PPL + 1 ], N, M, curdx;
bool visited[ MAX + 1 ][ MAX + 1 ];
vector< pii > points( PPL + 1 );
queue< pii > q;

void init()
{
	ans = INF;
	for( int i = 0; i <= N; i++ ){
		for( int j = 0; j <= M; j++ ) {
			grid[ i ][ j ] = 0;
			visited[ i ][ j ] = false;
			for( int k = 0; k <= PPL; k++ ) {
				dist[ i ][ j ][ k ] = INF;
			}
		}
	}
	points.clear();
}

void check( int x, int y, int w )
{
	pii a = make_pair( x, y );
	if( x <= 0 || y <= 0 || x > N || y > M || visited[ x ][ y ] || !grid[ x ][ y ] ) {
		return;
	}
	q.push( a );
	dist[ x ][ y ][ curdx ] = w + 1;
	visited[ x ][ y ] = true;
}

void bfs( pii a, int k )
{
	while( !q.empty() ) {
		q.pop();
	}
	for( int i = 0; i <= N; i++ ) {
		for( int j = 0; j <= M; j++ ) {
			visited[ i ][ j ] = false;
		}
	}
	curdx = k;
	q.push( a );
	dist[ a.first ][ a.second ][ curdx ] = 0;
	visited[ a.first ][ a.second ] = true;
	while( !q.empty() ) {
		pii a = q.front();
		q.pop();
		int x = a.first, y = a.second, w = dist[ x ][ y ][ curdx ];
		check( x + 1, y , w );
		check( x - 1, y , w );
		check( x, y - 1 , w );
		check( x, y + 1 , w );
	}
}

void rotate( int dd )
{ 
	vector< int > dx;
	for( int i = 0; i <= dd; i++ ) {
		dx.push_back( i );
	}	
	do {
		int distance = 0;
		for( int i = 1; i <= dd; i++ ) {
			distance += dist[ points[ dx[ i ] ].first ][ points[ dx[ i ] ].second ][ dx[ i - 1 ] ];
		}
		ans = min( ans, distance );
	} while( next_permutation( dx.begin() + 1, dx.end() - 1 ) );
}

int main( void )
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int dd = 1;
		char c;
		scanf("%d%d\n",&N, &M );
		init();
		pii tn, aw;
		for( int i = 1; i <= N; i++ ) {
			for( int j = 1; j <= M; j++ ) {
				c = getchar_unlocked();
				if( c == '#' ) {
					grid[ i ][ j ] = false;
				} else {
					if( c == 'T' ) {
						tn = make_pair( i, j );
					}
					else if( c == 'W' ) {
						aw = make_pair( i, j );
					}
					else if( c == 'C' ) {			
						points[ dd ] = make_pair( i, j );
						dd++;
					}
					grid[ i ][ j ] = true;
				}	
			}
			getchar_unlocked();
		}
		points[ 0 ] = tn;
		points[ dd ] = aw;
		for( int i = 0; i < dd; i++ ) {
			bfs( points[ i ], i );
		}
		rotate( dd );
		if( ans == INF ) {
			printf("Mission Failed!\n");
		} else {
			printf("%d\n", ans );
		}
	}
	return 0;
}
