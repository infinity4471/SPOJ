#include <cstdio>
#include <algorithm>
#include <vector>

#define X first
#define Y second
#define mp make_pair
#define pb push_back

#define MAXN 201000
#define INF 10001000

using namespace std;

typedef pair< int, int > pii;

int maxp = 0, BIT[ 3*MAXN ][ 2 ];

struct point {
	pii P;
	int idx;
};

bool operator<( point A, point B )
{
	return A.P < B.P;
}

point Pall[ MAXN + 1 ];
int ans[ MAXN + 1 ], CC[ INF + 1 ], cnt = 1;

void add1( int val, int range ) // adding to tree for y1 < y
{
	while( range <= maxp ) {
		BIT[ range ][ 0 ] = max( BIT[ range ][ 0 ], val );
		range += ( range & -range );
	}
}

void add2( int val, int range ) // adding to tree for y1 >= y
{
	while( range > 0 ) {
		BIT[ range ][ 1 ] = max( BIT[ range ][ 1 ], val );
		range -= ( range & -range );
	}
}

int get_rmq1( int range ) // retrieving from tree for y1 < y
{
	int sol = -4*INF;
	while( range > 0 ) {
		sol = max( sol, BIT[ range ][ 0 ] );
		range -= ( range & -range );
	}
	return sol;
}

int get_rmq2( int range ) // retrieving from tree for y1 >= y
{
	int sol = -4*INF;
	while( range <= maxp ) {
		sol = max( sol, BIT[ range ][ 1 ] );
		range += ( range & -range );
	}
	return sol;
}

int readint() {
    int n = 0;
    char c = getchar_unlocked();
    while ( !( '0' <= c && c <= '9' ) ) {
        c = getchar_unlocked();
    }
    while ( '0' <= c && c <= '9' ) {
        n = n * 10 + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

void compress( int N )
{
	vector< int > V;
	for( int i = 1; i <= N; i++ ) {
		V.pb( Pall[ i ].P.Y );
	}
	sort( V.begin(), V.end() );
	for( int i = 0; i < N; i++ ) {
		if( !CC[ V[ i ] ] ) CC[ V[ i ] ] = cnt++;
	}
}

int main( void )
{
	int N, x, y;
	N = readint();
	for( int i = 1; i <= N; i++ ) {
		x = readint();	
		y = readint();
		ans[ i ] = 4*INF;
		Pall[ i ] = ( point ) { mp( x + 1, y + 1 ), i };
	}
	sort( Pall + 1, Pall + N + 1 );
	compress( N );
	maxp = cnt + 10;
	for( int i = 1; i <= maxp; i++ ) BIT[ i ][ 0 ] = BIT[ i ][ 1 ] = -4*INF;
	for( int i = 1; i <= N; i++ ) {
		int q1 = get_rmq1( CC[ Pall[ i ].P.Y ] );
		int q2 = get_rmq2( CC[ Pall[ i ].P.Y ] + 1 );
		if( q1 ) ans[ Pall[ i ].idx ] = min( ans[ Pall[ i ].idx ], Pall[ i ].P.X + Pall[ i ].P.Y - q1 );
		if( q2 ) ans[ Pall[ i ].idx ] = min( ans[ Pall[ i ].idx ], Pall[ i ].P.X - Pall[ i ].P.Y - q2 );
		add1( Pall[ i ].P.X + Pall[ i ].P.Y, CC[ Pall[ i ].P.Y ] );
		add2( Pall[ i ].P.X - Pall[ i ].P.Y, CC[ Pall[ i ].P.Y ]  );
	}
	for( int i = 1; i <= maxp; i++ ) BIT[ i ][ 0 ] = BIT[ i ][ 1 ] = -4*INF;
	for( int i = N; i > 0; i-- ) {
		int q1 = get_rmq1( CC[ Pall[ i ].P.Y ] );
		int q2 = get_rmq2( CC[ Pall[ i ].P.Y ] + 1 );
		if( q1 ) ans[ Pall[ i ].idx ] = min( ans[ Pall[ i ].idx ], -Pall[ i ].P.X + Pall[ i ].P.Y - q1 );
		if( q2 ) ans[ Pall[ i ].idx ] = min( ans[ Pall[ i ].idx ], -Pall[ i ].P.X - Pall[ i ].P.Y - q2 );
		add1( -Pall[ i ].P.X + Pall[ i ].P.Y, CC[ Pall[ i ].P.Y ] );
		add2( -Pall[ i ].P.X - Pall[ i ].P.Y, CC[ Pall[ i ].P.Y ] );
	}
	for( int i = 1; i <= N; i++ ) {
		printf("%d\n", ans[ i ] );
	}
	return 0;
}
