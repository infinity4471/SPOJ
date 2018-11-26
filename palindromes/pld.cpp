#include <cstdio>
#include <algorithm>
#include <cstring>

#define MOD 34027797218763967LL
#define A 26
#define MAXN 500000

using namespace std;

typedef long long ll;

ll table[ MAXN + 1][ 2 ];

int rolling( char* pattern, char* rev, int N, int K )
{
	int ans = 0;
	ll hash = 0, hash1 = 0, mult = 1;
	for( int i = 0; i < K; i++ ) {
		hash = ( ( hash * A ) % MOD + pattern[ i ] ) % MOD;
		hash1 = ( ( hash1 * A ) % MOD + rev[ i ] ) % MOD;
	}
	table[ K - 1 ][ 0 ] = hash;
	table[ K - 1 ][ 1 ] = hash1;
	for( int i = 0; i < K - 1; i++ ) {
		mult = ( mult*A ) % MOD;
	}
	for( int i = K; i < N; i++ ) {
		hash = ( hash - ( mult*pattern[ i - K ] ) % MOD ) % MOD;
		hash = hash * A % MOD;
		hash = ( hash + pattern[ i ] ) % MOD;
		hash1 = ( hash1 - ( mult*rev[ i - K ] ) % MOD ) % MOD;
		hash1 = hash1 * A % MOD;
		hash1 = ( hash1 + rev[ i ] ) % MOD;
		table[ i ][ 0 ] = hash;
		table[ i ][ 1 ] = hash1;
	}
	for( int i = K - 1, j = N - 1; i < N; i++, j-- ) {
		if( table[ i ][ 0 ] == table[ j ][ 1 ] ) ans++;
	}
	return ans;
}

int main( void )
{
	int N, K;
	char pattern[ MAXN + 1 ], rev[ MAXN + 1 ];
	scanf("%d%s", &K, pattern );
	N = strlen( pattern );
	if( K > N ) {
		printf("0\n");
		return 0;
	}
	for( int j = N - 1; j >= 0 ; j-- ) {
		rev[ j ] = pattern[ N - j - 1 ];
	}
	for( int i = 0; i < N; i++ ) {
		pattern[ i ] -= 'a';
		rev[ i ] -= 'a';
	}
	printf("%d\n", rolling( pattern, rev, N, K ) );
	return 0;
}
