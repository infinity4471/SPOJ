#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void)
{
	while ( 1 ) {
		int N,d,ans=0;
		cin >> N;
		if(N==0) return 0;
		vector<int> v;
		for(int i=0; i<N; i++) {
			cin >> d;
			v.push_back(d);
		}
		sort(v.begin(), v.end() );
		for(int i=0; i<N-2; i++) {
			for(int j=i+1; j<N-1; j++) {
				int pos=N;
				for(int k=j+1,l=N-1; k<=l; ) {
					int mid=(k+l)/2;
					if(v[i]+v[j]<v[mid]) {
						l=mid-1;
						if(pos>mid) pos=mid;
					} else if(v[i]+v[j]>=v[mid]) {
						k=mid+1;
					}
				}
				ans+=N-pos;
			}
		}
		cout << ans << endl;
	}
	return 0;
}
