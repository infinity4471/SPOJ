#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXN 100000
#define MAXL 32

#define mp make_pair

using namespace std;

typedef long long ll;

struct node {
  int AB[ 2 ], idx;
};

node trie[ MAXL * MAXN + 1 ];
int nodecnt = 2;

int N;
ll A[ MAXN + 1 ], pows[ MAXL + 1 ], PX[ MAXN + 1 ]; // partial xor table

void precompute() {
  pows[ 0 ] = 1;
  for( int i = 1; i <= MAXL; i++ ) pows[ i ] = ( ll )2LL * (ll)pows[ i - 1 ];
}

void add( ll num, int index ) {
  int node = 1;
  for( int i = MAXL; i >= 0; i-- ) {
    int bit = ( num & pows[ i ] ) ? 1 : 0;
    if( trie[ node ].AB[ bit ] ) node = trie[ node ].AB[ bit ];
    else {
      trie[ node ].AB[ bit ] = nodecnt + 1;
      node = nodecnt + 1;
      nodecnt++;
    }
  }
  trie[ node ].idx = index;
}

int find( ll u ) {
  int node = 1;
  ll res = 0LL;
  for( int i = MAXL; i >= 0; i-- ) {
    ll val = ( ( ll )u & ( ll )pows[ i ] );
    ll bit = ( val != 0LL ) ? 1 : 0;
    if( trie[ node ].AB[ 1 - bit ] ) {
      node = trie[ node ].AB[ 1 - bit ];
      res += pows[ i ];
    }
    else if( trie[ node ].AB[ bit ] ) {
      node = trie[ node ].AB[ bit ];
    }
  }
  return trie[ node ].idx;
}

int main( void ) {
  precompute();

  int l = 0, r = 0;
  ll ans = 0;
  scanf("%d", &N );
  for( int i = 1; i <= N; i++ ) {
    scanf("%lld", &A[ i ] );
  }
  add( 0, 0 );
  for( int i = 1; i <= N; i++ ) {
    PX[ i ] = ( ll )PX[ i - 1 ] ^ ( ll )A[ i ];
    int newidx = find( PX[ i ] );
    int l1 = min( newidx, i );
    int r1 = max( newidx, i );
    ll val = PX[ r1 ] ^ PX[ l1 ];
    if( val > ans ) {
      l = l1, r = r1, ans = val;
    }
    else if( val == ans ) {
      if( mp( l1, r1 ) < mp( l, r ) ) l = l1, r = r1;
    }
    add( PX[ i ], i ); // we add the binary representation
  }
  printf("%lld\n%d %d\n", ans, l + 1, r );
  return 0;
}
