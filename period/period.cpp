#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 1001000

using namespace std;

int P[ MAXN + 1 ];

void prefix( char* S )
{
	int N = strlen( S );
	P[ 0 ] =  P[ 1 ] = 0;
	for( int i = 2; i <= N; i++ ) {
		int j = P[ i - 1 ];
		do {
			if( S[ i - 1 ] == S[ j ] ) {
				P[ i ] = j + 1;
				break;
			}
			else if( j == 0 ) {
				P[ i ] = 0;
				break;
			} else {
				j = P[ j ];
			}
		} while( true );
	}
}

int main( void )
{
	int T, cnt = 1;
	scanf("%d", &T );
	while( T-- ) {
		int N;
		scanf("%d", &N );
		char S[ N + 1 ];
		scanf("%s", S );
		prefix( S );
		for( int i = 1; i <= N; i++ ) {
			printf("P[ %d ] = %d\n", i, P[ i ] );
		}
		printf("Test case #%d\n", cnt++ );
		for( int i = 1; i < N; i++ ) {
			int j = i + 1;
			if( P[ j ] != 0 && j % ( j - P[ j ] ) == 0 ) {
				printf("%d %d\n", j, j / ( j - P[ j ] ) );
			}
		}
		printf("\n");
	}
	return 0;
}
