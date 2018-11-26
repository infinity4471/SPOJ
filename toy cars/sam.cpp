#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

#define X first
#define Y second
#define mp make_pair
#define pb push_back

#define MAXN 501000

using namespace std;

typedef pair< int, int > pii;

set< pii > S;
int A[ MAXN + 1 ], prev[ MAXN + 1 ], next[ MAXN + 1 ];
bool inS[ MAXN + 1 ];

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		S.clear();
		int N, K, M, cnt = 0, ans = 0;
		scanf("%d%d%d", &N, &K, &M );
		for( int i = 1; i <= M; i++ ) {
			scanf("%d", &A[ i ] );
			inS[ A[ i ] ] = false;
			prev[ A[ i ] ] = MAXN;
		}
		for( int i = M; i > 0; i-- ) {
			next[ i ] = prev[ A[ i ] ];
			prev[ A[ i ] ] = i;
		}
		for( int i = 1; i <= M; i++ ) {
			if( inS[ A[ i ] ] ) {
				S.insert( mp( next[ i ], A[ i ] ) );
				continue;
			}
			if( cnt == K ) {
				set< pii >::iterator it = --S.end();
				S.erase( it );
				inS[ (*it).Y ] = false;
				cnt--;
			}
			S.insert( mp( next[ i ], A[ i ] ) );
			inS[ A[ i ] ] = true;
			cnt++;
			ans++;
		}
		printf("%d\n", ans );
	}
	return 0;
}
