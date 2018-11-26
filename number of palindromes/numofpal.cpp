#include <cstdio>
#include <cstring>

#define MAXN 1000

int main( void )
{
	int N, ans = 0;
	char str[ MAXN + 1 ];
	scanf("%s",&str);
	N = strlen( str );
	bool dp[ N ][ N ];
	for( int i = 0; i < N; i++ ) {
		for( int j = 0; j < N; j++ ) {
			dp[ i ][ j ] = 0;
		}
	}
	for( int i = 0; i < N; i++ ) {
		dp[ i ][ i ] = 1;
	}
	for( int i = 0; i < N - 1; i++ ) {
		int x = i, y = i + 1;
		while( x >= 0 && y < N && str[ x ] == str[ y ] ) {
			dp[ x ][ y ] = 1;
			x--;
			y++;
		}
	}
	for( int i = 1; i < N - 1; i++ ) {
		int x = i - 1, y = i + 1;
		while( x >= 0 && y < N && str[ x ] == str[ y ] ) {
			dp[ x ][ y ] = 1;
			x--;
			y++;
		}
	}
	for( int i = 0; i < N; i++ ) {
		for( int j = 0; j < N; j++ ) {
			ans += dp[ i ][ j ];
		}
	}
	printf("%d\n", ans );
	return 0;
}
