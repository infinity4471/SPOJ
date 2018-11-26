#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

typedef pair<int,int> pii;

int main(void)
{
	int N,u,v;
	scanf("%d",&N);
	vector< pii > rect(N+1);
	for(int i=1; i<=N; i++) {
		scanf("%d%d",&u,&v);
		rect[i].first = u;
		rect[i].second = v;
	}
	int dp[N+1][2];
	dp[1][0]=rect[1].first;
	dp[1][1]=rect[1].second;
	for(int i=2; i<=N; i++) {
		dp[i][0] = rect[i].first + max(dp[i-1][0] + fabs(rect[i].second - rect[i-1].second ) ,
				dp[i-1][1] + fabs(rect[i-1].first - rect[i].second ) );
		dp[i][1] = rect[i].second + max(dp[i-1][0] + fabs(rect[i-1].second - rect[i].first)  ,
				dp[i-1][1]  + fabs(rect[i-1].first - rect[i].first ) );
	}
	printf("%d\n",max(dp[N][0],dp[N][1]));
	return 0;
}
