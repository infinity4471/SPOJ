#include <cstdio>
#include <cmath>

#define EPSILON 0.00001

using namespace std;

int main(void)
{
	int T;
	scanf("%d",&T);
	for(int k=0; k<T; k++) {
		long double score,newscore;
		long long ans=1;
		double a;
		scanf("%llf",&score);
		newscore=score;
		while(abs( newscore - round(newscore) ) > EPSILON ) {
			newscore+=score;
			ans++;
			//printf("%0.4lf %lld\n",(double) newscore,round(newscore));
		}
		printf("%d\n",ans);
	}
	return 0;
}
