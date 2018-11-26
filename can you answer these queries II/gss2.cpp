#include <cstdio>
#include <algorithm>
#include <vector>

#define OFFSET 100007
#define MAXN 201000
#define INF 123456789012345LL

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;
typedef long long ll;

struct node {
  ll maxelem, maxim, flag, maxflag;
  int isup;
};

node segtree[ 4*MAXN + 1 ];

int N, Q, A[ MAXN + 1 ], prev[ MAXN + 1 ];

ll ans[ MAXN + 1 ];

vector< pii > line[ MAXN + 1 ];

void init() {
  for( int i = 1; i <= 4*MAXN; i++ ) segtree[ i ].maxim = -INF;
}

void unflag( int n, int l, int r ) {
  if( segtree[ n ].isup ) {
    segtree[ n ].maxim = max( segtree[ n ].maxelem + segtree[ n ].maxflag, segtree[ n ].maxim );
    segtree[ n ].maxelem += segtree[ n ].flag;
    if( l != r ) {
      segtree[ 2*n ].maxflag = max( segtree[ 2*n ].maxflag, segtree[ 2*n ].flag + segtree[ n ].maxflag );
      segtree[ 2*n ].flag += segtree[ n ].flag;
      segtree[ 2*n + 1 ].maxflag = max( segtree[ 2*n + 1 ].maxflag, segtree[ 2*n + 1 ].flag + segtree[ n ].maxflag );
      segtree[ 2*n + 1 ].flag += segtree[ n ].flag;
      segtree[ 2*n ].isup = segtree[ 2*n + 1 ].isup = true;
    }
    segtree[ n ].flag = segtree[ n ].maxflag = 0LL;
    segtree[ n ].isup = 0;
  }
}

void update( int n, int l, int r, int i, int j, ll val ) {
  if ( r < i || l > j ) unflag( n, l, r );
  else if( i <= l && r <= j ) {
    segtree[ n ].flag += val;
    segtree[ n ].isup = true;
    segtree[ n ].maxflag = max( segtree[ n ].flag, segtree[ n ].maxflag );
    unflag( n, l, r );
  } else {
    int mid = ( l + r ) >> 1;
    unflag( n, l, r );
    update( 2*n, l, mid, i, j, val );
    update( 2*n + 1, mid + 1, r, i, j, val );
    if( l != r ) {
      segtree[ n ].maxelem = max( segtree[ 2*n ].maxelem, segtree[ 2*n + 1 ].maxelem );
      segtree[ n ].maxim = max( segtree[ 2*n ].maxim, segtree[ 2*n + 1 ].maxim );
    }
  }
}

ll query( int n, int l, int r, int i, int j ) {
  int mid = ( l + r ) >> 1;
  unflag( n, l, r );
  if( r < i || l > j ) return -INF;
  else if( i <= l && r <= j ) return segtree[ n ].maxim;
  else return max( query( 2*n, l, mid, i, j ), query( 2*n + 1, mid + 1, r, i, j ) );
}

int main( void ) {
  int u, v;
  scanf("%d", &N );
  for( int i = 1; i <= N; i++ ) {
    scanf("%d", &A[ i ] );
  }
  scanf("%d", &Q );
  for( int i = 1; i <= Q; i++ ) {
    scanf("%d%d", &u, &v );
    line[ v ].pb( mp( u, i ) );
  }
  init();
  for( int i = 1; i <= N; i++ ) {
    update( 1, 1, N, prev[ A[ i ] + OFFSET ] + 1, i, ( ll )A[ i ] );
    for( int j = 0; j < line[ i ].size(); j++ ) {
      int other = line[ i ][ j ].X, idx = line[ i ][ j ].Y;
      ans[ idx ] = query( 1, 1, N, other, i );
    }
    prev[ A[ i ] + OFFSET ] = i;
  }
  for( int i = 1; i <= Q; i++ ) {
    printf("%lld\n", ans[ i ] );
  }
  return 0;
}
