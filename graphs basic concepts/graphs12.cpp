#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

int N, M;
vector< pii >* G;

int *visited, *par, *time, *low, *A, ncomp = 0, cnt = 1;
vector< int > traversals[ 2 ], *comp;

void dfs( int u, int p ) {
  int chil = 0;
  traversals[ 1 ].pb( u );
  visited[ u ] = 1;
  time[ u ] = cnt++;
  low[ u ] = time[ u ];
  comp[ ncomp ].pb( u );
  for( int i = 0; i < G[ u ].size(); i++ ) {
    int v = G[ u ][ i ].X, w = G[ u ][ i ].Y;
    if( visited[ v ] == 0 ) {
      par[ v ] = u;
      chil++;
      dfs( v, u );
      low[ u ] = min( low[ u ], low[ v ] );
      if( p != -1 && time[ u ] <= low[ v ] ) A[ u ] = true;

    }
    else if( visited[ v ] == 1 && v != p ) {
      low[ u ] = min( low[ u ], time[ v ] );
    }
  }
  if( p == -1 && chil >= 2 ) A[ u ] = true;
  visited[ u ] = 2;
}

void bfs( int s ) {
  queue< int > Q;
  Q.push( s );
  visited[ s ] = 1;
  par[ s ] = -1;
  while( !Q.empty() ) {
    int u = Q.front();
    Q.pop();
    traversals[ 0 ].pb( u );
    for( int i = 0; i < G[ u ].size(); i++ ) {
      int v = G[ u ][ i ].X;
      if( visited[ v ] ) continue;
      visited[ v ] = 1;
      Q.push( v );
      par[ v ] = u;
    }
  }
}

void printpath( int u ) {
  stack< int > S;
  while( u != -1 ) {
    S.push( u );
    u = par[ u ];
  }
  if( S.top() != 1 ) return;
  printf("%d", S.top() );
  while( !S.empty() ) {
    S.pop();
    if( !S.empty() ) printf(" %d", S.top() );
  }
  printf("\n");
}

int main( void ) {
  int d, u, v, w;
  scanf("%d%d%d", &d, &N, &M );
  printf("%d\n%d %d\n", d, N, M );
  G = new vector< pii >[ N + 1 ];
  comp = new vector< int >[ N + 1 ];
  visited = new int[ N + 1 ];
  par = new int[ N + 1 ];
  time = new int[ N + 1 ];
  low = new int[ N + 1 ];
  A = new int[ N + 1 ];

  for( int i = 1; i <= N; i++ ) {
    visited[ i ] = time[ i ] = low[ i ] = A[ i ] = 0;
  }
  for( int i = 0; i < M; i++ ) {
    scanf("%d%d%d", &u, &v, &w );
    printf("%d %d %d\n", u, v, w );
    G[ u ].pb( mp( v, w ) );
    if( d == 0 ) G[ v ].pb( mp( u, w ) );
  }
  printf("\n");
  for( int i = 1; i <= N; i++ ) {
    if( !visited[ i ] ) bfs( i );
  }
  printf("BFS:\n");
  printf("%d", traversals[ 0 ][ 0 ] );
  for( int i = 1; i < traversals[ 0 ].size(); i++ ) {
    printf(" %d", traversals[ 0 ][ i ] );
  }
  printf("\n\n");
  printf("BFS Paths:\n");
  for( int i = 1; i <= N; i++ ) {
    printpath( i );
  }
  printf("\n");

  for( int i = 1; i <= N; i++ ) {
    visited[ i ] = par[ i ] = 0;
  }
  for( int i = 1; i <= N; i++ ) {
    if( !visited[ i ] ) {
      par[ i ] = -1;
      dfs( i, -1 );
      ncomp++;
    }
  }
  printf("DFS:\n");
  printf("%d", traversals[ 1 ][ 0 ] );
  for( int i = 1; i < traversals[ 1 ].size(); i++ ) {
    printf(" %d", traversals[ 1 ][ i ] );
  }
  printf("\n\n");
  printf("DFS Paths:\n");
  for( int i = 1; i <= N; i++ ) {
    printpath( i );
  }
  printf("\n");
  printf("Connected Components:\n");
  for( int i = 0; i < ncomp; i++ ) {
    sort( comp[ i ].begin(), comp[ i ].end() ) ;
    printf("C%d:", i + 1 );
    for( int j = 0; j < comp[ i ].size(); j++ ) {
      printf(" %d", comp[ i ][ j ] );
    }
    printf("\n");
  }
  printf("\n");
  vector< int > articulation;
  for( int i = 1; i <= N; i++ ) {
    if( A[ i ] ) {
      articulation.pb( i );
    }
  }
  printf("Articulation Vertices:\n" );
  if( articulation.size() ) {
    printf("%d", articulation[ 0 ] );
    for( int i = 1; i < articulation.size(); i++ ) {
      printf(" %d", articulation[ i ] );
    }
    printf("\n");
  }
  return 0;
}
