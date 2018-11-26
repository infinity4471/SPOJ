#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 1100
#define INF 5010

using namespace std;

int number[ MAXN + 1 ], dp[ MAXN + 1 ][ INF + 1 ], N, ans;
int calls = 0;

int memo( int n, int val )
{
	if( n == N ) return val == ans ? dp[ n ][ val ] = 0: dp[ n ][ val ] = INF;
	int newval = 0;
	int& res = dp[ n ][ val ];
	if( res != -1 ) return res;
	res = INF;
	for( int i = n; i < N; i++ ) {
		newval = 10*newval + number[ i ];
		if( newval + val > ans ) break;
		res = min( res, memo( i + 1, val + newval ) + 1 );
	}
	return res;
}

int main( void )
{
	char c;
	N = 1;
	int cnt = 0;
	while( ( c = getchar_unlocked() ) != '=' ) {
		if( c == '0' ) cnt++;
		else cnt = 0;
		if( cnt < 5 ) number[ N++ ] = c - '0';
	}
	memset( dp, -1, sizeof( dp ) );
	scanf("%d", &ans );
	printf("%d\n", memo( 1, 0 ) - 1 );
	return 0;
}
