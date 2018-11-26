#include <cstdio>
#include <algorithm>
#include <ctime>

using namespace std;

int main( void )
{
	srand( time( NULL ) );
	freopen("test.in","wt",stdout);
	int N,C,Q;
	N = 300000;
	C = 100000;
	printf("%d %d\n", N, C );
	int k = rand() % C + 1;
	printf("%d", k );
	for( int i = 1; i < N; i++ ) {
		int u = rand() % C + 1;
		printf(" %d", u );
	}
	printf("\n");
	Q = 500000;
	printf("%d\n", Q );
	for( int i = 1; i <= Q; i++ ) {
		int u,v;
		u = 1;
		v = N;
		if( u > v ) swap( u, v );
		printf("%d %d\n", u, v );
	}
	return 0;
}
