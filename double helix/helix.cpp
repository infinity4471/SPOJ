#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

typedef pair<int,int> pii;

int main(void)
{
	while( 1 ) {
		int N,M,d;
		long long sum=0;
		vector<int> A,B;
		vector<pii> inter;
		scanf("%d",&N);
		if(N==0) {
			break;
		}
		for(int i=0; i<N; i++) {
			scanf("%d",&d);
			A.push_back(d);
		}
		scanf("%d",&M);
		for(int i=0; i < M; i++ ) {
			scanf("%d",&d);
			B.push_back(d);
		}
		for(int i=0; i<N; i++) {
			for(int j=0,k=M-1; j<=k; ) {
				int mid=(j+k)/2;
				if(A[i]>B[mid]) {
					j=mid+1;
				}
				else if(A[i]<B[mid]) {
					k=mid-1;
				}
				else if(A[i]==B[mid]) {
					pii a;
					a.first=i+1;
					a.second=mid+1;
					inter.push_back(a);
					break;
				}
			}
		}
		vector<int> parA(N+1),parB(M+1);
		parA.push_back(0);
		parB.push_back(0);
		for(int i=1; i<=N; i++) {
			parA[i] = parA[i-1]+A[i-1];
		}
		for(int i=1; i<=M; i++) {
			parB[i]=parB[i-1]+B[i-1];
		}
		int pos=0;
		if(inter.size()) {
			sum+=max(parA[inter[0].first],parB[inter[0].second]);
			for(int i=0; i<inter.size()-1; i++) {
				sum+=max(parA[inter[i+1].first]-parA[inter[i].first],parB[inter[i+1].second]-parB[inter[i].second]);
			}
			sum+=max(parA[N]-parA[inter[inter.size()-1].first],parB[M]-parB[inter[inter.size()-1].second]);
		}
		else {
			sum=max(parA[N],parB[M]);
		}
		printf("%lld\n",sum);
	}
	return 0;
}
