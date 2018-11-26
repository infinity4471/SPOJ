#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 110
#define INF 1234567890

using namespace std;

int N,M;
int memo[ 2*MAXN + 1 ][ MAXN + 1 ][ MAXN + 1 ];
int grid[ MAXN + 1 ][ MAXN + 1 ];

int dp( int n, int x, int y ) // max he can get if he starts two disjoint paths one ending at column x and other at y having done n steps already
{
	int x1 = n - x + 2;
	int y1 = n - y + 2;
	if( x > M || y > M || x1 > N || y1 > N ) return -INF;
	if( memo[ n ][ x ][ y ] != -1 ) return memo[ n ][ x ][ y ];
	if( grid[ x1 ][ x ] == -1 || grid[ y1 ][ y ] == -1 ) return memo[ n ][ x ][ y ] = -INF;
	if( n == N + M - 2 ) {
		if( x1 == y1 && x == y && x1 == N && x == M ) {
			return memo[ n ][ x ][ y ] = grid[ x1 ][ x ];
		} else return memo[ n ][ x ][ y ] = -INF;
	}		
	int add = 0;
	if( grid[ x1 ][ x ] ) add++;
	if( grid[ y1 ][ y ] && ( x1 != y1 || x != y ) ) add++;
	return memo[ n ][ x ][ y ] = add + max( max( dp( n + 1, x + 1, y + 1 ), dp( n + 1, x + 1, y ) ), 
						max( dp( n + 1, x, y + 1 ), dp( n + 1, x, y ) ) );
}

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		scanf("%d%d", &M, &N );
		memset( grid, 0, sizeof( grid ) );
		memset( memo, -1, sizeof( memo ) );
		for( int i = 1; i <= N; i++ ) {
			scanf("\n");
			for( int j = 1; j <= M; j++ ) {
				char c;
				scanf("%c", &c );
				if( c == '.' ) grid[ i ][ j ] = 0;
				else if( c == '#' ) grid[ i ][ j ] = -1;
				else if( c == '*' ) grid[ i ][ j ] = 1;
			}
		}
		printf("%d\n", dp( 0, 1, 1 ) );
	}
	return 0;
}
