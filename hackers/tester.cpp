#include <cstdio>
#include <algorithm>
#include <ctime>

using namespace std;

int main( void )
{
	freopen("test.in","wt",stdout);
	printf("1\n");
	srand( time( NULL ) );
	int N = rand() % 10000 + 1, M = rand() % 1000 + 1, K = rand() % 200 + 1;
	printf("%d %d\n", M, K );
	for( int i = 0; i < N; i++ ) {
		char c = rand() % 26 + 'a';
		printf("%c", c );
	}
	for( int i = 0; i < M; i++ ) {
		int len = rand() % 20 + 1;
		for( int j = 0; j < len; j++ ) {
			char c = rand() % 26 + 'a';
			printf("%c", c );
		}
		printf("\n");
	}
	return 0;
}
