#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

map<long long,long long> memo;

#define MAX(x,y) x>y?x:y

long long produce(int value)
{
	if(value==0) {
		memo[value]=0;
	}
	else {
		if(memo[value]==0) {
			memo[value]=MAX(produce(value/2)+produce(value/3)+produce(value/4),value);
		}
	}
	return memo[value];
}

int main(void)
{
	int N;
	while( cin >> N ) {
		cout <<  produce(N) << endl;
	}
	return 0;
}
