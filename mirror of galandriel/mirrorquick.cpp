#include <iostream>
#include <string>
#include <stack>

using namespace std;

string reverse(string base)
{
	stack<char> s;
	string rev;
	for(int i=0; i<base.length(); i++) {
		s.push(base[i]);
	}
	while ( !s.empty() ) {
		rev+=s.top();
		s.pop();
	}
	return rev;
}

int main(void)
{
	int T;
	cin >> T;
	while( T-- ) {
		string base,rev;
		cin >> base;
		rev=reverse(base);
		if(rev==base) {
			cout << "YES" << endl;
		} else {
			cout << "NO"  << endl;
		}
	}
	return 0;
}
