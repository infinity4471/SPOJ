#include <iostream>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

int main(void)
{
	string A,B;
	while ( cin >> A >> B ) {
		string ans,lcs;
		stack<char> s;
		int N=A.length(),M=B.length();
		int LCS[N+1][M+1],print[N+1][M+1];
		for(int i=0; i<=N; i++) {
			LCS[i][0]=0;
		}
		for(int i=0; i<=M; i++) {
			LCS[0][i]=0;
		}
		for(int i=1; i<=N; i++) {
			for(int j=1; j<=M; j++) {
				if(A[i-1]==B[j-1]) {
					LCS[i][j]=LCS[i-1][j-1]+1;
					print[i][j]=2;
				} else {
					if(LCS[i-1][j] > LCS[i][j-1]) {
						print[i][j]=1;
						LCS[i][j]=LCS[i-1][j];
					} else {
						LCS[i][j]=LCS[i][j-1];
						print[i][j]=0;
					}
				}
			}
		}
		for(int i=N,j=M; i>0 && j>0; ) {
			if(print[i][j]==2) {
				s.push(A[i-1]);
				i--; j--;
			}
			else if(print[i][j]==1) {
				i--;
			}
			else {
				j--;
			}
		}
		while( !s.empty() ) {
			lcs+=s.top();
			s.pop();
		}
		//cout << lcs << endl;
		int i=0,j=0,k=0;
		for(i=0,j=0,k=0; k<lcs.length();) {
			if(lcs[k]!=A[i] && i<A.length()) {
				ans+=A[i];
				i++;
			}
			else if(lcs[k]!=B[j] && j<B.length()) {
				ans+=B[j];
				j++;
			} 
			else {
				ans+=lcs[k];
				k++;	
				i++;
				j++;
			}
		}
		for(; i<A.length(); i++) {
			ans+=A[i];
		}
		for(; j<B.length(); j++) {
			ans+=B[j];
		}
		cout << ans << endl;
	}
	return 0;
}
