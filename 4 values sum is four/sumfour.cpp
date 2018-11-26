#include <cstdio>
#include <algorithm>
#include <vector>

#define pb push_back

using namespace std;

typedef long long ll;

vector< int > S;

int CC( int val )
{
	int N = ( int )S.size();
	int idx1 = -1, idx2 = -1, lo = 0, hi = N - 1;
	while( lo <= hi ) {
		int mid = ( lo + hi ) / 2;
		if( S[ mid ] < val ) lo = mid + 1;
		else {
			hi = mid - 1;
			idx1 = mid;
		}
	}
	lo = 0, hi = N - 1;
	while( lo <= hi ) {
		int mid = ( lo + hi ) / 2;
		if( S[ mid ] > val ) hi = mid - 1;
		else {
			lo = mid + 1;
			idx2 = mid;
		}
	}
	if( idx1 == -1 && idx2 == N - 1 ) return 0;
	return idx2 - idx1 + 1;
}

int main( void )
{
	int N, ans = 0;
	scanf("%d", &N );
	int A[ N + 1 ], B[ N + 1 ], C[ N + 1 ], D[ N + 1 ];
	for( int i = 1; i <= N; i++ ) {
		scanf("%d%d%d%d", &A[ i ], &B[ i ], &C[ i ], &D[ i ] );
	}
	for( int i = 1; i <= N; i++ ) {
		for( int j = 1; j <= N; j++ ) {
			S.pb( A[ i ] + B[ j ] );
		}
	}
	sort( S.begin(), S.end() );
	for( int i = 1; i <= N; i++ ) {
		for( int j = 1; j <= N; j++ ) {
			ans += CC( -C[ i ] - D[ j ] );
		}
	}
	printf("%d\n", ans );
	return 0;
}
