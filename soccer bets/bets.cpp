#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

typedef pair<string,string> pii;

int main(void)
{
	int T;
	cin >> T;
	while(T--) {
		int u,v;
		string a,b,ans;
		map<string,bool> found;
		map<string,bool> status;
		vector<string> teams;
		for(int i=0; i<16; i++) {
			cin >> a >> b >> u >> v;
			if( !found[ a ] ) {
				teams.push_back(a);
			}
			if( !found[ b ] ) {
				teams.push_back(b);
			}
			if(u<v) {
				status[ a ] = true;
			} else {
				status[ b ] = true;
			}
			found[ a ] = true;
			found[ b ] = true;
		}
		for(int i=0; i<teams.size(); i++) {
			if( !status[ teams[i] ] ) {
				ans = teams[i];
			}
		}
		cout << ans << endl;
	}
	return 0;
}
