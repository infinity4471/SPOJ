#include <iostream>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;

bool find(string base,string sub)
{
	for(int i=0; i<=base.length(); i++) {
		bool status=true;
		for(int j=0; j<sub.length(); j++) {
			if(sub[j]!=base[i+j]) {
				status=false;
			}
		}
		if(status) {
			return true;
		}
	}
	return false;
}

string reverse(string sub)
{
	string rev;
	stack<char> s;
	for(int i=0; i<sub.length(); i++) {
		s.push(sub[i]);
	}
	while( !s.empty() ) {
		rev+=s.top();
		s.pop();
	}
	return rev;
}

bool genfind(string base,int i,int j)
{
	string sub;
	for(int k=i; k<=j; k++) {
		sub+=base[k];
	}
	return find(base,reverse(sub));
}

int main(void)
{
	int T;
	cin >> T;
	while ( T-- ) {
		string base;
		cin >> base;
		bool status=true;
		for(int i=0; i<base.length(); i++) {
			for(int j=i; j<base.length(); j++) {
				if(!genfind(base,i,j)) {
					status=false;
				}
			}
		}
		if(status) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}
	return 0;
}
