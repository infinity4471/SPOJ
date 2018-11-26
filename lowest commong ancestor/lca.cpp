#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

#define MAXN 1100

#define pb push_back

using namespace std;

int N, root, par[ MAXN + 1 ], depth[ MAXN + 1 ], P[ MAXN + 1 ][ 12 ];

vector< int > tree[ MAXN + 1 ];

void precompute() {
  for( int i = 1; i <= N; i++ ) {
    P[ i ][ 0 ] = par[ i ];
    if( !par[ i ] ) root = i;
  }
  for( int j = 1; j < 12; j++ ) {
    for( int i = 1; i <= N; i++ ) {
      P[ i ][ j ] = P[ P[ i ][ j - 1 ] ][ j - 1 ];
    }
  }
}

void dfs( int u, int d ) {
  depth[ u ] = d;
  for( int i = 0; i < tree[ u ].size(); i++ ) {
    int v = tree[ u ][ i ];
    dfs( v, d + 1 );
  }
}

int LCA( int u, int v ) {
  if( depth[ u ] < depth[ v ] ) swap( u, v );
  int lg = 0;
  while( ( 1 << lg ) <= depth[ u ] ) lg++;
  lg--;
  int d1 = depth[ u ], d2 = depth[ v ];
  for( int i = lg; i >= 0; i-- ) {
    if( d1 - ( 1 << i ) >= d2 ) {
      u = P[ u ][ i ];
      d1 -= ( 1 << i );
    }
  }
  if( u == v ) return v;
  for( int i = lg; i >= 0; i-- ) {
    if( P[ u ][ i ] && P[ u ][ i ] != P[ v ][ i ] ) {
      u = P[ u ][ i ];
      v = P[ v ][ i ];
    }
  }
  return P[ u ][ 0 ];
}

int main( void ) {
  int T;
  scanf("%d", &T );
  for( int t = 1; t <= T; t++ ) {
    int Q, chil, u, v;
    scanf("%d", &N );
    for( int i = 1; i <= N; i++ ) {
      scanf("%d", &chil );
      for( int j = 0; j < chil; j++ ) {
        scanf("%d", &v );
        tree[ i ].pb( v );
        par[ v ] = i;
      }
    }
    precompute();
    dfs( root, 0 );
    scanf("%d", &Q );
    printf("Case %d:\n", t );
    while( Q-- ) {
      scanf("%d%d", &u, &v );
      printf("%d\n", LCA( u, v ) );
    }
    memset( par, 0, sizeof( par ) );
    memset( P, 0, sizeof( P ) );
    memset( depth, 0, sizeof( depth ) );
    for( int i = 1; i <= N; i++ ) tree[ i ].clear();
  }
  return 0;
}
