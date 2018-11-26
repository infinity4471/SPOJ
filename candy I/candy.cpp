#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void)
{
	int N=0;
	while( true ) {
		int t,k=0,ans=0;
		cin >> N;
		if(N==-1) break;
		vector<int> A;
		for(int i=0; i<N; i++) {
			cin >> t;
			k+=t;
			A.push_back(t);
		}
		if(k%N) {
			cout << -1 << endl;
			continue;
		}
		k/=N;
		sort(A.begin(),A.end());
		int i=0,j=N-1;
		for(; i<j; ) {
			if(A[i]==k) i++;
			if(A[i]<k) {
				A[i]++;
				A[j]--;
				ans++;
			}
			if(A[j]==k) j--;
		}
		cout << ans << endl;
	}
	return 0;
}
