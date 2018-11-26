#include <iostream>
#include <algorithm>
 
using namespace std;
 
int main(void)
{
	int N,M;
	while( 1 ) {
		cin >> N >> M;
		if(N==0 && M==0) break;
		int dp[N+1];
		dp[1]=0;
		for(int i=2; i<=N; i++) {
			dp[i]=(dp[i-1]+M) % i;
		}
		cout << N << " " << M << " " << dp[N]+1 << endl;
	}
	return 0;
}
