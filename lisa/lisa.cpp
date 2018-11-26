#include <cstdio>
#include <iostream>
#include <algorithm>

#define INF 10000000

using namespace std;

int main(void)
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int cnum = 0,cop = 0;
		string cmd;
		cin >> cmd;
		int N = cmd.length() / 2 + 1;
		int num[ N ];
		bool op[N-1];
		int dp[2][N][N]; // 0 for the max, 1 for the min
		for(int i=0; i<cmd.length(); i++) {
			if( i%2 == 0 ) {	
				num[ cnum++ ] = cmd[i] - '0';
			} else {
				if(cmd[i] == '*'){
					op[cop++] = 1;
				} else {
					op[cop++]=0;
				}
			}
		}
		for(int i=0; i<N; i++) {
			dp[0][i][i] = num[i];
			dp[1][i][i] = num[i];
		}
		for(int l = 1; l<N; l++) {
			for(int i=0; i<N-l; i++) {
				int j = i + l;
				dp[0][i][j] = 0;
				dp[1][i][j] = INF;
				for(int k=i; k<j; k++) {
					if( !op[ k ] ) { // plus
						dp[0][i][j] = max(dp[0][i][j],dp[0][i][k] + dp[0][k+1][j]);
						dp[1][i][j] = min(dp[1][i][j],dp[1][i][k] + dp[1][k+1][j]);
					}
					else if( op[k] ) { // times
						dp[0][i][j] = max(dp[0][i][j],dp[0][i][k]*dp[0][k+1][j]);
						dp[1][i][j] = min(dp[1][i][j],dp[1][i][k]*dp[1][k+1][j]);
					}
				}
			}
		}
		printf("%d %d\n",dp[0][0][N-1],dp[1][0][N-1]);
	}
	return 0;
}
