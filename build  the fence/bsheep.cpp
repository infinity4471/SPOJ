#include <cstdio>
#include <algorithm>
#include <stack>
#include <cmath>
#include <map>
#include <utility>

#define INF 100010

using namespace std;

struct pt {
	int x,y,idx;
};

pt minim;
int hull[ INF + 1 ], size = 0;
double circum;

int CCW( pt a, pt b, pt c )
{
	return ( b.x - a.x ) * ( c.y - a.y ) - ( c.x - a.x ) * ( b.y - a.y );
}

int dist( pt a, pt b )
{
	return ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y );
}

bool cmp( pt a, pt b )
{
  int ccw = CCW( minim, a, b );
  if( ccw != 0 ) {
    return ccw > 0;
  }
  int dist1 = dist( minim, a ), dist2 = dist( minim, b );
  if( dist1 == dist2 ) return a.idx < b.idx;
  return dist1 > dist2;
}

void graham( pt* p, int N )
{
	int i;
	minim.x = INF;
	minim.y = INF;
	for( i = 0; i < N; i++ ) {
		if( p[ i ].y <  minim.y ) {
			minim = p[ i ];
		}
		else if( p[ i ].y == minim.y ) {
			if( p[ i ].x < minim.x ) {
				minim = p[ i ];
			}
		}
	}
	sort( p , p + N, cmp );
	pt stack[ N + 1 ];
	size = 0;
	for( i = 0; i < N; i++ ) {
		while( size >= 2 && CCW( stack[ size - 2 ], stack[ size - 1 ] , p[ i ] ) <= 0 ) {
			size--;
		}
		stack[ size++ ] = p[ i ];
	}
	circum = 0;
	for( i = 0; i < size && stack[ i ].idx != 0; i++ ) {
		circum += sqrt( dist( stack[ i ], stack[ (i + 1 ) % size ] ) );
		hull[ ( i + 1 ) % size ] = stack[ i ].idx;
	}
	size = i;
}

int main( void )
{
	int T;
	scanf("%d", &T);
	while( T-- ) {
		int N, j = 0;
		scanf("%d", &N);
		pt pts[ N ], pp;
		map< pair< int ,int >, bool > mm;
		for( int i = 0; i < N; i++ ) {
			int x,y;
			scanf("%d%d", &x, &y );
			if( !mm[ make_pair( x, y ) ] ) {
				mm[ make_pair( x, y ) ] = true;
				pts[ j ].x = x;
				pts[ j ].y = y;
				pts[ j ].idx = i + 1;
				j++;
			}
		}
		graham( pts, j );
		printf("%0.2lf\n%d", circum, hull[ 0 ] );
		for( int i = 1; i < size; i++ ) {
			printf(" %d", hull[ i ] );
		}
		printf("\n");
		if( T ) {
			printf("\n");
		}
	}
	return 0;
}
