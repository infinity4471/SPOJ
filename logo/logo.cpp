#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <functional>

using namespace std;

int main(void)
{
	while ( 1 ) {
		string a;
		cin >> a;
		if(a=="Q") break;
		int ans=0;
		vector< pair<int ,int > > pts;
		map < pair< int ,int > , int > grid;
		int x=0,y=0;
		pair<int ,int > b;
		b.first=x;
		b.second=y;
		pts.push_back(b );
		grid[pts.back()]++;
		for(int i=0; i<a.length()-1; i++) {
			if(a[i]=='U') y++;
			else if(a[i]=='R') x++;
			else if(a[i]=='L') x--;
			else if(a[i]=='D') y--;
			b.first=x;
			b.second=y;
			pts.push_back(b);
			grid[pts.back()]++;
		}
		for(int i=0; i<pts.size(); i++) {
			if(grid[pts[i]]>1) ans++;
		}
		cout << ans/2 << endl;
		a.clear();
		pts.clear();
	}
	return 0;
}
