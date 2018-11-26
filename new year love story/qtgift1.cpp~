#include <cstdio>
#include <algorithm>
#include <list>

#define MAXN 1010000

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

int S[ MAXN + 1 ], dp[ MAXN + 1 ], A[ MAXN + 1 ];
pii Q[ MAXN + 1 ];
int beg = 1, end = 1;

inline int readint() {
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

int main( void )
{
	int N, K;
	N = readint();
	K = readint() - 1;
	for( int i = 1; i <= N; i++ ) {
		A[ i ] = readint();
		S[ i ] = S[ i - 1 ] + A[ i ];
	}
	for( int i = 1; i <= K; i++ ) {
		dp[ i ] = S[ i ];
		int val = dp[ i - 1 ] - S[ i ];
		while( beg <= end && Q[ end ].X <= val ) end--;
		Q[ ++end ] = mp( val, i );
	}
	for( int i = K + 1; i <= N; i++ ) {
		int val = dp[ i - 1 ] - S[ i ];
		if( beg <= end && Q[ beg ].Y < i - K ) beg++;
		while( beg <= end && Q[ end ].X <= val ) end--;
		Q[ ++end ] = mp( val, i );
		dp[ i ] = S[ i ] + Q[ beg ].X;
	}
	printf("%d\n", dp[ N ] );
	return 0;
}
