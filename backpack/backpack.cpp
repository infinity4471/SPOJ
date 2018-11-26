#include <cstdio>
#include <algorithm>
 
using namespace std;
 
int main( void )
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int V,N;
		scanf("%d%d",&V,&N);
		V /= 10;
		int comb[ N + 1 ][ 4 ],num[ N + 1][ 4 ],K[ N + 1 ],dp[ V + 1][ N + 1 ];
		for(int i = 0; i <= N; i++ ) {
			dp[ 0 ][ i ] = 0;
			K[ i ] = 0;
			for(int j = 0; j < 3; j++ ) {
				comb[ i ][ j ] = 0;
				num[ i ][ j ] = 0;
			}
		}
		for(int i = 0; i <= V; i++ ) {
			dp[ i ][ 0 ] = 0;
		}
		for( int i = 1; i <= N; i++ ) {
			int n,m,k;
			scanf("%d%d%d",&n,&m,&k);
			n /= 10;
			if( !k ) {
				comb[ i ][ 0 ] = n*m;
				num[ i ][ 0 ] = n;
			} else {
				K[ k ]++;
				comb[ k ][ K[ k ] ] = n*m;
				num[ k ][ K[ k ] ] =  n;
			}
		}
		for(int i = 0; i <= N; i++ ) {
			comb[ i ][ 3 ] = comb[ i ][ 2 ] + comb[ i ][ 1 ] + comb[ i ][ 0 ];
			comb[ i ][ 1 ] = comb[ i ][ 0 ] + comb[ i ][ 1 ];
			comb[ i ][ 2 ] = comb[ i ][ 0 ] + comb[ i ][ 2 ];
			num[ i ][ 3 ] = num[ i ][ 2 ] + num[ i ][ 1 ] + num[ i ][ 0 ];
			num[ i ][ 1 ] = num[ i ][ 0 ] + num[ i ][ 1 ];
			num[ i ][ 2 ] = num[ i ][ 0 ] + num[ i ][ 2 ];
		}
		for( int i = 1; i <= V; i++ ) {
			for(int j = 1; j <= N; j++ ) {
				dp[ i ][ j ] = dp[ i ][ j - 1];
				if( comb[ j ][ 0 ] > 0) { 
					for(int k = 0; k < 4; k++ ) {
						if( i - num[ j ][ k ] >= 0 ) {
							dp[ i ][ j ] = max( dp[ i ][ j ],dp[ i - num[ j ][ k ] ][ j - 1 ] + comb[ j ][ k ] );
						}
					}
				}
			}
		}
		printf("%d\n",10*dp[V][N]);
	}
	return 0;
}
