#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 2001

using namespace std;

static int dp[ MAXN + 1 ][ MAXN + 1 ];

int main( void )
{
	char* A,*B, c = 0;
	int K, N, M;
	A = new char[ MAXN + 1 ];
	B = new char[ MAXN + 1 ];
	for( int i = 0;; i++ ) {
		c = getchar_unlocked();
		if( c == '\n' ) {
			c = 0;
			break;
		}
		A[ i ] = c;
	}
	for( int i = 0;; i++ ) {
		c = getchar_unlocked();
		if( c == '\n' ) {
			c = 0;
			break;
		}
		B[ i ] = c;
	}
	scanf("%d",&K);
	N = strlen( A );
	M = strlen( B );
	dp[ 0 ][ 0 ] = 0;
	for( int i = 0; i < N; i++ ) {
		dp[ i + 1 ][ 0 ] = K*( i + 1 );
	}
	for( int j = 0; j < M; j++ ) {
		dp[ 0 ][ j + 1 ] = K*( j + 1 );
	}
	for( int i = 1; i <= N; i++ ) {
		for( int j = 1; j <= M; j++ ) {
			dp[ i ][ j ] = min( dp[ i - 1 ][ j - 1 ] + abs( A[ i - 1 ] - B[ j - 1 ] ),
						min( dp[ i - 1 ][ j ] +  K , dp[ i ][ j - 1 ] +  K ) );
		}
	}
	printf("%d\n",dp[ N ][ M ] );
	return 0;
}		
