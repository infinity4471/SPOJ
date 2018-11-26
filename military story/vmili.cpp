#include <cstdio>
#include <algorithm>
#include <vector>
 
#define MAXN 4001
#define INF 10000000
 
using namespace std;
 
struct pt {
	int x,y,idx;
};
 
pt minim;
vector< pt > hull;
 
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
	if( dist1 != dist2 ) {
		return dist1 < dist2;
	}
	return a.idx < b.idx;
}

bool cmp1( pt a, pt b )
{
	return a.idx < b.idx;
}

void graham( vector< pt > P )
{
	int i;
	minim.x = INF;
        minim.y = INF;
        for( int i = 0; i < P.size(); i++ ) {
                if( P[ i ].y <  minim.y ) {
                        minim = P[ i ];
                }
                else if( P[ i ].y == minim.y ) {
                        if( P[ i ].x < minim.x ) {
                                minim = P[ i ];
                        }
                }
        }
	sort( P.begin() , P.end(), cmp );
	pt stack[ MAXN + 1 ];
	int size = 0;
	for( i = 0; i < P.size(); i++ ) {
		while( size >= 2 && CCW( stack[ size - 2 ], stack[ size - 1 ] , P[ i ] ) <= 0 ) {
			size--;
		}
		stack[ size++ ] = P[ i ];
	}
	for( i = 0; i < size; i++ ) {
		hull.push_back( stack[ i ] );
	}
	size = i;
}

int main( void )
{
	int N, cnt = 0;
	scanf("%d", &N );
	vector< pt > P;
	for( int i = 0; i < N; i++ ) {
		pt A;
		scanf("%d%d", &A.x, &A.y );
		A.idx = i;
		P.push_back( A );
	}
	while( P.size() > 2 ) { 
		while( !hull.empty() ) {
			hull.pop_back();
		}
		graham( P );
		sort( hull.begin(), hull.end(), cmp1 );
		sort( P.begin(), P.end(), cmp1 );
		for( int j = hull.size() - 1,i = P.size() - 1; i >= 0; i-- ) {
			if( P[ i ].idx == hull[ j ].idx ) {
				P.erase( P.begin() + i );
				j--;
			}
		}
		cnt++;
	}
	printf("%d\n", cnt );
	return 0;
}
