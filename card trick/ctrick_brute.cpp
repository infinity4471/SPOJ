#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 20100

using namespace std;

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int N;
		scanf("%d", &N );
		int A[ N + 1 ], pos = 0;
		memset( A, 0, sizeof( A ) );
		for( int i = 1; i <= N; i++ ) {
			int cnt = 0;
			while( cnt < i ) {
				if( A[ pos ] == 0  ) cnt++;
				pos++;
				pos %= N;
			}
			while( A[ pos ] ) pos = ( pos + 1 ) % N;
			A[ pos ] = i;
		}
		printf("%d", A[ 0 ] );
		for( int i = 1; i < N; i++ ) {
			printf(" %d", A[ i ] );
		}
		printf("\n");
	}
	return 0;
}
