#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int main(void)
{
	int N;
	scanf("%d",&N);
	vector<string> sol;
	map<long long int, int > nums;
	map<long long int, bool > equali;
	int dif=0,equal=0;
	for(int i=0; i<N; i++) {
		char a[10];
		long long k;
		scanf("%s%lld",&a,&k);
		if(!strcmp(a,"insert")) {
			if(nums[k]==0) dif++;
			nums[k]++;
			if(nums[k]>=2) {
				equali[k]=true;
				equal++;
			}
		}
		else if(!strcmp(a,"delete")) {
			nums[k]--;
			if(nums[k]==0) {
				dif--;
			}
			if(nums[k]==1 && equali[k]) {
				equali[k]=false;
				equal--;
			}
		}
		if(dif>=2 && equal>0) sol.push_back("both");
		else if(dif<2 && equal>0) sol.push_back("homo");
		else if(dif>=2 && equal==0) sol.push_back("hetero");
		else if(dif<2 && equal==0) sol.push_back("neither");
		//cout << "different numbers: " << dif << endl;
		//cout << "equal numbers: " << equal << endl;
	}
	for(int i=0; i<sol.size(); i++) {
		cout << sol[i] << endl;
	}
	return 0;
}
