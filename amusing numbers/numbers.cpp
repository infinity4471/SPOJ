#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int st,dig;

string tobin(int i)
{
	string bin;
	while(i>0) {
		bin+=i%2+'0';
		i/=2;
	}
	return bin;
}

string reverse(string a)
{
	stack<char> st;
	string b;
	for(int i=0; i<a.length(); i++) {
		st.push(a[i]);
	}
	while(!st.empty()) {
		b+=st.top();
		st.pop();
	}
	return b;
}

int main(void)
{
	int N;
	cin >> N;
	for(int k=0; k<N; k++) {
		st=0;
		dig=0;
		int K;
		string ans;
		vector<string> binaries;
		string num;
		cin >> K;
		for(int i=0; st+pow(2,i)<=K; i++) {
			st+=pow(2,i);
			dig++;
		}
		//cout << dig << endl;
		//cout << st << " " << K << endl;
		ans=tobin(K-st);
		for(int i=ans.length(); i<dig; i++) {
			ans+='0';
		}
		ans=reverse(ans);
		for(int i=0; i<ans.length(); i++) {
			if(ans[i]=='0') {
				cout << 5;
			} else cout << 6;
		}
		cout << endl;
	}
	return 0;
}
