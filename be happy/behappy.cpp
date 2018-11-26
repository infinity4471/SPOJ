#include <cstdio>
#include <algorithm>

using namespace std;

int main( void )
{
	while( true ) {
		int M,N;
		bool iszero = true;
		scanf("%d%d",&M,&N);
		if( !M && !N ) {
			break;
		}
		long long dp[M+1][N+1];
		int A[M+1],B[M+1];
		for(int i=1; i<=M; i++) {
			scanf("%d%d",&A[i],&B[i]);
		}
		for(int i = 0; i<=N; i++) {
			dp[ 0 ][ i ] = 0;
		}
		dp[ 0 ][ 0 ] = 1;
		for(int i = 1; i <= M; i++) {
			if( A[ i ] > 0 ) {
				iszero = false;
			}
			if( iszero ) {
				dp[ i ][ 0 ] = 1;
			} else {
				dp[ i ][ 0 ] = 0;
			}
		}
		for(int i = 1; i <= M; i++) { 
			for(int j = 1; j <= N; j++) {
				dp[ i ][ j ] = 0;
				for(int k = A[ i ]; k <= B[ i ]; k++) {
					if( k <= j ) {
						dp[ i ][ j ] = dp[ i ][ j ] + dp[ i-1 ][ j - k ];
					}
				}
			}
		}
		printf("%lld\n",dp[ M ][ N ]);
	}
	return 0;
}
