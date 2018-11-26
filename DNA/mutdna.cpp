#include <cstdio>
#include <algorithm>

using namespace std;

int main( void )
{
	int N;
	char c;
	scanf("%d\n",&N );
	int dp[ N + 1][ 2 ];
	bool dna[ N + 1 ];
	for( int i = 1; i <= N; i++ ) {
		c = getchar_unlocked();
		dna[ i ] = c - 'A';
	}
	dp[ 1 ][ 0 ] = dna[ 1 ] == 0 ? 0: 1;
	dp[ 1 ][ 1 ] = dna[ 1 ] == 1 ? 0: 1;
	for( int i = 2; i <= N; i++ ) {
		dp[ i ][ 0 ] = min( 1 + dp[ i - 1 ][ 1 ] + ( dna[ i ] == 1 ? 0: 1 ), dp[ i - 1 ][ 0 ] + ( dna[ i ] == 0 ? 0: 1 ) );
		dp[ i ][ 1 ] = min( 1 + dp[ i - 1 ][ 0 ] + ( dna[ i ] == 0 ? 0: 1 ), dp[ i - 1 ][ 1 ] + ( dna[ i ] == 1 ? 0: 1 ) );
	}
	printf("%d\n", dp[ N ][ 0 ] );
	return 0;
}
