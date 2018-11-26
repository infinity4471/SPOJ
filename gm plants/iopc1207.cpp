#include <cstdio>
#include <algorithm>

#define MAXN 101000

using namespace std;

typedef long long ll;

struct node {
    int D[ 3 ], flag[ 3 ];
};

int NX, NY, NZ;

node* segtree;

void unflag( int n, int l, int r, int id ) {
    if( segtree[ n ].flag[ id ] ) {
        segtree[ n ].D[ id ] = ( r - l + 1 ) - segtree[ n ].D[ id ];
        if( l != r ) {
            segtree[ 2*n ].flag[ id ] = 1 - segtree[ 2*n ].flag[ id ];
            segtree[ 2*n + 1 ].flag[ id ] = 1 - segtree[ 2*n + 1 ].flag[ id ];
        }
        segtree[ n ].flag[ id ] = false;
    }
}

void update( int n, int l, int r, int i, int j, int id ) {
    if( r < i || l > j ) {
        unflag( n, l, r, id );
        return;
    }
    else if( i <= l && r <= j ) {
        segtree[ n ].flag[ id ] = 1 - segtree[ n ].flag[ id ];
        unflag( n, l, r, id );
    } else {
        int mid = ( l + r ) / 2;
        unflag( n, l, r, id );
        update( 2*n, l, mid, i, j, id );
        update( 2*n + 1, mid + 1, r, i, j, id );
        if( l != r ) segtree[ n ].D[ id ] = segtree[ 2*n ].D[ id ] + segtree[ 2*n + 1 ].D[ id ];
    }
}

int query( int n, int l, int r, int i, int j, int id ) {
    int mid = ( l + r ) / 2;
    unflag( n, l, r, id );
    if ( r < i || l > j ) return 0;
    if( i <= l && r <= j ) return segtree[ n ].D[ id ];
    else return query( 2*n, l, mid, i, j, id ) + query( 2*n + 1, mid + 1, r, i, j, id );
}

int main() {
    int T;
    scanf("%d", &T );
    while( T-- ) {
        segtree = new node[ 4*MAXN + 1 ];

        int Q;
        scanf("%d%d%d%d", &NX, &NY, &NZ, &Q );
        while( Q-- ) {
            int q, x1, y1, x2, y2, z1, z2;
            scanf("%d", &q );
            if( q < 3 ) {
                scanf("%d%d", &z1, &z2 );
                update( 1, 1, MAXN, z1, z2, q ); 
            } else {
                scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2 );
                ll area = 0, n1 = ( ll )( x2 - x1 + 1 ), n2 = ( ll )( y2 - y1 + 1 ), n3 = ( ll )( z2 - z1 + 1 );
                ll qx = ( ll )query( 1, 1, MAXN, x1, x2, 0 );
                ll qy = ( ll )query( 1, 1, MAXN, y1, y2, 1 );
                ll qz = ( ll )query( 1, 1, MAXN, z1, z2, 2 );
                area = ( ll )qx * n2 * n3 + ( ll )qy * n1 * n3 + ( ll )qz * n2 * n1;
                area -= 2LL * qx * qy * n3 + 2LL * qx * qz * n2 + 2LL * qy * qz * n1 - 4LL * qx * qy * qz;
                printf("%lld\n", area );
            }
        }
        delete [] segtree;
    }
    return 0;
}
