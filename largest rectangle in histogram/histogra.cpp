#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAXN 100100
#define INF 1234567891

#define X first
#define Y second
#define mp make_pair

using namespace std;

typedef long long ll;
typedef pair< int, int > pii;

pii A[ MAXN + 1 ];
int BIT[ MAXN + 1 ];

void add( int u, int N )
{
	while( u <= N ) {
		BIT[ u ]++;
		u += u & -u;
	}
}

int get( int u )
{
	int sum = 0;
	while( u > 0 ) {
		sum += BIT[ u ];
		u -= u & -u;
	}
	return sum;
}

int BS( int i, int N )
{
	int lo = i, hi = N, idx1 = i, idx2 = i;
	while( lo <= hi ) {
		int mid = ( lo + hi ) / 2;
		if( get( mid ) - get( i - 1 ) == mid - i + 1 ) {
			idx1 = mid;
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}
	lo = 1, hi = i;
	while( lo <= hi ) {
		int mid = ( lo + hi ) / 2;
		if( get( i ) - get( mid - 1 ) == i - mid + 1 ) {
			idx2 = mid;
			hi = mid - 1;
		} else {
			lo = mid + 1;
		}
	}
	i = idx1;
	return idx1 - idx2 + 1;
}

int main( void )
{
	do {
		int N;
		ll ans = 0;
		scanf("%d", &N );
		if( !N ) break;
		memset( BIT, 0, sizeof( BIT ) );
		for( int i = 1; i <= N; i++ ) {
			int u;
			scanf("%d", &u );
			A[ i ] = mp( u, i );
		}
		sort( A + 1, A + N + 1 ); 
		for( int i = N; i > 0; i-- ) {
			add( A[ i ].Y, N );
			ans = max( ans, ( ll )BS( A[ i ].Y, N ) * A[ i ].X );
		}
		printf("%lld\n", ans );
	} while( true );
	return 0;
}
