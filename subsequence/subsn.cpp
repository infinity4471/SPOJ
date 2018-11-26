#include <cstdio>
#include <algorithm>
#include <cstring>
	
int main( void )
{
	int T;
	scanf("%d", &T );
	getchar_unlocked();
	for( int z = 1; z <= T; z++ ) {
		int N, cnt = 0;
		char* str = new char[ 100011 ], c;
		int **S, *size;
		S = new int*[ 27 ];
		size = new int[ 27 ];
		for( int i = 0; i < 27; i++ ) {
			S[ i ] = new int[ 100005 ];
		}
		while( true ) {
			c = getchar_unlocked();
			if( c == '\n' ) {
				break;
			}
			str[ cnt++ ] = c;
		}
		for( int i = 0; i < cnt; i++ ) {
			S[ str[ i ] - 'a' ][ size[ str[ i ] - 'a' ]++ ] = i + 1 ;
		}
		scanf("%d", &N );
		getchar_unlocked();
		printf("Case %d:\n", z );
		for( int i = 0; i < N; i++ ) {
			char* ss = new char[ 210 ];
			int prev = 0, status = 1, count [ 27 ] = {0};
			cnt = 0;
			while( true ) {
				c = getchar_unlocked();
				if( c == '\n' ) {
					break;
				}
				ss[ cnt++ ] = c;
			}
			if( strlen( ss ) > strlen( str ) ) {
				printf("NO\n");
				continue;
			}
			for( int j = 0; j < cnt; j++ ) {
				int next = -1;
				while( next < prev && count[ ss[ j ] - 'a' ] <= size[ ss[ j ] - 'a' ] ) {
					next = S[ ss[ j ] - 'a' ][ count[ ss[ j ] - 'a' ]++ ];
				}
				if( count[ ss[ j ] - 'a' ] > size[ ss[ j ] - 'a' ] ) {
					status = false;
					break;
				}
				prev = next;
			}
			printf("%s\n", status?"YES":"NO" );
		}
	}
	return 0;
}
