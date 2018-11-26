#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAXN 30000

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

int dp[ MAXN + 1 ], BIT[ MAXN + 1 ];

void add( int x, int val ) {
    while( x > 0 ) {
        BIT[ x ] = max( BIT[ x ], val );
        x -= ( x & -x );
    }
}

int get( int u ) {
    int val = 0;
    while( u <= MAXN ) {
        val = max( val, BIT[ u ] );
        u += ( u & -u );
    }
    return val;
}

bool cmp( pii A, pii B ) {
    if( A.X == B.X ) return A.Y > B.Y;
    return A.X < B.X;
}

int main() {
    int T;
    scanf("%d", &T );
    while( T-- ) {
        int N, x, y, ans = 0;
        scanf("%d", &N );
        pii D[ N + 1 ];;
        for( int i = 1; i <= N; i++ ) {
            scanf("%d%d", &x, &y );
            D[ i ] = mp( x, y );
        }
        sort( D + 1, D + N + 1, cmp );
        for( int i = 1; i <= N; i++ ) {
            dp[ i ] = 1 + get( D[ i ].Y );
            add( D[ i ].Y, dp[ i ] );
            ans = max( ans, dp[ i ] );
        }
        printf("%d\n", ans );
        memset( BIT, 0, sizeof( BIT ) );
    }
    return 0;
}
