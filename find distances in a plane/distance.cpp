#include <cstdio>
#include <algorithm>
#include <cmath>

#define MAXN 100010
#define INF 50000010
 
using namespace std;
 
typedef unsigned long long llu;

struct pt {
	int x,y, idx;
};
 
int size, N;
pt* hull, minim;
pt X[ MAXN ],Y[ MAXN ];
 
bool cmpx( pt a, pt b )
{
	if( a.x == b.x ) {
		return a.y < b.y;
	} return a.x < b.x;
}
 
bool cmpy( pt a, pt b )
{
	if( a.y == b.y ) {
		return a.x < b.x;
	} return a.y < b.y;
}

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
 
llu combine( llu d, int mid, int lo, int hi, pt& A, pt& B )
{
	int cnt = 0;
	llu newmin = d;
	pt arr[ N + 1 ];
	for( int i = lo; i <= hi; i++ ) { 
		if( fabs( X[ mid ].x - Y[ i ].x ) < d ) {
			arr[ cnt++ ] = Y[ i ];
		}
	}
	for( int i = 0; i < cnt; i++ ) {
		for( int j = i + 1; j < cnt && ( llu )( arr[ j ].y - arr[ i ].y ) * ( arr[ j ].y - arr[ i ].y ) < d; j++ ) {
			if( dist( arr[ i ], arr[ j ] ) < newmin ) {
				newmin = dist( arr[ i ], arr[ j ] );
				A = arr[ i ];
				B = arr[ j ];
			}
		}
	}
	return newmin;
}
 
llu findmin( int i, int j, pt& A, pt& B )
{
	llu mindist = INF;
	if( j - i > 3 ) {
		int lo,hi;
		pt nA[ 2 ],nB[ 2 ];
		for( lo = ( i + j ) / 2; lo >= i && X[ lo ].x == X[ ( i + j ) / 2 ].x; lo-- );
		for( hi = ( i + j ) / 2; hi <= j && X[ hi ].x == X[ ( i + j ) / 2 ].x; hi++ ); 
		llu d1 = findmin( i, lo, nA[ 0 ], nB[ 0 ] );
		llu d2 = findmin( hi ,j, nA[ 1 ], nB[ 1 ] );
		if( d1 < d2 ) {
			mindist = d1;
			A = nA[ 0 ];
			B = nB[ 0 ];
		} else {
			mindist = d2;
			A = nA[ 1 ];
			B = nB[ 1 ];
		}
		mindist = min( combine( mindist, ( i + j ) >> 1, i, j, A, B ), mindist );
	} else {
		for( int k = i; k < j; k++ ) {
			for( int l = k + 1; l <= j; l++ ) {
				if( dist( X[ k ], X[ l ] ) < mindist ) {
					mindist = dist( X[ k ], X[ l ] );
					A = X[ k ];
					B = X[ l ];
				}
			}
		}
	}
	return mindist;
}

int main( void )
{
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
		X[ i ] = Y[ i ] = P[ i ];
	}
	if( N == 1 ) {
		printf("0\n");
		return 0;
	}
	else if( N == 2 ) {
		printf("%llu %llu\n", dist( P[ 0 ], P[ 1 ] ), dist( P[ 0 ], P[ 1 ] ) );
		return 0;
	}
	graham( P, N );
		for( int i = 0; i < size; i++ ) {	
		ans = max( ans, dist( hull[ i ], hull[ tSearch( i ) ] ) );
	}
	sort( X, X + N, cmpx );
	sort( Y, Y + N, cmpy );
	pt A, B;
	ans2 = findmin( 0, N - 1, A, B  );
	printf("%llu %llu\n", ans2, ans );
	delete [] hull;
	return 0;
}
