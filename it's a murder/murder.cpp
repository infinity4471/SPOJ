#include <cstdio>
#include <algorithm>

#define MAX 1000000

using namespace std;

long long BIT[MAX+1];
int A[MAX+1];

void init()
{
	for(int i = 0; i <= MAX; i++ ) {
		BIT[ i ] = 0;
	}
}

void add(int k,int i,int N)
{
	while(i<=MAX) {
		BIT[ i ] += k;
		i += ( i & -i );
	}
}

long long S(int i)
{
	i--;
	long long sum = 0;
	while( i > 0 ) {
		sum += BIT[ i ];
		i -= (i & -i);
	}
	return sum;
}

int main(void)
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int N;
		long long ans = 0;
		scanf("%d",&N);
		init();
		for(int i = 0; i < N; i++ ) {
			scanf("%d",&A[ i ]);
		}
		for(int i = 0; i < N; i++) {
			if( A[ i ] ) {
				add(A[i],A[i],N);
				ans += S( A[ i ] );
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
