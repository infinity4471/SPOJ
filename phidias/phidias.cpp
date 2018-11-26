#include <cstdio>
#include <algorithm>

int main(void)
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int N,M,K;
		scanf("%d%d%d",&M,&N,&K);
		int k,l,dp[N+1][M+1];
		for(int i = 1; i<=N; i++) {
			for(int j= 1; j<=M; j++) {
				dp[i][j] = i*j;
			}
		}
		for(int i=0; i< K; i++) {
			scanf("%d%d",&k,&l);
			dp[l][k] = 0;
		}
		for(int i=1; i<=N; i++) {
			for(int j = 1; j<=M; j++) {
				for(int k = 1; k<i; k++) {
					dp[i][j] = std::min(dp[i][j],dp[k][j] + dp[i-k][j]  );
				}
				for(int k = 1; k<j; k++) {
					dp[i][j] = std::min( dp[i][j], dp[i][k] + dp[i][j-k] );
				}
			}
		}
		printf("%d\n",dp[N][M]);
	}
	return 0;
}
