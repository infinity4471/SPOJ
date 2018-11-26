#include <iostream>
#include <algorithm>
#include <cmath>
 
using namespace std;
 
int main(void)
{
	int K;
	cin >> K;
	for(int k=0; k<K; k++) {
		int M,N,i=0;
		cin >> M >> N;
		bool prime[N-M+1];
		for(int i=0; i<=N-M; i++) {
			prime[i]=true;
		}
		for(i=2; i<=sqrt(N); i++) {
			int less=(M/i);
			less*=i;
			for(int j=less; j<=N; j+=i) {
				if(j>=M && j!=i) {
					prime[j-M]=false;
				}
			}
		}
		for(int i=0; i<=N-M; i++) {
			if(prime[i] && i+M!=1) {
				cout << i+M << endl;
			}
		}
	}
	return 0;
}
