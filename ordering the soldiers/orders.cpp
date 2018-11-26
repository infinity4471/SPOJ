#include <cstdio>
#include <algorithm>

#define MAXN 200001
 
using namespace std;

int BIT[ MAXN + 1 ] = { 0 };

void init()
{
	for( int i = 1; i <= MAXN; i++ ) {
		BIT[ i ] = 0;
	}
}

void add( int pos, int val )
{
	while( pos <= MAXN ) {
		BIT[ pos ] += val;
		pos += ( pos & -pos );
	}
}

int sum ( int pos )
{
	int ans = 0;
	while( pos > 0 ) {
		ans += BIT[ pos ];
		pos -= ( pos & -pos );
	}
	return ans;
}

int R( int pos, int N )
{
	int lo = 1, hi = N;
	//printf("requesting -> %d\n", pos );
	while( lo < hi ) {
		int mid = ( lo + hi ) / 2;
		int S = sum( mid );
		//printf("S( %d ) = %d\n", mid, S );
		if( S < pos ) {
			lo = mid + 1;
		} else {
			hi = mid;
		}
	}
	//printf("returning -> %d\n", lo );
	return lo;
}

int main( void )
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int N;
		scanf("%d",&N);
		init();
		int move[ N + 1 ], rank[ N + 1 ];
		for( int i = 1; i <= N; i++ ) {
			scanf("%d", &move[ i ] );
			add( i, 1 );
		}
		for( int i = N; i > 0; i-- ) {
			rank[ i ] = R( i - move[ i ], N ); // index( i ) - move( i ) + pass_through
			add( rank[ i ], -1 );
		}
		printf("%d", rank[ 1 ] );
		for( int i = 2; i <= N; i++ ) {
			printf(" %d", rank[ i ] );
		}
		printf("\n"); 
	}
	return 0;
}
