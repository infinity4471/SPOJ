#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

string reverse(string str)
{
	string rev;
	stack<char> s;
	for(int i=0; i<str.length(); i++) {
		s.push(str[i]);
	}
	while( !s.empty() ) {
		rev+=s.top();
		s.pop();
	}
	return rev;
}

int main(void)
{
	int N;
	cin >> N;
	string palin,rev;
	cin >> palin;
	rev=reverse(palin);
	int dp[2][N+1];
	for(int i=0; i<=N; i++) {
		dp[i%2][0]=dp[0][i]=0;
	}
	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=N; j++)
		{
			if(palin[i-1]==rev[j-1]) {
				dp[i%2][j]=dp[(i-1)%2][j-1]+1;
			} else {
				dp[i%2][j]=max(dp[(i-1)%2][j],dp[i%2][j-1]);
			}
		}
	}
	cout << N-dp[N%2][N] << endl;
	return 0;
}
