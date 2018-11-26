#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXN 10000000
#define MOD 10000LL

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair< int, int > pii;

int main( void )
{
	int N, U, Q, u, v;
	//freopen("test.in","rt",stdin);
	//freopen("test2.out","wt",stdout);
	scanf("%d%d%d", &N, &U, &Q );
	vector< pii > updates;
	while( U-- ) {
		scanf("%d%d", &u, &v );
		updates.pb( mp( u, v ) );
	}
	while( Q-- ) {
		scanf("%d%d", &u, &v );
		ll ans = 0;
		for( int i = 0; i < updates.size(); i++ ) {
			int x = updates[ i ].X, y = updates[ i ].Y;
			if( x > v || y < u ) continue;
			int left_end = max( u, x ), right_end = min( v, y );
			ans = ( ans + ( ll )( left_end + right_end - 2*x + 2 ) * ( right_end - left_end + 1 ) / 2 ) % MOD;		
		}
		printf("%lld\n", ans % MOD );
	}
	return 0;
}
