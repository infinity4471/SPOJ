#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 100010
#define MAXSIZE 10001000

using namespace std;

typedef long long ll;

int N, Q;
int roots[ MAXN + 1 ][ 2 ], left[ MAXSIZE + 1 ][ 2 ], right[ MAXSIZE + 1 ][ 2 ], nodecnt[ 2 ];
ll segtree[ MAXSIZE + 1 ][ 2 ];

inline int L( int n, int d ) {
  if( !left[ n ][ d ] ) {
    left[ n ][ d ] = nodecnt[ d ] + 1;
    nodecnt[ d ]++;
  }
  return left[ n ][ d ];
}

inline int R( int n, int d ) {
  if( !right[ n ][ d ] ) {
    right[ n ][ d ] = nodecnt[ d ] + 1;
    nodecnt[ d ]++;
  }
  return right[ n ][ d ];
}

void update( int n, int preved, int d, int l, int r, int idx, int val ) {
  if( l == r ) {
    segtree[ n ][ d ] = segtree[ preved ][ d ] + val;
    return;
  }
  int mid = ( l + r ) / 2;
  if( idx <= mid ) {
    update( L( n, d ), L( preved, d ), d, l, mid, idx, val );
    right[ n ][ d ] = right[ preved ][ d ];
  } else {
    update( R( n, d ), R( preved, d ), d, mid + 1, r, idx, val );
    left[ n ][ d ] = left[ preved ][ d ];
  }
  segtree[ n ][ d ] = segtree[ L( n, d ) ][ d ] + segtree[ R( n, d ) ][ d ];
}

void update_normal( int n, int d, int l, int r, int idx, int val ) {
  printf("normal update function %d, %d, %d, %d\n", n, d,l , r );
  if( l == r ) {
    segtree[ n ][ d ] += val;
    return;
  }
  int mid = ( l + r ) / 2;
  if( idx <= mid ) update_normal( L( n, d ), d, l, mid, idx, val );
  else update_normal( R( n, d ), d, mid + 1, r, idx, val );
  segtree[ n ][ d ] = segtree[ L( n, d ) ][ d ] + segtree[ R( n, d ) ][ d ];
}

ll query( int n, int d, int l, int r, int i, int j ) {
  int mid = ( l + r ) / 2;
  if( r < i || l > j ) return 0;
  else if( i <= l && r <= j ) return segtree[ n ][ d ];
  else return query( L( n, d ), d, l, mid, i, j ) + query( R( n, d ), d, mid + 1, r, i, j );
}

void range_update( int i, int j, int edition, ll val ) {
  update( roots[ edition ][ 0 ], roots[ edition - 1 ][ 0 ], 0, 1, N, i, val );
  if( j < N ) update( roots[ edition ][ 0 ], roots[ edition - 1 ][ 0 ], 0, 1, N, j + 1, -val );
  update( roots[ edition ][ 1 ], roots[ edition - 1 ][ 1 ], 1, 1, N, i, ( ll )( i - 1 ) * val );
  if( j < N ) update( roots[ edition ][ 1 ], roots[ edition - 1 ][ 1 ], 1, 1, N, j + 1, -( ll )( i - 1 ) * val - val * ( ll )( j - i + 1 ) );
}

void range_update_normal( int i, int j, ll val ) {
  update_normal( 1, 0, 1, N, i, val );
  if( j < N ) update_normal( 1, 0, 1, N, j + 1, -val );
  update_normal( 1, 1, 1, N, i, ( ll )( i - 1 ) * val );
  if( j < N ) update_normal( 1, 1, 1, N, j + 1, -( ll )( i - 1 ) * val - val * ( ll )( j - i + 1 ) );
}

ll range_query( int i, int j, int edition ) {
  ll suma = 0, sumb = 0;
  if( i > 1 ) suma = query( roots[ edition ][ 0 ], 0, 1, N, 1, i - 1 ) * ( i - 1 ) - query( roots[ edition ][ 1 ], 1, 1, N, 1, i - 1 );
  sumb = query( roots[ edition ][ 0 ], 0, 1, N, 1, j ) - query( roots[ edition ][ 1 ], 1, 1, N, 1, j );
  printf("suma -> %lld\n", suma );
  return sumb - suma;
}

int A[ MAXN + 1 ];

int main( void ) {
  scanf("%d%d", &N, &Q );

  memset( segtree, 0 ,sizeof( segtree ) );
  nodecnt[ 0 ] = nodecnt[ 1 ] = 2;
  roots[ 0 ][ 0 ] = 1;
  roots[ 0 ][ 1 ] = 1;
  for( int i = 1; i <= N; i++ ) {
    scanf("%d", &A[ i ] );
    range_update_normal( i, i, ( ll )A[ i ] );
  }
  int cured = 0;
  while( Q-- ) {
    char c;
    scanf(" %c", &c );
    if( c == 'C' ) {
      int l, r, d;
      scanf("%d%d%d", &l, &r, &d );
      cured++;
      range_update( l, r, cured, ( ll )d );
      roots[ cured ][ 0 ] = nodecnt[ 0 ];
      roots[ cured ][ 1 ] = nodecnt[ 1 ];
    }
    else if( c == 'Q' ) {
      int l, r;
      scanf("%d%d", &l, &r );
      printf("%lld\n", range_query( l, r, cured ) );
    }
    else if( c == 'H' ) {
      int l, r, t;
      scanf("%d%d", &l, &r );
      printf("%lld\n", range_query( l, r, t ) );
    } else {
      int t;
      scanf("%d", &t );
      cured = t;
    }
  }
  return 0;
}
