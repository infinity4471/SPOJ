#include <cstdio>
#include <algorithm>

#define MAXN 2000000

using namespace std;

typedef long long ll;

int a[ MAXN + 10 ] = { 0 };

int main( void )
{
	int N;
	ll ans = 0;
	scanf("%d", &N );
	int A[ N + 1 ], maxim = 0;
	for( int i = 1; i <= N; i++ ) {
		scanf("%d", &A[ i ] );
		a[ A[ i ] ]++;
		maxim = max( A[ i ], maxim );
	}
	for( int i = 1; i <= maxim; i++ ) {
		ll res = 0, num = 0;
		for( int j = i; j <= maxim; j += i ) {
			res += ( ll )i*a[ j ];
			num += ( ll )a[ j ];
		}
		if( num > 1 ) {
			ans = max( ans, res );
		}
	}
	printf("%lld\n", ans );
	return 0;
}
