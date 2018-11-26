#include <cstdio>
#include <algorithm>
#include <stack>
#include <cmath>
#include <map>
#include <utility>

#define INF 1000000000
 
using namespace std;
 
struct pt {
	long x,y,idx;
};
 
pt minim, hull[ 101 ][ 2 ];
int size[ 2 ],cnt;
 
bool difsign( int a, int b )
{
	return ( a < 0 && b > 0 ) || ( a > 0 && b < 0 );
}
 
long long CCW( pt a, pt b, pt c )
{
	return ( long long )( b.x - a.x ) * ( c.y - a.y ) - ( long long )( c.x - a.x ) * ( b.y - a.y );
}
 
unsigned long long dist( pt a, pt b )
{
	return ( a.x - b.x ) * ( a.x - b.x ) + ( a.y - b.y ) * ( a.y - b.y );
}
 
bool cmp( pt a, pt b )
{
	long long ccw = CCW( minim, a, b );
	if( ccw != 0 ) {
		return ccw > 0;
	}
	unsigned long long dist1 = dist( minim, a ), dist2 = dist( minim, b );
	if( dist1 != dist2 ) {
		return dist1 > dist2;
	}
	return a.idx < b.idx;
}
 
void graham( pt* p, int N,int ii )
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
	size[ ii ] = 0;
	for( i = 0; i < N; i++ ) {
		while( size[ ii ] >= 2 && CCW( stack[ size[ ii ] - 2 ], stack[ size[ ii ] - 1 ] , p[ i ] ) <= 0 ) {
			size[ ii ]--;
		}
		stack[ size[ ii ]++ ] = p[ i ];
	}
	for( i = 0; i < size[ ii ]; i++ ) {
		hull[ ( i + 1 ) % size[ ii ] ][ ii ] = stack[ i ];
	}
}
 
bool onsegment( pt a, pt b, pt c )
{
	if( min( a.x, b.x ) <= c.x && c.x <= max( a.x, b.x ) && min( a.y, b.y ) <= c.y && c.y <= max( a.y, b.y ) ) {
		return true;
	} else {
		return false;
	}
}
 
bool inhull( pt a, int ii )
{
	int i;
	for( i = 1; i < size[ ii ] - 1; i++ ) {
		if( ( difsign( CCW( hull[ i - 1 ][ ii ], hull[ i ][ ii ], a ), CCW( hull[ i ][ ii ], hull[ i + 1 ][ ii ], a )) ) ) {
			return false;
		}
	}
	if( difsign( CCW( hull[ 0 ][ ii ], hull[ 1 ][ ii ], a ), CCW( hull[ size[ ii ] - 1 ][ ii ], hull[ 0 ][ ii ], a ) ) ) {
		return false;
	}
	return true;
}
 
bool intersect( pt A, pt B, pt C, pt D ) {
        return ( difsign(CCW ( A,B,C ) , CCW ( A,B,D ) ) && difsign (CCW ( C, D, A ) , CCW ( C, D, B ) ) );
}
 
void solve( )
{
	int N,M;
	scanf("%d%d", &N, &M );
	bool status = true;
	if( N == 0 && M == 0 ) {
		exit(0);
	}
	pt Ni[ N ], Mi[ M ];
	for( int i = 0; i < N; i++ ) {
		scanf("%ld%ld", &Ni[ i ].x, &Ni[ i ].y );
		Ni[ i ].idx = i + 1;
	}
	for( int i = 0; i < M; i++ ) {
		scanf("%ld%ld", &Mi[ i ].x, &Mi[ i ].y );
		Mi[ i ].idx = N + i + 1;
	}
	graham( Ni, N, 0 );
	graham( Mi, M, 1 );
	hull[ size[ 0 ] ][ 0 ] = hull[ 0 ][ 0 ];
	hull[ size[ 1 ] ][ 1 ] = hull[ 0 ][ 1 ];
	if( size[ 0 ] == 1 && size[ 1 ] == 1 ) {
		if( hull[ 0 ][ 0 ].x != hull[ 0 ][ 1 ].x || hull[ 0 ][ 0 ].y != hull[ 0 ][ 1 ].y ) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	else if( size[ 0 ] == 1 && size[ 1 ] == 2 ) {
		if( !onsegment( hull[ 0 ][ 1 ], hull[ 1 ][ 1 ], hull[ 0 ][ 0 ] ) ) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	else if( size[ 0 ] == 2 && size[ 1 ] == 1 ) {
		if( !onsegment( hull[ 0 ][ 0 ], hull[ 1 ][ 0 ], hull[ 0 ][ 1 ] ) ) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	else if( size[ 0 ] == 2 && size[ 1 ] == 2 ) {
		if( intersect( hull[ 0 ][ 0 ], hull[ 1 ][ 0 ], hull[ 0 ][ 1 ], hull[ 1 ][ 1 ] ) ) {
			printf("NO\n");
		} else {
			printf("YES\n");
		}
	} else {
		for( int i = 0; i < size[ 1 ]&&cnt!=12; i++ ) {
			if( inhull( hull[ i ][ 1 ], 0 ) ) {
				status = false;
			}
		}
		for( int i = 0; i < size[ 0 ]&&cnt!=12; i++ ) {
			if( inhull( hull[ i ][ 0 ], 1 ) ) {
				status = false;
			}
		}
		for( int i = 0; i < size[ 0 ]; i++ ) {
			for( int j = 0; j < size[ 1 ]; j++ ) {
				if( intersect( hull[ i ][ 0 ], hull[ ( i + 1 ) % size[ 0 ] ][ 0 ], 
				hull[ j ][ 1 ], hull[ ( j + 1 ) % size[ 1 ] ][ 1 ] ) ) {
					status = false;
				}
			}
		}
		printf("%s\n", status?"YES":"NO" );
	}
}
 
int main( void )
{
	cnt = 1;
	while( true ) {
		size[ 0 ] = size[ 1 ] = 0;
		solve();
		cnt++;
	}
	return 0;
}
