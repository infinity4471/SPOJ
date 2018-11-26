#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

#define MAXN 1100
#define INF 1234567890

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

int N;
pii array[ MAXN + 1 ];
bool taken[ MAXN + 1 ];

int solve()
{
	int sol = 0;
	vector< int > A;
	A.pb( array[ 1 ].X );
	sol += array[ 1 ].Y;
	taken[ array[ 1 ].Y ] = true;
	for( int i = 2; i <= N; i++ ) {
		int rank = array[ i ].Y;
		for( int j = 1; j <= array[ i ].Y; j++ ) rank -= taken[ j ];
		if( *A.begin() > array[ i ].X ) A.insert( A.begin(), array[ i ].X );
		else if( *A.end() < array[ i ].X ) A.insert( A.end(), array[ i ].X );
		else return INF;
		sol += i * rank;
		taken[ array[ i ].Y ] = true;
	}
	printf("answer -> %d\n", sol );
	return sol;
}

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int u, ans = INF;
		scanf("%d", &N );
		for( int i = 1; i <= N; i++ ) {
			scanf("%d", &u );
			array[ i ] = mp( u, i );
		}
		sort( array + 1, array + N + 1 );
		do {
			memset( taken, 0, sizeof( taken ) );
			printf("permutation->");
			for( int i = 1; i <= N; i++ ) {
				printf(" %d", array[ i ].X );
			}
			printf("\n");
			ans = min( ans, solve() );
			if( ans == 69 ) break;
		} while( next_permutation( array + 1, array + N + 1 ) );	
		printf("%d\n", ans );
	}
	return 0;
}
