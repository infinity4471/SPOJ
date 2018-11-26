#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

static int dp[2001][2001];

int main(void)
{
	int T;
	cin >> T;
	while( T-- ) {
		string A,B;
		cin >> A >> B;
		int N = A.length();
		int M = B.length();
		for(int i=0; i<=N; i++) {
			dp[i][0] = i;
		}
		for(int j=0; j<=M; j++) {
			dp[0][j] = j;
		}
		for(int i = 1; i<=N; i++) {
			for(int j=1; j<=M; j++) {
				int cost ;
				if(A[i-1] == B[j-1] ) {
					cost = 0;
				} else {
					cost = 1;
				}
				dp[i][j] = min(dp[i-1][j-1]+cost,min(dp[i-1][j],dp[i][j-1]) + 1);
			}
		}
		cout << dp[N][M] << endl;
	}
	return 0;
}
