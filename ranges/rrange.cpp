#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

#define MAXN 1000000
#define MOD 10000LL

#define X first
#define Y second
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair< ll, ll > pll;

int Left[ MAXN ], Right[ MAXN ], number[ MAXN ], nodecnt = 2;
pll segtree[ MAXN ];

inline int L( int n )
{
	return !Left[ n ] ? Left[ n ] = ++nodecnt: Left[ n ];
}

inline int R( int n )
{
	return !Right[ n ] ? Right[ n ] = ++nodecnt: Right[ n ];
}

void unflag( int n, int l, int r )
{
	if( number[ n ] ) {
		ll minival2 = ( ll )( l + r + 2 );
		ll val1 = ( ll )( number[ n ] * minival2 - 2*segtree[ n ].Y );
		ll val2 = ( ll )( r - l + 1 );
		segtree[ n ].X = ( segtree[ n ].X + ( ll )val1 * val2 / 2 ) % MOD; 
		if( l != r ) {
			segtree[ L( n ) ].Y += segtree[ n ].Y;
			segtree[ R( n ) ].Y += segtree[ n ].Y;
			number[ L( n ) ] += number[ n ];
			number[ R( n ) ] += number[ n ];
		}
		number[ n ] = 0;
		segtree[ n ].Y = 0;
	}
}

void update( int n, int l, int r, int i, int j )
{
	if( r < i || l > j ) unflag( n, l, r );
	else if( i <= l && r <= j ) {
		segtree[ n ].Y += i;
		number[ n ]++;
		unflag( n, l, r );
	} else {
		unflag( n, l, r );
		update( L( n ), l, ( l + r ) / 2, i, j );
		update( R( n ), ( l + r ) / 2 + 1, r, i, j );
		if( l != r ) segtree[ n ].X = ( ll )( segtree[ L( n ) ].X % MOD + segtree[ R( n ) ].X % MOD ) % MOD;
	}
}

ll sum( int n, int l, int r, int i, int j )
{
	if( r < i || l > j ) return 0;
	unflag( n, l, r );
	if( i <= l && r <= j ) return ( ll )( segtree[ n ].X % MOD );
	else return ( ll )( ( sum( L( n ), l, ( l + r ) / 2, i, j ) % MOD ) + ( sum( R( n ), ( l + r ) / 2 + 1, r, i, j ) % MOD ) ) % MOD;
}

int main( void )
{
	//freopen("test.in","rt",stdin);
	//freopen("test.out","wt",stdout);
	int N, U, Q, u, v;
	scanf("%d%d%d", &N, &U, &Q );
	while( U-- ) {
		scanf("%d%d", &u, &v );
		update( 1, 1, N, u, v );
	}
	while( Q-- ) {
		scanf("%d%d", &u, &v );
		printf("%lld\n", sum( 1, 1, N, u, v ) % MOD );
	}
	return 0;
}
