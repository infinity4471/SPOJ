#include <cstdio>
#include <algorithm>

#define MAXA 500100LL

using namespace std;

typedef long long ll;

bool check( int H, int P, int A, int t )
{
	ll val = ( ll )H - ( ll )P * ( ll )( ( ll )t * ( ll )( t + 1 ) / 2 ) + ( ll )( t - 1 ) * ( ll )A;
	return val > 0;
}

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int H,P,A;
		scanf("%d%d%d", &H, &P, &A );
		
		int lo = 0, hi = MAXA, ans = 1;
		while( lo <= hi ) {
			int mid = ( lo + hi ) / 2;
			if( check( H, P, A, mid )  ) {
				ans = 2*mid + 1;
				lo = mid + 1;
			} else {
				hi = mid - 1;
			}
		}
		printf("%d\n", ans );
	}
	return 0;
}
