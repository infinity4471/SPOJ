#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>

#define mp make_pair
#define MAXN 400000

using namespace std;

typedef long long ll;
typedef pair< ll, ll > pii;

pii segtree[ 4*MAXN + 1 ];

void init( )
{
	for( int i = 0; i <= 4*MAXN; i++ ) {
		segtree[ i ] = mp( 0, -1 );
	}
}

void update( int n, int l, int r, int idx, ll val )
{
	if( l == r ) {
		segtree[ n ] = mp( val, ( ll )idx );
		return;
	}
	if( idx <= ( l + r ) / 2 ) {
		update( 2*n, l, ( l + r ) / 2, idx, val );
	} else {
		update( 2*n + 1, ( l + r ) / 2 + 1, r, idx, val );
	}
	segtree[ n ] = max( segtree[ 2*n ], segtree[ 2*n + 1 ] );
}

pii query( int n, int l, int r, int i, int j )
{
	if( r < i || l > j ) {
		return mp( 0, -1 );
	}
	else if( i <= l && r <= j ) {
		return segtree[ n ];
	} else {
		return max( query( 2*n, l, ( l + r ) / 2, i, j ), query( 2*n + 1, ( l + r ) / 2 + 1, r, i, j ) );
	}
}

int main( void )
{
	int N,K;
	ll u, v;
	ll ans = 0;
	scanf("%d%d", &N, &K );
	pii jew[ N + 1 ];
	ll C[ K + 1 ];
	for( int i = 1; i <= N; i++ ) {
		scanf("%lld%lld", &u, &v );
		jew[ i ] = mp( u, v );
	}
	for( int i = 1; i <= K; i++ ) {
		scanf("%lld", &C[ i ] );
	}
	sort( C + 1, C + K + 1 );
	sort( jew + 1, jew + N + 1 );
	init();
	for( int i = 1; i <= N; i++ ) {
		update( 1, 1, N, i, ( ll )jew[ i ].second );
	}
	for( int i = 1; i <= K; i++ ) {
		int lo = 1, hi = N, idx = N;
		while( lo <= hi ) {
			int mid = ( lo + hi ) / 2;
			if( jew[ mid ].first <= C[ i ] ) {
				idx = mid;
				lo = mid + 1;
			} else {
				hi = mid - 1;
			}
		}	
		pii q = query( 1, 1, N, 1, idx );
		if( q.second != -1 ) {
			ans += ( ll )q.first;
			update( 1, 1, N, q.second, 0 );
		}
	}
	printf("%lld\n", ans );
	return 0;
}
