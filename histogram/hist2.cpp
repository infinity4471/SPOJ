#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 15

using namespace std;

typedef long long ll;

int dp[ 1 << MAXN ][ MAXN ];
ll dp_count[ 1 << MAXN ][ MAXN ];

int main( void )
{
	int N;
	while( scanf("%d", &N ) == 1 && N ) {
		int ans = 0;
		ll cnt_ans = 0;
		memset( dp, 0, sizeof( dp ) );
		memset( dp_count, ( ll )0, sizeof( dp_count ) );
		int A[ N + 1 ];
		for( int i = 0; i < N; i++ ) {
			scanf("%d", &A[ i ] );
			dp[ 1 << i ][ i ] = 2*A[ i ] + 2;
			dp_count[ 1 << i ][ i ] = 1;
		}
		for( int bitmask = 1; bitmask < ( 1 << N ); bitmask++ ) {
			if( bitmask & ( bitmask - 1 ) == 0 ) continue;
			for( int i = 0; i < N; i++ ) {
				if( !( bitmask & ( 1 << i ) ) ) continue;
				for( int j = 0; j < N; j++  ) {
					if( !( bitmask & ( 1 << j ) ) || i == j ) continue;
					int val = 2 + A[ i ];
					if( A[ i ] >= A[ j ] ) {
						val = val + A[ i ] - 2*A[ j ];
					} else {
						val = val - A[ i ];
					}
					dp[ bitmask ][ i ] = max( dp[ bitmask ][ i ], dp[ bitmask ^ ( 1 << i ) ][ j ] + val );
				}
				for( int j = 0; j < N; j++  ) {
					if( !( bitmask & ( 1 << j ) ) || i == j ) continue;
					int val = 2 + A[ i ];
					if( A[ i ] >= A[ j ] ) {
						val = val + A[ i ] - 2*A[ j ];
					} else {
						val = val - A[ i ];
					}
					if( dp[ bitmask ^ ( 1 << i ) ][ j ] + val == dp[ bitmask ][ i ] ) {
						dp_count[ bitmask ][ i ] += ( ll )dp_count[ bitmask ^ ( 1 << i ) ][ j ];
					}
				}
				ans = max( ans, dp[ bitmask ][ i ] );
				if( !dp_count[ bitmask ][ i ] ) {
					dp_count[ bitmask ][ i ] = ( ll )1;
				}
			}
		}
		for( int i = 0; i < N; i++ ) {
			if( dp[ ( 1 << N ) - 1 ][ i ] == ans ) {
				cnt_ans += dp_count[ ( 1 << N ) - 1 ][ i ];
			}
		}
		printf("%d %lld\n", ans, cnt_ans );
	}
	return 0;
}
