#include <cstdio>

int main(void)
{
	long long N,K,max=0,lim=0;
	scanf("%lld%lld",&N,&K);
	int A[N];
	for(int i=0; i<N; i++) {
		scanf("%lld",&A[i]);
		if(A[i]>max)
			max=A[i];
	}
	for(long long i=0,j=max; i<=j; ) {
		long long mid=(i+j)/2,h=0;
		for(int k=0; k<N; k++) {
			if(A[k]>mid)
				h+=A[k]-mid;
		}
		if(h>K) {
			if(mid>lim) lim=mid;			 
			i=mid+1;
		}
		else if(h<K) j=mid-1;
		else if (h==K) { 
			lim=mid; 
			break;
		}
	}
	printf("%lld\n",lim);
	return 0;
}
