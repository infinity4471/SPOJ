#include <cstdio>
#include <algorithm>

#define MAXN 100100

using namespace std;

int A[ MAXN + 1 ], segtree[ 4*MAXN + 1 ];

void init( int n, int l, int r ) {
    if( l == r ) segtree[ n ] = 1;
    else {
        init( 2*n, l, ( l + r ) / 2 );
        init( 2*n + 1, ( l + r ) / 2 + 1, r );
        segtree[ n ] = segtree[ 2*n ] + segtree[ 2*n + 1 ];
    }
}

void update( int n, int l, int r, int idx ) {
    if( l == r ) {
        segtree[ n ]--;
        return;
    }
    if( idx <= ( l + r ) / 2 ) update( 2*n, l, ( l + r ) / 2, idx );
    else update( 2*n + 1, ( l + r ) / 2 + 1, r, idx );
    segtree[ n ] = segtree[ 2*n ] + segtree[ 2*n + 1 ];
}

int find( int n, int l, int r, int num ) {
    if( l == r ) return l;
    int S1 = segtree[ 2*n ], S2 = segtree[ 2*n + 1 ], mid = ( l + r ) / 2;
    if( S1 >= num ) return find( 2*n, l, mid, num );
    else return find( 2*n + 1, mid + 1, r, num - S1 );
}

int main() {
    int T;
    scanf("%d", &T );
    for( int l = 1; l <= T; l++ ) {
        int N, status = true;
        scanf("%d", &N );
        for( int i = 1; i <= N; i++ ) {
            scanf("%d", &A[ i ] );
            if( A[ i ] >= i ) status = false;
            A[ i ] = i - A[ i ];
        }
        init( 1, 1, N );
        for( int i = N; i > 0; i-- ) {
            A[ i ] = find( 1, 1, N, A[ i ] );
            update( 1, 1, N, A[ i ] );
        }
        printf("Test : %d\n", l );
        if( !status ) {
            printf("-1\n");
            continue;
        }
        printf("%d", A[ 1 ] );
        for( int i = 2; i <= N; i++ ) {
            printf(" %d", A[ i ] );
        }
        printf("\n");
    }
    return 0;
}
