#include <cstdio>
#include <algorithm>

int main( void )
{
	int N,K;
	long long ans = 0;
	scanf("%d%d",&N,&K);
	int A[ N ];
	for(int i = 0; i < N; i++ ) {
		scanf("%d",&A[ i ]);
	}
	std::sort(A,A+N);
	for(int i = 1,j = 0; i<N && j<N; ) {
		if(A[ i ] - A[ j ] < K) {
			i++;
		}
		else if(A[ i ] - A[ j] > K) {
			j++;
		} else {
			ans++;
			if(A[ i+1 ] == A[ i ] ) {
				i++;
			} else if(A [j + 1] == A[ j ]) {
				j++;
			} else {
				i++;
				j++;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
