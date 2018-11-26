#include <cstdio>
#include <algorithm>

using namespace std;

int main( void )
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int N;
		scanf("%d",&N);
		N--;
		unsigned long long ans = 0;
		int mul3,mul5, mul15;
		mul3 = N / 3;
		mul5 = N / 5;
		mul15 = N / 15;
		int n3 = 3 + 3*(mul3 - 1 );
		int n5 = 5 + 5*(mul5 - 1 );
		int n15 = 15 + 15*(mul15 - 1 );
		ans = (unsigned long long )mul3*(3+ n3 ) / 2 + (unsigned long long )mul5*(5 + n5 ) / 2 - (unsigned long long)mul15*( 15 + n15 ) / 2;
		printf("%llu\n", ans );
	}
	return 0;
}
