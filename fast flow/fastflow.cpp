#include <cstdio>
#include <algorithm>

#define MAXN 5100
#define MAXE 30010
#define INF 1234567890

using namespace std;

int N, M;

int flow[ MAXN + 1 ][ MAXN + 1 ], cap[ MAXN + 1 ][ MAXN + 1 ], par[ MAXN + 1 ];

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

bool bfs( int s, int t ) {
  bool visited[ N + 1 ];
  for( int i = 0; i <= N; i++ ) visited[ i ] = 0;
  visited[ s ] = true;
  par[ s ] = -1;
  int queue[ N + 1 ], front = 0, rear = 1;
  queue[ front ] = s;
  while( front < rear ) {
    int u = queue[ front++ ];
    for( int v = 1; v <= N; v++ ) {
      if( cap[ u ][ v ] - flow[ u ][ v ] > 0 && !visited[ v ] ) {
        queue[ rear++ ] = v;
        par[ v ] = u;
        visited[ v ] = true;
      }
    }
  }
  return visited[ t ];
}

int maxflow( int s, int t ) {
  int ans = 0;
  while( bfs( s, t ) ) {
    int minim = INF;
    for( int u = t; par[ u ] != -1; u = par[ u ] ) {
      minim = min( minim, cap[ par[ u ] ][ u ] - flow[ par[ u ] ][ u ] );
    }
    for( int u = t; par[ u ] != -1; u = par[ u ] ) {
      flow[ par[ u ] ][ u ] += minim;
      flow[ u ][ par[ u ] ] -= minim;
    }
    ans += minim;
  }
  return ans;
}

int main( void ) {
  int u, v, w;
  N = readint();
  M = readint();
  for( int i = 0; i < M; i++ ) {
    u = readint();
    v = readint();
    w = readint();
    cap[ u ][ v ] += w;
    cap[ v ][ u ] += w;
  }
  printf("%d\n", maxflow( 1, N ) );
  return 0;
}
