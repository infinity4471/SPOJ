#include <cstdio>
#include <algorithm>
 
#define INF 1234567890

using namespace std;
 
int main( void )
{
	int N, ans = INF;
	scanf("%d", &N );
	int A[ N ];
	for( int i = 0; i < N; i++ ) {
		scanf("%d", &A[ i ] );
	}
	for( int i = 0; i < N; i++ ) {
		//printf("number 1 goes to pos %d\n", i );
		int pos[ N + 1 ], arr[ N ], swaps = 0;
		for( int j = 1; j <= N; j++ ) {
			pos[ j ] = ( i + j - 1 ) % N;
		}
		for( int j = 0; j < N; j++ ) {
			arr[ j ] = pos[ A[ j ] ];
			//printf("pos[ %d ] = %d\n", A[ j ], pos[ A[ j ] ] );
			//printf("arr[ %d ] = %d\n", j, arr[ j ] );
		}
		for( int j = 0; j < N; j++ ) {
			for( int k = j + 1; k < N; k++ ) {
				if( arr[ j ] > arr[ k ] ) {
					swaps++;
				}
			}
		}
		//printf("swaps -> %d\n", swaps );
		ans = min( ans, swaps );
	}
	printf("%d\n", ans );
	return 0;
}
