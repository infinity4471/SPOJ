#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXN 100100
#define MOD 1000000007LL
#define pb push_back

using namespace std;

typedef long long ll;

struct node {
    ll val, SH, flag1, flag2, isup;
    // flag 1 is for K, flag 2 is for x
};

vector< int > T[ MAXN + 1 ];
int pos[ MAXN + 1 ], sub_size[ MAXN + 1 ], height[ MAXN + 1 ], par[ MAXN + 1 ], A[ MAXN + 1 ], cnt = 0;

node segtree[ 4*MAXN + 1 ];

void dfs( int u, int h ) {
    sub_size[ u ] = 1;
    pos[ u ] = ++cnt;
    A[ cnt ] = u;
    height[ u ] = h;
    for( int i = 0; i < T[ u ].size(); i++ ) {
        int v = T[ u ][ i ];
        if( v == par[ u ] ) continue;
        dfs( v, h + 1 );
        sub_size[ u ] += sub_size[ v ];
    }
}

void init( int n, int l, int r ) {
    if( l == r ) {
        segtree[ n ].val = segtree[ n ].flag1 = segtree[ n ].flag2 = 0;
        segtree[ n ].SH = ( ll )height[ A[ l ] ];
    } else {
        int mid = ( l + r ) / 2;
        init( 2*n, l, mid );
        init( 2*n + 1, mid + 1, r );
        segtree[ n ].val = segtree[ n ].flag1 = segtree[ n ].flag2 = 0;
        segtree[ n ].SH = ( ll )( ( ll )segtree[ 2*n ].SH + ( ll )segtree[ 2*n + 1 ].SH ) % MOD;
    }
}

void unflag( int n, int l, int r ) {
    if( segtree[ n ].isup ) {
        segtree[ n ].val = ( segtree[ n ].val + ( ( ll )( r - l + 1 )*segtree[ n ].flag2  % MOD ) ) % MOD;
        segtree[ n ].val = ( segtree[ n ].val + ( ( ll )segtree[ n ].flag1 * segtree[ n ].SH  % MOD ) ) % MOD;
        if( l != r ) {
            segtree[ 2*n ].flag1 = ( segtree[ 2*n ].flag1 + segtree[ n ].flag1 ) % MOD;
            segtree[ 2*n + 1 ].flag1 = ( segtree[ 2*n + 1 ].flag1 + segtree[ n ].flag1 ) % MOD;
            segtree[ 2*n ].flag2 = ( segtree[ 2*n ].flag2 + segtree[ n ].flag2 ) % MOD;
            segtree[ 2*n + 1 ].flag2 = ( segtree[ 2*n + 1 ].flag2 + segtree[ n ].flag2 ) % MOD;
            segtree[ 2*n ].isup = segtree[ 2*n + 1 ].isup = 1;
        }
        segtree[ n ].isup = 0;
        segtree[ n ].flag2 = 0;
        segtree[ n ].flag1 = 0;
    }
}

void update( int n, int l, int r, int i, int j, ll X, ll K, ll H ) {
    if( r < i || l > j ) {
        unflag( n, l, r );
    }
    else if( i <= l && r <= j ) {
        segtree[ n ].isup = 1;
        segtree[ n ].flag1 = ( ll )( segtree[ n ].flag1 + K ) % MOD;
        segtree[ n ].flag2 = ( ll )( segtree[ n ].flag2 + ( ll )X - ( ll )K*H ) % MOD;
        if( segtree[ n ].flag2 < 0 ) segtree[ n ].flag2 += MOD;
        unflag( n, l, r );
    } else {
        unflag( n, l, r );
        int mid = ( l + r ) / 2;
        update( 2*n, l, mid, i, j, X, K, H );
        update( 2*n + 1, mid + 1, r, i, j, X, K, H );
        if( l != r ) {
            segtree[ n ].val = ( ll )( segtree[ 2*n ].val + segtree[ 2*n + 1 ].val ) % MOD;
        }
    }
}

ll query( int n, int l, int r, int i, int j ) {
    unflag( n, l, r );
    int mid = ( l + r ) / 2;
    if( r < i || l > j ) return 0;
    else if( i <= l && r <= j ) return segtree[ n ].val;
    else return ( ll )( query( 2*n, l, mid, i, j ) + query( 2*n + 1, mid + 1, r, i, j ) ) % MOD;
}

int main() {
    int N, M;
    scanf("%d", &N );
    for( int i = 2; i <= N; i++ ) {
        scanf("%d", &par[ i ] );
        T[ i ].pb( par[ i ] );
        T[ par[ i ] ].pb( i );
    }
    dfs( 1, 0 );
    init( 1, 1, N );
    scanf("%d", &M );
    while( M-- ) {
        int t, u, x, k;
        scanf("%d%d", &t, &u );
        if( t == 1 ) {
            scanf("%d%d", &x, &k );
            update( 1, 1, N, pos[ u ], pos[ u ] + sub_size[ u ] - 1, ( ll )x, ( ll )k, ( ll )height[ u ] );
        } else {
            printf("%lld\n", query( 1, 1, N, pos[ u ], pos[ u ] + sub_size[ u ] - 1 ) );
        }
    }
    return 0;
}
