#include <cstdio>
#include <algorithm>
 
#define MAXN 101
 
using namespace std;
 
int readint() {
    int n = 0;
    char c = getchar_unlocked();
    while ( !( '0' <= c && c <= '9' ) ) {
        c = getchar_unlocked();
    }
    while ( '0' <= c && c <= '9' ) {
        n = n * 10 + c - '0';
        c = getchar_unlocked();
    }
    return n;
}
 
int table[ 1 << 8 ];
 
int TableBitCount(unsigned int x) {
  return table[x & 0xff] + table[(x >> 8) & 0xff] +
         table[(x >> 16) & 0xff] + table[(x >> 24) & 0xff];
}
 
static int dp[ MAXN + 1 ][ MAXN + 1 ], col[ MAXN + 1 ][ MAXN + 1 ][ MAXN + 1 ];
 
int main( void )
{
	int N,M,K, ans = 0;
	N = readint();
	M = readint();
	K = readint();
	int grid[ N + 1 ][ M + 1 ];
	for (int i = 0; i < 8; ++i) table[1 << i] = 1;
  	for (int i = 0; i < (1 << 8); ++i) table[i] = table[i & (i - 1)] + table[i & -i];
	for( int i = 1; i <= N; i++ ) {
		scanf("\n");
		for( int j = 1; j <= M; j++ ) {
			char c;
			c = getchar_unlocked();
			grid[ i ][ j ] = 1 << ( c - 'A' );
			col[ j ][ i ][ i ] = grid[ i ][ j ];
		}
	}
	for( int i = 1; i <= M; i++ ) {
		for( int j = 1; j < N; j++ ) {
			for( int k = j + 1; k <= N; k++ ) {
				col[ i ][ j ][ k ] = col[ i ][ j ][ k - 1 ] | grid[ k ][ i ];
			}
		}
	}
	for( int i = 1; i <= N; i++ ) {
		for( int j = 1; j <= M; j++ ) {
			for( int k = i; k <= N; k++ ) {
				for( int l = j; l <= M; l++ ) {
					if( i == k && j == l ) {
						dp[ k ][ l ] = grid[ i ][ j ];
					}
					else if( i == k && j != l ) {
						dp[ k ][ l ] = dp[ k ][ l - 1 ] | grid[ k ][ l ];
					}
					else if( j == l && i != k ) {
						dp[ k ][ l ] = col[ j ][ i ][ k ];
					} else if( i != k && j != l ) {
						dp[ k ][ l ] = dp[ k ][ l - 1 ] | col[ l ][ i ][ k ];
					}
					if( TableBitCount( dp[ k ][ l ] ) == K ) {
						ans++;
					}
				}
			}
		}
	}
	printf("%d", ans );
	puts("");
	return 0;
}
