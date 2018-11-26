#include <cstdio>
#include <algorithm>

#define MAXN 30010

using namespace std;

struct node {
  int minpref, sum;
};

node segtree[ 4 * MAXN + 1 ];

char S[ MAXN + 1 ];
int N, A[ MAXN + 1 ];

void init( int n, int l, int r ) {
  if( l == r ) {
    segtree[ n ].minpref = segtree[ n ].sum = A[ l ];
  } else {
    int mid = ( l + r ) >> 1;
    init( 2*n, l, mid );
    init( 2*n + 1, mid + 1, r );
    segtree[ n ].minpref = min( segtree[ 2*n ].minpref, segtree[ 2*n + 1 ].minpref + segtree[ 2*n ].sum );
    segtree[ n ].sum = segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum;
  }
}

void replace( int n, int l, int r, int idx ) {
  if( l == r ) {
    if( segtree[ n ].sum == 1 ) segtree[ n ].sum = segtree[ n ].minpref = -1;
    else segtree[ n ].sum = segtree[ n ].minpref = 1;
    return;
  }
  int mid = ( l + r ) >> 1;
  if( idx <= mid ) replace( 2*n, l, mid, idx );
  else replace( 2*n + 1, mid + 1, r, idx );
  segtree[ n ].minpref = min( segtree[ 2*n ].minpref, segtree[ 2*n + 1 ].minpref + segtree[ 2*n ].sum );
  segtree[ n ].sum = segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum;
}

bool check() {
  return segtree[ 1 ].minpref == 0 && segtree[ 1 ].sum == 0;
}

int main( void ) {
  for( int t = 0; t < 10; t++ ) {
    int Q, u;
    scanf("%d%s", &N, S );
    for( int i = 1; i <= N; i++ ) {
      if( S[ i - 1 ] == '(' ) A[ i ] = 1;
      else A[ i ] = -1;

    }
    printf("Test %d:\n", t + 1 );
    init( 1, 1, N );
    scanf("%d", &Q );
    while( Q-- ) {
      scanf("%d", &u );
      if( u == 0 ) {
        if( check() ) printf("YES\n");
        else printf("NO\n");
      }
      else replace( 1, 1, N, u );
    }
  }
  return 0;
}
