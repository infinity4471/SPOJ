#include <cstdio>
#include <queue>
#include <vector>

#define MAXN 1001000

using namespace std;

int dist[ MAXN + 1 ], par[ MAXN + 1 ], visited[ MAXN + 1 ];

vector< int > G[ MAXN + 1 ];

void bfs( int source ) {
  queue< int > Q;
  Q.push( source );
  visited[ source ] = true;
  while( !Q.empty() ) {
    int u = Q.front();
    Q.pop();
    for( int i = 0; i < G[ u ].size(); i++ ) {
      int v = G[ u ][ i ];
      if( !visited[ v ] ) {
        visited[ v ] = true;
        dist[ v ] = dist[ u ] + 1;
        par[ v ] = u;
      }
    }
  }
}

int main( void ) {
  return 0;
}
