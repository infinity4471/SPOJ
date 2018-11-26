#include <cstdio>
#include <algorithm>

using namespace std;

struct stud {
	int a,b;
};

stud* students;
int* grace, N, K;

long long function( int k )
{
	long long ans = 0;
	for( int i = 0; i < N; i++ ) {
		ans += abs( students[ i ].a - ( students[ i ].b + grace[ k ] ) );
	}
	return ans;
}

int search( int i, int j )
{
	int grc;
	long long result;
	while( j - i >= 3 ) {
		int k = ( 2*i + j ) / 3;
		int l = ( 2*j + i ) / 3;
		if( function( k ) > function( l ) ) {
			i = k;
		} else {
			j = l;
		}
	}
	grc = grace[ i ];
	result = function( i );
	for( int k = i + 1; k <= j; k++ ) {
		if( function( k ) < result ) {
			grc = grace[ k ];
			result = function( k );
		}
	}
	return grc;
}

int main( void )
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		scanf("%d",&N);
		students = new stud[ N ];
		for( int i = 0; i < N; i++ ) {
			scanf("%d",&students[ i ].a );
		}
		for( int i = 0; i < N; i++ ) {
			scanf("%d",&students[ i ].b );
		}
		scanf("%d",&K);
		grace = new int[ K ];
		for( int i = 0; i < K; i++ ) {
			scanf("%d",&grace[ i ] );
		}
		sort( grace, grace + K );
		printf("%d\n", search( 0, K - 1 ) );
		delete [] students;
		delete [] grace;
	}
	return 0;
}
