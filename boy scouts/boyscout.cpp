#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

#define X first
#define Y second
#define mp make_pair
#define pb push_back

#define MAXN 150
#define INF 10000000.0

using namespace std;

typedef pair< long double, long double > pdd;

int N, memo[ MAXN + 1 ][ MAXN + 1 ];
pdd stand; 
vector< pdd > P, P2;

long double CCW( pdd A, pdd B, pdd C ) {
    return ( long double )( B.X - A.X ) * ( long double )( C.Y - A.Y ) - ( long double )( B.Y - A.Y ) * ( long double )( C.X - A.X );
}

long double dist( pdd A, pdd B ) {
    return ( long double  )( A.X - B.X ) * ( long double )( A.X - B.X ) + ( long double )( A.Y - B.Y ) * ( long double )( A.Y - B.Y );
}

bool cmp( pdd A, pdd B ) {
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

int fix_origin( int id ) {
    P2 = P;
    memset( memo, -1, sizeof( memo ) );
    swap( P[ id ], P[ 0 ] );
    for( int i = 1; i < P.size(); i++ ) {
        if( P[ i ].Y < P[ 0 ].Y ) {
            P.erase( P.begin() + i );
            i--;
        }
    }
    int newN = N;
    N = P.size();
    stand = P[ 0 ];
    sort( ++P.begin(), P.end(), cmp );
    int res = dp( 0, 0 );
    P = P2;
    N = newN;
    return res;
}

int main() {
    long double x, y;
    int ans = 0;
    scanf("%d", &N );
    for( int i = 0; i < N; i++ ) {
        cin >> x >> y;
        P.pb( mp( x, y ) );
    }
    for( int i = 0; i < N; i++ ) {
        ans = max( ans, fix_origin( i ) );
    }
    printf("%d\n", ans );
    return 0;
}
