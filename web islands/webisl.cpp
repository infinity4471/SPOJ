#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>

#define MAXN 100100
#define pb push_back

using namespace std;

int N, M, visited[ MAXN + 1 ], compsize = 0, mycomp[ MAXN + 1 ];

vector< int > G[ MAXN + 1 ], T[ MAXN + 1 ], comp[ MAXN + 1 ];

stack< int > S;

void dfs1( int u ) {
  visited[ u ] = 1;
  for( int i = 0; i < G[ u ].size(); i++ ) {
    int v = G[ u ][ i ];
    if( visited[ v ] ) continue;
    dfs1( v );
  }
  S.push( u );
}

void dfs2( int u ) {
  visited[ u ] = 0;
  comp[ compsize ].pb( u );
  for( int i = 0; i < T[ u ].size(); i++ ) {
    int v = T[ u ][ i ];
    if( !visited[ v ] ) continue;
    dfs2( v );
  }
}

int main( void ) {
  int u, v;
  scanf("%d%d", &N, &M );
  for( int i = 0; i < M; i++ ) {
    scanf("%d%d", &u, &v );
    G[ u ].pb( v );
    T[ v ].pb( u );
  }
  for( int i = 0; i < N; i++ ) {
    if( !visited[ i ] ) dfs1( i );
  }
  while( !S.empty() ) {
    int u = S.top();
    if( visited[ u ] ) {
      dfs2( u );
      compsize++;
    }
    S.pop();
  }
  for( int i = 0; i < compsize; i++ ) {
    sort( comp[ i ].begin(), comp[ i ].end() );
    for( int j = 0; j < comp[ i ].size(); j++ ) {
      mycomp[ comp[ i ][ j ] ] = comp[ i ][ 0 ];
    }
  }
  for( int i = 0; i < N; i++ ) {
    printf("%d\n", mycomp[ i ] );
  }
  return 0;
}
