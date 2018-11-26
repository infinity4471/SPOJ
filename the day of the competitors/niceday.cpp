#include <cstdio>
#include <algorithm>

#define MAXN 100001

using namespace std;

struct comp {
	int x,y,z;
};

int BIT[ MAXN + 1 ], N;

void init()
{
	for( int i = 0; i <= MAXN; i++ ) {
		BIT[ i ] = MAXN;
	}
}

bool cmp( comp a, comp b )
{
	return a.x < b.x;
}

void add( int idx, int val )
{
	while( idx <= N ) {
		BIT[ idx ] = min( BIT[ idx ], val );
		idx += ( idx & -idx );
	}
}

int find( int idx )
{
	int minim = MAXN;
	while( idx > 0 ) {
		minim = min( BIT[ idx ], minim );
		idx -= ( idx & -idx );
	}
	return minim;
}

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int ans = 0;
		scanf("%d", &N );
		comp A[ N + 1 ];
		init();
		for( int i = 1; i <= N; i++ ) {
			scanf("%d%d%d", &A[ i ].x, &A[ i ].y, &A[ i ].z );
		}
		sort( A + 1, A + N + 1, cmp );
		for( int i = 1; i <= N; i++ ) {
			if( find( A[ i ].y - 1 ) > A[ i ].z ) {
				ans++;
			}
			add( A[ i ].y , A[ i ].z );
		}
		printf("%d\n", ans );
	}
	return 0;
}
