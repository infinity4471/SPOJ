#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

string reverse(string a)
{
	string b;
	stack<char> s;
	for(int i=0; i<a.length(); i++) {
		s.push(a[i]);
	}
	while(!s.empty()) {
		b+=s.top();
		s.pop();
	}
	return b;
}

int main(void)
{
	int T;
	cin >> T;
	while( T-- ) {
		string pal,rev;
		int N;
		cin >>  pal;
		N=pal.length();
		rev=reverse(pal);
		int dp[2][N+1];
		for(int i=0; i<=N; i++)
		dp[i%2][0]=dp[0][i]=0;
		for(int i=1; i<=N; i++)
		{
			for(int j=1; j<=N; j++)
			{
				if(pal[i-1]==rev[j-1]) dp[i%2][j]=dp[(i-1)%2][j-1]+1;
				else dp[i%2][j]=max(dp[(i-1)%2][j],dp[i%2][j-1]);
			}
		}
		cout << N-dp[N%2][N] << endl;
	}
	return 0;
}
