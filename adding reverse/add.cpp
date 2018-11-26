#include <cstdio>
#include <cmath>

int log(int a)
{
	int cnt=0;
	while(a>0) {
		a/=10;
		cnt++;
	}
	return cnt;
}

int reverse(int a)
{
	int b=0,cnt=0;
	int d=log(a);
	while(a>0) {
		int c=a%10;
		b+=c*pow(10,d-cnt-1);
		a/=10;
		cnt++;
	}
	return b;
}

int main(void)
{
	int K;
	scanf("%d",&K);
	while(K--) {
		int i,j;
		scanf("%d%d",&i,&j);
		printf("%d\n",reverse(reverse(i)+reverse(j)));
	}
	return 0;
}
