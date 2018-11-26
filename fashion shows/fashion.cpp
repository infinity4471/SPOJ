#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void)
{
	int T;
	cin >> T;
	while(T--) {
		int N,d,sum=0;
		vector<int> A;
		vector<int> B;
		cin >> N;
		for(int i=0; i<N; i++) {
			cin >> d;
			A.push_back(d);
		}
		for(int i=0; i<N; i++) {
			cin >> d;
			B.push_back(d);
		}
		sort(A.begin(),A.end());
		sort(B.begin(),B.end());
		for(int i=0; i<N; i++) {
			sum+=A[i]*B[i];
		}
		cout << sum << endl;
	}
	return 0;
}
