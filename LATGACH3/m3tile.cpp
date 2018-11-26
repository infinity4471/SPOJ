#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 50

using namespace std;

const int R = 3;
typedef long long ll;

int N;
ll memo[ R + 1 ][ MAXN + 1 ][ 1 << ( R + 1 )  ];

ll dp( int i, int j, int bit )
{
	if( i > R ) return 0;
	ll& ans = memo[ i ][ j ][ bit ];
	if( ans != -1 ) return ans;
	if( j == N ) return bit == 0;
	if( i == R ) return ans = dp( 0, j + 1, bit );
	ans = 0;
	if( bit & ( 1 << i ) ) ans += dp( i + 1, j, bit ^ ( 1 << i ) );
	else {
		ans += dp( i + 1, j, bit | ( 1 << i ) );
		if( !( bit & ( 1 << ( i + 1 ) ) ) ) ans += dp( i + 2, j, bit );
	}
	return ans;
}

int main( void )
{
	do {	
		scanf("%d", &N );
		if( N == -1 ) break;
		memset( memo, -1, sizeof( memo ) );
		printf("%lld\n", dp( 0, 0, 0 ) );
	} while( true );
	return 0;
}
