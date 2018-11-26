#include <cstdio>
#include <algorithm>
#include <ctime>

using namespace std;

int main( void )
{
	freopen("test.in","wt",stdout);
	srand( time( NULL ) );
	int N, U, Q;
	N = 10000;
	U = 1000;
	Q = 1000;
	printf("%d %d %d\n", N, U, Q );
	while( U-- ) {
		int u = rand() % N + 1;
		int v = rand() % N + 1;
		if( u > v ) swap( u, v );
		printf("%d %d\n", u, v );
	}
	while( Q-- ) {
		int u = rand() % N + 1;
		int v = rand() % N + 1;
		if( u > v ) swap( u, v );
		printf("%d %d\n", u, v );
	}
	return 0;
}
