#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <set>

#define MAXN 2100
#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

vector< pii > Q[ 2 ];
map< int, int > C;
int dp[ MAXN + 1 ], where[ MAXN + 1 ];
vector< int > A[ MAXN + 1 ];

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

void compress() {
  int cnt = 1;
  vector< int > nums;
  for( int i = 0; i < Q[ 0 ].size(); i++ ) {
    nums.pb( Q[ 0 ][ i ].X );
    nums.pb( Q[ 0 ][ i ].Y );
  }
  sort( nums.begin(), nums.end() );
  C[ nums[ 0 ] ] = cnt++;
  for( int i = 1; i < nums.size(); i++ ) {
    if( nums[ i ] == nums[ i - 1 ] ) continue;
    C[ nums[ i ] ] = cnt++;
  }
  for( int i = 0; i < Q[ 0 ].size(); i++ ) {
    Q[ 1 ].pb( mp( C[ Q[ 0 ][ i ].X ], C[ Q[ 0 ][ i ].Y ] ) );
  }
}

int main( void ) {
  int N, T, x, y;
  T = readint();
  for( int t = 1; t <= T; t++ ) {
    N = readint();
    for( int i = 0; i < N; i++ ) {
      x = readint();
      y = readint();
      Q[ 0 ].pb( mp( x, y ) );
    }
    compress();
    for( int i = 2*N + 1; i >= 0; i-- ) {
      int sum = 0;
      dp[ i ] = 0;
      for( int j = 0; j <= 2*N; j++ ) where[ j ] = 0;
      for( int j = 0; j < N; j++ ) {
        if( Q[ 1 ][ j ].X >= i ) {
          where[ Q[ 1 ][ j ].X ]++;
          where[ Q[ 1 ][ j ].Y + 1 ]--;
        }
      }
      for( int j = i; j <= 2*N; j++ ) {
        sum += where[ j ];
        dp[ i ] = max( dp[ i ], dp[ j + 1 ] + ( sum > 2 ? sum: 0 ) );
      }
    }
    printf("Case #%d: %d\n", t, dp[ 0 ] );
    C.clear();
    Q[ 0 ].clear();
    Q[ 1 ].clear();
  }
  return 0;
}
