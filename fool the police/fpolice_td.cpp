#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXN 1010
#define INF 1234567890

#define X first
#define Y second
#define mp make_pair

using namespace std;

typedef pair< int, int > pii;

pii dp[ MAXN + 1 ][ MAXN + 1 ];
int N,T, tt[ MAXN + 1 ][ MAXN + 1 ], cost[ MAXN + 1 ][ MAXN + 1 ];

pii memo( int city, int time )
{
	if( time < 0 ) return mp( INF, INF ); 
	if( dp[ city ][ time ] != mp( -1, -1 ) ) return dp[ city ][ time ];
	if( city == 1 ) return dp[ city ][ time ] = mp( 0, 0 );
	pii newstate = mp( INF, INF );
	for( int i = 1; i <= N; i++ ) {
		if( i == city ) continue;
		pii news = mp( cost[ i ][ city ] + memo( i , time - tt[ i ][ city ] ).X, tt[ i ][ city ] + memo( i, time - tt[ i ][ city ] ).Y );
		if( newstate > news ) newstate = news;
	}
	return dp[ city ][ time ] = newstate;
}

int main( void )
{
	int tests;
	scanf("%d", &tests );
	while( tests-- ) {
		scanf("%d%d", &N, &T );
		if( !N && !T ) break;
		for( int i = 1; i <= N; i++ ) {
			for( int j = 1; j <= N; j++ ) {
				scanf("%d", &tt[ i ][ j ] );
			}
		}
		for( int i = 1; i <= N; i++ ) {
			for( int j = 1; j <= N; j++ ) {
				scanf("%d", &cost[ i ][ j ] );
			}
		}
		for( int i = 0; i <= N; i++ ) {
			for( int j = 0; j <= T; j++ ) {
				dp[ i ][ j ] = mp( -1, -1 );
			}
		}
		pii current = memo( N, T );
		for( int i = T; i >= 0; i-- ) {
			if( memo( N, i ) < current ) current = dp[ i ][ N ];
		}
		if( current.Y > T ) printf("-1\n");
		else printf("%d %d\n", current.X, current.Y );
	}
	return 0;
}
