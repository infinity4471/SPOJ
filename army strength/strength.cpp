#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
	int T;
	cin >> T;
	while(T--) {
		int N,M,d;
		cin >> N >> M;
		vector<int> godz,megodz;
		for(int i=0; i<N; i++) {
			cin >> d;
			godz.push_back(d);
		}
		for(int i=0; i<M; i++) {
			cin >> d;
			megodz.push_back(d);
		}
		sort(godz.begin(),godz.end());
		sort(megodz.begin(),megodz.end());
		while(!godz.empty() && !megodz.empty()) {
			if(godz.back()<megodz.back()) {
				godz.pop_back();
			}
			else {
				megodz.pop_back();
			}
		}
		if(godz.empty()) {
			cout << "MechaGodzilla" << endl;
		} else if(megodz.empty()) {
			cout << "Godzilla" << endl;
		}
	}
	return 0;
}
