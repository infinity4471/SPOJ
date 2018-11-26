#include <cstdio>
#include <algorithm>

#define MAXN 100010
#define INF 50000010

using namespace std;

typedef unsigned long long llu;

struct pt {
	int x,y, idx;
};

int size;
pt* hull, minim;


long long CCW( pt a, pt b, pt c )
{
	return (long long)( b.x - a.x ) * ( c.y - a.y ) - ( long long )( c.x - a.x ) * ( b.y - a.y );
}
 
llu dist( pt a, pt b )
{
	return (llu)( a.x - b.x ) * ( a.x - b.x ) + (llu)( a.y - b.y ) * ( a.y - b.y );
}
 
bool cmp( pt a, pt b )
{
	long long ccw = CCW( minim, a, b );
	if( ccw != 0 ) {
		return ccw > 0;
	}
	llu dist1 = dist( minim, a ), dist2 = dist( minim, b );
	if( dist1 != dist2 ) {
		return dist1 > dist2;
	}
	return a.idx < b.idx;
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
	for( i = 0; i < size && p[ i ].idx != 0; i++ ) {
		hull[ ( i + 1 ) % size ] = stack[ i ];
	}
	size = i;
}

int tSearch( int myp )
{
	int i = 0, j = size - 1;
	llu dista = 0;
	int idx;
	while( j - i >= 3 ) {
		int k = ( 2*i + j ) / 3;
		int l = ( 2*j + i ) / 3;
		if( dist( hull[ myp ], hull[ k ] ) < dist( hull[ myp ], hull[ l ] ) ) {
			i = k;
		} else {
			j = l;
		}
	}
	idx = i;
	dista = dist( hull[ myp ], hull[ i ] );
	for( int k = i + 1; k <= j; k++ ) {
		if( dist( hull[ myp ], hull[ k ] ) > dista ) {
			dista = dist( hull[ myp ], hull[ k ] );
			idx = k;
		}
	}
	return idx;
}

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int N;
		size = 0;
		minim.x = INF;
		minim.y = INF;
		llu ans = 0, ans2 = 0;
		scanf("%d", &N );
		pt P[ N + 1 ];
		hull = new pt[ N + 1 ];
		for( int i = 0; i < N; i++ ) {
			scanf("%d%d", &P[ i ].x, &P[ i ].y );
			P[ i ].idx = i + 1;
		}
		if( N == 1 ) {
			printf("0\n");
			continue;
		}
		else if( N == 2 ) {
			printf("%llu\n", dist( P[ 0 ], P[ 1 ] ) );
			continue;
		}
		graham( P, N );
		for( int i = 0; i < size; i++ ) {	
			ans = max( ans, dist( hull[ i ], hull[ tSearch( i ) ] ) );
		}
		printf("%llu\n", ans);
		delete [] hull;
	}
	return 0;
}
