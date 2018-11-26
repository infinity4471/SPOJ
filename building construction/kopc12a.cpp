#include <cstdio>
#include <algorithm>

using namespace std;

struct bd {
	int h,c;
};

bd* BD;
int N;

bool cmp( bd a, bd b )
{
	if( a.h == b.h ) {
		return a.c < b.c;
	} else {
		return a.h < b.h;
	}
}

long long function( int k )
{
	long long cost = 0;
	for( int i = 0; i < N; i++ ) {
		 cost += abs(BD[ i ].h -  BD[ k ].h ) * BD[ i ].c;
	}
	return cost;
}

long long search( int i, int j )
{
	long long ans;
	while( j - i >= 3 ) {
		int k = ( 2*i + j ) / 3;
		int l = ( 2*j + i ) / 3;
		if( function( k ) > function( l ) ) {
			i = k;
		} else {
			j = l;
		}
	}
	ans = function( i );
	for( int k = i + 1; k <= j; k++ ) {
		ans = min( ans, function( k ) );
	}
	return ans;
}

int main( void )
{
	int T;
	scanf("%d",&T);
	while( T-- ) {		
		scanf("%d",&N);
		BD = new bd[ N ];
		for( int i = 0; i < N; i++ ) {
			scanf("%d",&BD[ i ].h );
		}
		for( int i = 0; i < N; i++ ) {
			scanf("%d",&BD[ i ].c );
		}
		sort( BD, BD + N, cmp );
		printf("%lld\n", search( 0, N - 1 ) );
		delete [] BD;
	}
	return 0;
} 
