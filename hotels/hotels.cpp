#include <cstdio>
#include <algorithm>

using namespace std;

int main(void)
{
	int N;
	long long M;
	long long ans=0;
	scanf("%d%lld",&N,&M);
	int hotels[N];
	long long parsums[N+1];
	for(int i=0; i<N; i++) {
		scanf("%d",&hotels[i]);
	}
	parsums[0]=0;
	for(int i=1; i<=N; i++) {
		parsums[i]=hotels[i-1]+parsums[i-1];
	}
	for(int i=0; i<N; i++) {
		for(int j=i,k=N; j<=k; ) {
			int mid=(j+k)/2;
			if(parsums[mid]-parsums[i]>M) {
				k=mid-1;
			}
			else {
				if(parsums[mid]-parsums[i]>ans) {
					ans=parsums[mid]-parsums[i];
				}
				j=mid+1;
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
