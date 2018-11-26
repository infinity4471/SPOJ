#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 1001000

using namespace std;

char A[ MAXN + 1 ], B[ MAXN + 1 ];
int ans = 0, letter[ 27 ][ 2 ] = { 0 }, common[ MAXN + 1 ][ 2 ] = { 0 };

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		ans = 0;
		scanf("%s%s", A, B );
		int N = strlen( A ), M = strlen( B );
		for( int i = 0; i < 26; ++i ) letter[ i ][ 0 ] = letter[ i ][ 1 ] = 0;
		common[ 0 ][ 0 ] = common[ 0 ][ 1 ] = 1;
		letter[ A[ 0 ] - 'a' ][ 0 ] = letter[ B[ 0 ] - 'a' ][ 1 ] = 1;
		for( int i = 1; i < N; ++i ) {
			if( A[ i ] == A[ i - 1 ] ) common[ i ][ 0 ] = 1 + common[ i - 1 ][ 0 ];
			else common[ i ][ 0 ] = 1;
			letter[ A[ i ] - 'a' ][ 0 ] = max( letter[ A[ i ] - 'a' ][ 0 ], common[ i ][ 0 ] );
		}
		for( int i = 1; i < M; ++i ) {
			if( B[ i ] == B[ i - 1 ] ) common[ i ][ 1 ] = 1 + common[ i - 1 ][ 1 ];
			else common[ i ][ 1 ] = 1;
			letter[ B[ i ] - 'a' ][ 1 ] = max( letter[ B[ i ] - 'a' ][ 1 ], common[ i ][ 1 ] );
		}
		for( int i = 0; i < 26; ++i ) ans = max( ans, letter[ i ][ 0 ] + letter[ i ][ 1 ] );
		printf("%d\n", ans );
	}
	return 0;
}
