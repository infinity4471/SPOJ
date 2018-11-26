#include <cstdio>
#include <algorithm>

#define MAXN 511
#define MOD 100003

using namespace std;

typedef long long ll;

int main( void )
{
	ll dp[ MAXN + 1 ][ MAXN + 1 ], combi[ MAXN + 1 ][ MAXN + 1 ];
	for( int i = 2; i <= MAXN; i++ ) {
		dp[ i ][ 1 ] = 1;
	}
	for( int i = 0; i <= MAXN; i++ ) { // binomial coefficients
		combi[ i ][ 0 ] = 1;
	}
	for( int i = 1; i <= MAXN; i++ ) {
		dp[ 0 ][ i ] = 0;
	}
	for( int i = 1; i <= MAXN; i++ ) {
		for( int j = 1; j <= i; j++ ) {
			combi[ i ][ j ] = ( combi[ i - 1 ][ j ] + combi[ i - 1 ][ j - 1 ] ) % MOD;
		}
	}
	for( int i = 3; i <= MAXN; i++ ) {
		for( int j = 2; j < i; j++ ) {
			dp[ i ][ j ] = 0;
			for( int k = 1; k < j; k++ ) {
				if( i - j >= j - k ) {
					dp[ i ][ j ] = ( dp[ i ][ j ] + dp[ j ][ k ] * combi[ i - j - 1 ][ j - k - 1 ] ) % MOD;
				}
			}
		}
	}
	int T;
	scanf("%d", &T );
	for( int z = 1; z <= T; z++ ) {
		int N;
		scanf("%d", &N );
		int ans = 0;
		for( int i = 1; i < N; i++ ) {
			ans = ( ans + ( int )dp[ N ][ i ] ) % MOD;
		}
		printf("Case #%d: %d\n", z, ans );
	}
	return 0;
}
