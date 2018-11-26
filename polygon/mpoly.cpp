#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define X first
#define Y second
#define mp make_pair
#define pb push_back

#define MAXN 150

using namespace std;

typedef pair< int, int > pii;

int N, memo[ MAXN + 1 ][ MAXN + 1 ];
const pii stand = mp( 0, 0 ); 
vector< pii > P;

int CCW( pii A, pii B, pii C ) {
    return ( B.X - A.X ) * ( C.Y - A.Y ) - ( B.Y - A.Y ) * ( C.X - A.X );
}

int dist( pii A, pii B ) {
    return ( A.X - B.X ) * ( A.X - B.X ) + ( A.Y - B.Y ) * ( A.Y - B.Y );
}

bool cmp( pii A, pii B ) {
    if( !CCW( stand, A, B ) ) {
        return dist( stand, A ) > dist( stand, B );
    }
    return CCW( stand, A, B ) > 0;
}

int dp( int n,  int m ) {
    int& res = memo[ n ][ m ];
    if( res != -1 ) return res;
    res = 0;
    if( CCW( P[ n ], P[ m ], P[ 0 ] ) > 0 ) res = 1;
    for( int i = m + 1; i < N; i++ ) {
        if( CCW( P[ n ], P[ m ], P[ i ] ) > 0 || ( n + m == 0 ) ) {
            res = max( res, 1 + dp( m, i ) );
        }
    }
    return res;
}

int main() {
    int x, y, ans = 0;
    scanf("%d", &N );
    for( int i = 0; i < N; i++ ) {
        scanf("%d%d", &x, &y );
        P.pb( mp( x, y ) );
    }
    N++;
    memset( memo, -1, sizeof( memo ) );
    P.pb( mp( 0, 0 ) );
    swap( P[ N - 1 ], P[ 0 ] );
    sort( ++P.begin(), P.end(), cmp );
    printf("%d\n", dp( 0, 0 ) );
    return 0;
}
