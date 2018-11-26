#include <cstdio>
#include <algorithm>

#define INF 0x4242424

using namespace std;

int main(void)
{
	int K;
	scanf("%d",&K);
	while(K--)
	{
		int W1,W2,W,N;
		scanf("%d%d",&W1,&W2);
		W=W2-W1;
		scanf("%d",&N);
		int val[N+1],cap[N+1],pig[W+1];
		for(int i=1; i<=N; i++)
			scanf("%d%d",&val[i],&cap[i]);
		pig[0]=0;
		for(int i=1; i<=W; i++) {
			pig[i]=INF;
			for(int j=1; j<=N; j++) {
				if(pig[i-cap[j]]+val[j]<pig[i] && i-cap[j]>=0)
					pig[i]=pig[i-cap[j]]+val[j];
			}
		}
		if(pig[W]!=INF)
			printf("The minimum amount of money in the piggy-bank is %d.\n",pig[W]);
		else printf("This is impossible.\n");
	}
	return 0;
}
