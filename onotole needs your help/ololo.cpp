#include <cstdio>

int main(void)
{
	int N,ans=0,num;
	scanf("%d",&N);
	for(int i=0; i<N; i++) {
		scanf("%d",&num);
		ans ^= num;
	}
	printf("%d\n",ans);
	return 0;
}
