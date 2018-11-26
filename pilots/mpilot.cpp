#include <cstdio>
#include <algorithm>

#define INF 100000000

int main( void )
{
	int N;
	scanf("%d",&N);
	int A[ N + 1 ],B[ N + 1 ], dp[ 2 ][ N + 1 ];
	for( int i = 1; i <= N; i++ ) {
		scanf("%d%d",&A[ i ], &B[ i ] );
	}
	for( int i = 0; i < 2; i++ ){
		for( int j =0; j <= N; j++ ) {
			dp[ i ] [ j ] = INF;
		}
	}
	dp[ 0 ][ 0 ] = 0;
	for( int i = 1; i <= N; i++ ) {
		for( int j = 0; j <= i; j++ ) {
			if( j == 0 ) {
				dp[ i%2 ][ j ] = dp[ (i - 1) % 2 ][ j + 1 ] + A[ i ];
			} else { 	
				dp[ i % 2 ][ j ] = std::min ( dp[ (i - 1) % 2 ][ j + 1 ] + A[ i ], dp[ (i - 1) % 2 ][ j - 1] + B[ i ] );
			}
		}
	}
	printf("%d\n",dp[ 0 ][ 0 ] );
	return 0;
}
