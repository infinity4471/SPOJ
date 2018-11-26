#include <cstdio>

int readint() {
    int n = 0;
    char c = getchar_unlocked();
    while ( !( '0' <= c && c <= '9' ) ) {
        c = getchar_unlocked();
    }
    while ( '0' <= c && c <= '9' ) {
        n = n * 10 + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

int main(void)
{
	int T;
	scanf("%d",&T);
	for(int o=0; o<T; o++) {
		long long N, M,amt=10000001,ans=0;
		N = readint();
		M = readint();
		long long A[N],parsums[N+1];
		for(int i=0; i<N; i++) {
			A[ i ] = readint();
		}
		parsums[0]=0;
		for(int i=1; i<=N; i++) {
			parsums[i]=parsums[i-1]+A[i-1];
		}
		for(int i=0; i<=N; i++) {
			int pos=0;
			for(int j=i,k=N; j<=k; ) {
				int mid=(j+k)/2;
				if(parsums[mid]-parsums[i]<=M) {
					if(mid>pos) {
						pos=mid;
					}
					j=mid+1;
				} else {
					k=mid-1;
				}
			}
			if(pos-i > ans) {
				ans=pos-i;
				amt=parsums[pos]-parsums[i];
			} else if(pos-i==ans) {
				if(parsums[pos]-parsums[i]<amt) {
					ans=pos-i;
                                	amt=parsums[pos]-parsums[i];
				}
			}
		}
		printf("%lld %lld\n",amt,ans);
	}
	return 0;
}
