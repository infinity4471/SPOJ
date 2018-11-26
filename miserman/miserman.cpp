#include <iostream>
#include <algorithm>

#define INF 10000000

using namespace std;

int main(void)
{
	int N,M;
	cin >> N >> M;
	int minim=INF;
	int dp[N][M];
	int bus[N][M];
	for(int i=0; i<N; i++)
		for(int j=0; j<M; j++)
			cin >> bus[i][j];
	for(int i=0; i<M; i++)
		dp[0][i]=bus[0][i];
	for(int i=1; i<N; i++) {
		for(int j=0; j<M; j++) {
			if(j==0) dp[i][j]=min(dp[i-1][j],dp[i-1][j+1])+bus[i][j];
			else if(j==M-1) dp[i][j]=min(dp[i-1][j-1],dp[i-1][j])+bus[i][j];
			else dp[i][j]=min(min(dp[i-1][j-1],dp[i-1][j]),dp[i-1][j+1])+bus[i][j];
		}
	}
	for(int i=0; i<M; i++)
		if(dp[N-1][i]<minim)
			minim=dp[N-1][i];
	cout << minim << endl;
	return 0;
}
