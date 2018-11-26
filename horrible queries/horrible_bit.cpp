#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

#define MAXN 100100

using namespace std;

typedef long long ll;

ll BIT[ MAXN + 1 ][ 2 ];
int N;

ll query( int X, int d )
{
	ll ans = 0;
	while( X > 0 ) {
		ans += BIT[ X ][ d ];
		X -= ( X & -X );
	}
	return ans;
}

void update( int X, ll val, int d )
{
	while( X <= N ) {
		BIT[ X ][ d ] += ( ll )val;
		X += ( X & -X );
	}
}

void update_range( int i, int j, ll val )
{
	update( i, val, 0 );
	update( j + 1, -val, 0 );
	update( i, ( i - 1 ) * val, 1 );
	update( j + 1, -( i - 1 ) * val - val * ( j - i + 1 ), 1 );
}

ll query_range( int i, int j )
{
	ll suma = 0, sumb = 0;
	suma = query( i - 1, 0 ) * ( i - 1 ) - query( i - 1, 1 );
	sumb = query( j, 0 ) * j - query( j, 1 );
	return sumb - suma;
}

int main( void )
{
	int T;
	ios_base::sync_with_stdio( false );
	cin >> T;
	while( T-- ) {
		memset( BIT, 0, sizeof( BIT ) );
		int Q;
		cin >> N >> Q;
		while( Q-- ) {
			int q, i, j;
			ll val;
			cin >> q >> i >> j;
			if( q == 0 ) {
				cin >> val;
				update_range( i, j, val );
			} else {
				cout << query_range( i, j ) << "\n";
			}
		}
	}
	return 0;
}
