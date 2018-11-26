#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 20100

using namespace std;

int BIT[ MAXN + 1 ], N;

void add( int pos )
{
	while( pos <= N ) {
		BIT[ pos ]++;
		pos += ( pos & -pos );
	}
}

int count( int i, int j )
{
	int curi = i, curj = j;
	int sum = 0;
	while( j > 0 ) {
		sum += BIT[ j ];
		j -= ( j & -j );
	}
	i--;
	while( i > 0 ) {
		sum -= BIT[ i ];
		i -= ( i & -i );
	}
	return curj - curi + 1 - sum;
}

int next( int pos )
{
	pos++;
	if( !count( pos, N ) ) pos = 1;
	int lo = pos, hi = N, ans = N;
	while( lo <= hi ) {
		int mid = ( lo + hi ) / 2;
		if( !count( pos, mid ) ) {
			lo = mid + 1;
		} else {
			hi = mid - 1;
			ans = mid;
		}
	}
	return ans;
}

int search( int pos, int k )
{
	int lo = pos, hi = N, ans = lo;
	while( lo <= hi ) {
		int mid = ( lo + hi ) / 2;
		if( count( pos, mid ) > k ) {
			hi = mid - 1;
		} else {
			ans = mid;
			lo = mid + 1;
		}
	}
	return next( ans );
}

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		scanf("%d", &N );
		memset( BIT, 0, sizeof( BIT ) );
		int pos = 1;
		int A[ N + 1 ];
		memset( A, 0, sizeof( A ) );
		for( int i = 1; i <= N; i++ ) {
			int value = i, curcount = 0;
			if( count( pos, N ) < value ) {
				value -= count( pos, N );
				pos = 1;
				curcount = count( 1, N );
				while( value > curcount ) value -= curcount;
			}
			pos = search( pos, value );
			add( pos );
			A[ pos ] = i;
		}
		printf("%d", A[ 1 ] );
		for( int i = 2; i <= N; i++ ) printf(" %d", A[ i ] );
		printf("\n");
	}
	return 0;
}
