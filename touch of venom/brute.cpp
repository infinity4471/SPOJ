#include <cstdio>
#include <algorithm>

#define MAXA 1001000

using namespace std;

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int H, P, A, ans = 0;
		scanf("%d%d%d", &H, &P, &A );
		for( int i = 1; i <= MAXA; i++ ) {
			ans++;
			H -= i * P;
			if( H <= 0 ) break;
			H += A;
			ans++;
		}
		printf("%d\n", ans );
	}
	return 0;
}
