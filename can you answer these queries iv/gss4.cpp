#include <cstdio>
#include <algorithm>
#include <cmath>

#define MAXL 30
#define MAXN 100001

using namespace std;

typedef long long ll;

struct node {
  ll sumroots[ MAXL + 1 ];
  int pointer, flag;
};

int N, Q;
ll A[ MAXN + 1 ];
node segtree[ 3 * MAXN + 1 ];

inline ll sumit( int n, int l, int r, int p ) {
  if( p > MAXL ) return ( ll )( r - l + 1 );
  return segtree[ n ].sumroots[ p ];
}

void init( int n, int l, int r ) {
  segtree[ n ].flag = 0;
  if( l == r ) {
    segtree[ n ].pointer = 1;
    segtree[ n ].sumroots[ 1 ] = ( ll )A[ l ];
    for( int i = 2; i <= MAXL; i++ ) segtree[ n ].sumroots[ i ] = ( ll )sqrt( segtree[ n ].sumroots[ i - 1 ] );
  } else {
    int mid = ( l + r ) >> 1;
    init( n << 1, l, mid );
    init( ( n << 1 ) | 1, mid + 1, r );
    segtree[ n ].pointer = 1;
    for( int i = 1; i <= MAXL; i++ ) segtree[ n ].sumroots[ i ] = segtree[ n << 1 ].sumroots[ i ] + segtree[ ( n << 1 ) | 1 ].sumroots[ i ];
  }
}

void unflag( int n, int l, int r ) {
  if( segtree[ n ].flag ) {
    segtree[ n ].pointer += segtree[ n ].flag;
    if( l != r ) {
      segtree[ ( n << 1 ) ].flag += segtree[ n ].flag;
      segtree[ ( n << 1 ) | 1 ].flag += segtree[ n ].flag;
    }
    segtree[ n ].flag = 0;
  }
}

void update( int n, int l, int r, int i, int j ) {
  int mid = ( l + r ) >> 1;
  if( sumit( n, l, r, segtree[ n ].pointer ) == r - l + 1 ) return;
  if( r < i || l > j ) unflag( n, l, r );
  else if( i <= l && r <= j ) {
    segtree[ n ].flag++;
    unflag( n, l, r );
  } else {
    unflag( n, l, r );
    if( sumit( n, l, r, segtree[ n ].pointer ) == r - l + 1 ) return;
    update( ( n << 1 ), l, mid, i, j );
    update( ( n << 1 ) | 1, mid + 1, r, i, j );
    if( l != r ) {
      segtree[ n ].pointer = 1;
      int p1 = segtree[ ( n << 1 ) ].pointer, p2 = segtree[ ( n << 1 ) | 1 ].pointer;
      for( int i = 1; i <= MAXL; i++ ) segtree[ n ].sumroots[ i ] = sumit( n << 1, l, mid, p1++ ) + sumit( ( n << 1 ) | 1, mid + 1, r, p2++ );
    }
  }
}

ll query( int n, int l, int r, int i, int j ) {
  int mid = ( l + r ) >> 1;
  unflag( n, l, r );
  if( r < i || l > j ) return 0LL;
  else if( i <= l && r <= j ) return sumit( n, l, r, segtree[ n ].pointer );
  else return query( ( n << 1 ), l, mid, i, j ) + query( ( n << 1 ) | 1, mid + 1, r, i, j );
}

int readint() {
    int n = 0;
    char c = getchar_unlocked();
    while ( !( '0' <= c && c <= '9' ) ) {
        c = getchar_unlocked();
    }
    while ( '0' <= c && c <= '9' ) {
        n = n * 10 + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

ll readlong() {
    ll n = 0LL;
    char c = getchar_unlocked();
    while ( !( '0' <= c && c <= '9' ) ) {
        c = getchar_unlocked();
    }
    while ( '0' <= c && c <= '9' ) {
        n = n * 10LL + c - ( ll )( '0' );
        c = getchar_unlocked();
    }
    return n;
}

int main( void ) {
  int t = 0, i;
  while( scanf("%d", &N ) == 1 ) {
    for( i = 1; i <= N; ++i ) A[ i ] = readlong();
    init( 1, 1, N );

    Q = readint();
    printf("Case #%d:\n", ++t );
    for( i = 1; i <= Q; i++ ) {
      int t, u, v;
      t = readint();
      u = readint();
      v = readint();
      if( u > v ) swap( u, v );
      if( t == 0 ) update( 1, 1, N, u, v );
      else if( t == 1 ) printf("%lld\n", query( 1, 1, N, u, v ) );
      if( sumit( 1, 1, N, segtree[ 1 ].pointer ) == N ) break;
    }
    for( ; i <= Q; i++ ) {
      int t, u, v;
      t = readint();
      u = readint();
      v = readint();
      if( u > v ) swap( u, v );
      if( t == 1 ) printf("%lld\n", ( ll )( v - u + 1 ) );
    }
    printf("\n");
  }
  return 0;
}
