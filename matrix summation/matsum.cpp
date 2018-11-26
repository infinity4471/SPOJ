#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 1026

using namespace std;

int BIT[ MAXN + 1 ][ MAXN + 1 ];

void init()
{
	for( int i = 0; i <= MAXN; i++ ) {
		for( int j = 0; j <= MAXN; j++ ) {
			BIT[ i ][ j ] = 0;
		}
	}
}

void add( int x, int y, int w )
{
	while( x <= MAXN ) {
		int ny = y;
		while( ny <= MAXN ) {
			BIT[ x ][ ny ] += w;
			ny += ( ny & -ny );
		}
		x += ( x & -x );
	}
}

int sum( int x, int y )
{
	int ans = 0;
	while( x > 0 ) {
		int ny = y;
		while( ny > 0 ) {
			ans += BIT[ x ][ ny ];
			ny -= ( ny & -ny );
		}
		x -= ( x & -x );
	}
	return ans;
}

int newsum( int x1, int y1, int x2, int y2 )
{
	return sum( x2, y2 ) - sum( x1 - 1, y2 ) - sum( x2, y1 - 1 ) + sum( x1 - 1, y1 - 1 );
}

int main( void )
{
	int T;
	//freopen("test.in","rt",stdin);
	//freopen("test.out","wt",stdout);
	scanf("%d", &T );
	while( T-- ) {
		int N;
		init();
		scanf("%d",&N);
		do {
			char q[ 10 ];
			scanf("%s", &q );
			if( !strcmp( q, "END" ) ) {
				break;
			}
			else if( !strcmp( q, "SET" ) ) {
				int u,v,w;
				scanf("%d%d%d", &u, &v, &w );
				add( u + 1 , v + 1, -newsum( u + 1, v + 1, u + 1, v + 1 ) );
				add( u + 1, v + 1, w );
			}
			else if( !strcmp( q, "SUM" ) ) {
					int x1,x2,y1,y2;
					scanf("%d%d%d%d", &x1, &y1,&x2,&y2 );
					printf("%d\n", newsum( x1 + 1, y1 + 1, x2 + 1, y2 + 1 ) );
			}
		} while( true );
	}
	return 0;
}
