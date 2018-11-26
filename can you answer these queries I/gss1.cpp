#include <cstdio>
#include <algorithm>
 
#define MAXN 50050
 
using namespace std;
 
struct node {
        int ans, mpref, msuf, sum;
};
 
node segtree[ 4*MAXN + 1 ];
 
int N, A[ MAXN + 1 ];
 
void init( int n, int l, int r ) {
    if( l == r ) {
        segtree[ n ].sum = A[ l ];
        segtree[ n ].mpref = A[ l ];
        segtree[ n ].msuf = A[ l ];
        segtree[ n ].ans = A[ l ];
    } else {
        int mid = ( l + r ) >> 1;
        init( 2*n, l, mid );
        init( 2*n + 1, mid + 1, r );
        segtree[ n ].sum = segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum;
        segtree[ n ].ans = max( 
        max( segtree[ 2*n ].ans, segtree[ 2*n + 1 ].ans ),
        segtree[ 2*n ].msuf + segtree[ 2*n + 1 ].mpref );
        
        segtree[ n ].mpref = max( segtree[ 2*n ].mpref, 
        segtree[ 2*n ].sum + segtree[ 2*n + 1 ].mpref );
        
        segtree[ n ].msuf = max( segtree[ 2*n + 1 ].msuf,
        segtree[ 2*n + 1 ].sum + segtree[ 2*n ].msuf );
    }
}
 
node query( int n, int l, int r, int i, int j ) {
    if( l == i && r == j ) return segtree[ n ];
    int mid = ( l + r ) >> 1;
    if( j <= mid ) return query( 2*n, l, mid, i, j );
    else if( i > mid ) return query( 2*n + 1, mid + 1, r, i, j );
    node A = query( 2*n, l, mid, i, mid );
    node B = query( 2*n + 1, mid + 1, r, mid + 1, j );
    node C;
    C.sum = A.sum + B.sum;
    C.ans = max( max( A.ans, B.ans ), A.msuf + B.mpref );
    C.mpref = max( A.mpref, A.sum + B.mpref );
    C.msuf = max( B.msuf, B.sum + A.msuf );
    return C;
 
}
 
int main( void ) {	
    scanf("%d", &N );
    for( int i = 1; i <= N; i++ ) {
        scanf("%d", &A[ i ] );
    }
    init( 1, 1, N );
    int Q;
    scanf("%d", &Q );
    while( Q-- ) {
            int x, y;
            scanf("%d %d", &x, &y );
            node A = query( 1, 1, N, x, y );
            printf("%d\n", A.ans );
    }
    return 0;
}