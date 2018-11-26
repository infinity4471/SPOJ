#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <set>

#define MAXN 200100
#define INF 1234567890123456LL

using namespace std;

typedef long long ll;

ll A[ MAXN + 1 ];

map< ll, int > rank;
set< ll > S;

ll BIT[ MAXN + 1 ][ 2 ];

void add1( int u, ll val ) {
    while( u <= MAXN ) {
        BIT[ u ][ 0 ] = min( BIT[ u ][ 0 ], val );
        u += ( u & -u );
    }
}

ll RMQ1( int u ) { // backwards for smaller elements
    ll rm = INF;
    while( u > 0 ) {
        rm = min( rm, BIT[ u ][ 0 ] );
        u -= ( u & -u );
    }
    return rm;
}

void add2( int u, ll val ) {
    while( u > 0 ) {
        BIT[ u ][ 1 ] = min( BIT[ u ][ 1 ], val );
        u -= ( u & -u );
    }
}

ll RMQ2( int u ) { // forward for bigger elements
    ll rm = INF;
    while( u <= MAXN ) {
        rm = min( rm, BIT[ u ][ 1 ] );
        u += ( u & -u );
    }
    return rm;
}

void init() {
    for( int i = 1; i <= MAXN; i++ ) {
        BIT[ i ][ 0 ] = BIT[ i ][ 1 ] = INF;
    }
}

int main() {
    int T;
    scanf("%d", &T );
    while( T-- ) {
        int N, i;
        init();
        ll ans = 0;
        scanf("%d", &N );
        for( i = 1; i <= N; i++ ) {    
            scanf("%lld", &A[ i ] );
            S.insert( A[ i ] );          
        }
        i = 1;
        for( set< ll >::iterator it = S.begin(); it != S.end(); ++it ) rank[ *it ] = i++;
        
        for( i = 2; i <= N; i++ ) {
            ll val1 = ( ll )A[ i - 1 ] * ( ll )A[ i - 1 ] + ( ll )( i - 1 ) * ( ll )( i - 1 );
            ll val2 = -1LL*A[ i - 1 ] * ( ll )A[ i - 1 ] + ( ll )( i - 1 ) * ( ll )( i - 1 );
            ll newval1 = ( ll )A[ i ] * ( ll )A[ i ] + ( ll )i * ( ll )i;
            ll newval2 = -1LL*( ll )A[ i ] * ( ll )A[ i ] + ( ll )i * ( ll )i;
            add1( rank[ A[ i - 1 ] ], val1 );
            add2( rank[ A[ i - 1 ] ], val2 );
            ll rmq1 = RMQ1( rank[ A[ i ] ] );
            ll rmq2 = RMQ2( rank[ A[ i ] ] );
            ans = max( ans, max( newval1 - rmq1, newval2 - rmq2 ) );
        }
        printf("%lld\n", ans );
        S.clear();
        rank.clear();
    }
    return 0;
}
