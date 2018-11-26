#include <cstdio>
#include <algorithm>

#define MAXN 10100

using namespace std;

struct node {
  int sum, subsum, prefix, suffix;
};

node segtree[ 4*MAXN + 1 ];

int N, A[ MAXN + 1 ];

node make_it( node A, node B ) {
  node newn;
  newn.sum = A.sum + B.sum;
  newn.prefix = max( A.prefix, A.sum + B.prefix );
  newn.suffix = max( B.suffix, B.sum + A.suffix );
  newn.subsum = max( max( A.subsum, B.subsum ), A.suffix + B.prefix );
  return newn;
}

void init( int n, int l, int r ) {
  if( l == r ) {
    segtree[ n ].sum = segtree[ n ].subsum = segtree[ n ].prefix = segtree[ n ].suffix = A[ l ];
  } else {
    int mid = ( l + r ) >> 1;
    init( 2*n, l, mid );
    init( 2*n + 1, mid + 1, r );
    segtree[ n ] = make_it( segtree[ 2*n ], segtree[ 2*n + 1 ] );
  }
}

node query( int n, int l, int r, int i, int j ) {
  if( j < i ) return ( node ) { 0, 0, 0, 0 };
  int mid = ( l + r ) >> 1;
  if( l == i && r == j ) return segtree[ n ];
  else if( j <= mid ) return query( 2*n, l, mid, i, j );
  else if( i > mid ) return query( 2*n + 1, mid + 1, r, i, j );
  else {
    node A = query( 2*n, l, mid, i, mid );
    node B = query( 2*n + 1, mid + 1, r, mid + 1, j );
    return make_it( A, B );
  }
}

int main( void ) {
  int T, Q;
  scanf("%d", &T );
  while( T-- ) {
    scanf("%d", &N );
    for( int i = 1; i <= N; i++ ) scanf("%d", &A[ i ] );
    init( 1, 1, N );
    scanf("%d", &Q );
    while( Q-- ) {
      int x1, x2, y1, y2;
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2 );
      if( y1 < x2 ) {
        printf("%d\n", query( 1, 1, N, x1, y1 ).suffix + query( 1, 1, N, y1 + 1, x2 - 1 ).sum + query( 1, 1, N, x2, y2 ).prefix );
      } else {
        int ans = query( 1, 1, N, x2, y1 ).subsum;
        ans = max( ans, query( 1, 1, N, x1, x2 - 1 ).suffix + query( 1, 1, N, x2, y2 ).prefix );
        ans = max( ans, query( 1, 1, N, x1, y1 ).suffix + query( 1, 1, N, y1 + 1, y2 ).prefix );
        printf("%d\n", ans );
      }
    }
  }
  return 0;
}
