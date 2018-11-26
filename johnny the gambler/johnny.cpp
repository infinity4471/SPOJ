#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

int main(void)
{
	//freopen("test.in","rt",stdin);
	int T,cnt=0;
	scanf("%d",&T);
	while( T-- ) {
		int N,X;
		long long ans=0;
		scanf("%d%d",&X,&N);
		map<int, long long > a;
		int A[N];
		for(int i=0; i<N; i++) {
			scanf("%d",&A[i]);
			a[A[i]]++;
		}
		for(int i=0; i<N; i++) {
			a[A[i]]--;
			int val = X - A[i];
			//printf("val to be added -> %d\n",val);
			ans+=a[val];
			//printf("number of %ds -> %d\n",val,a[val]);
		}
		printf("%d. %lld\n",cnt+1,ans);
		cnt++;
	}
	return 0;
}
