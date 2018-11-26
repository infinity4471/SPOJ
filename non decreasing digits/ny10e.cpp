#include <cstdio>
#include <algorithm>

#define MAXN 65
using namespace std;

typedef long long ll;

int main( void )
{
	ll dp[ MAXN ][ 10 ];
	for( int i = 0; i < 10; i++ ) {
		dp[ 1 ][ i ] = 1;
	}
	for( int i = 2; i < MAXN; i++ ) {
		for( int j = 0; j < 10; j++ ) {
			dp[ i ][ j ] = 0;
			for( int k = j; k >= 0; k-- ) {
				dp[ i ][ j ] += dp[ i - 1 ][ k ];
			}
		}
	}
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int u,v;
		scanf("%d%d", &u, &v );
		ll ans = 0;
		for( int i = 0; i < 10; i++ ) {
			ans += dp[ v ][ i ];
		}
		printf("%d %lld\n", u, ans );
	}
	return 0;
}
