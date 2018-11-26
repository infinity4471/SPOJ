#include <cstdio>
#include <vector>
#include <list>

using namespace std;

void dfs( list< int > *G, int src, vector< bool > &vis, list< int > &T ) {
  if ( !vis[ src ] ) {
    vis[ src ] = true;
    for ( list< int >::iterator it = G[ src ].begin(); it != G[ src ].end(); ++it ) {
      dfs( G, *it, vis, T );
    }
    T.push_front( src );
  }
}

int main() {
  int i, n, k, w, src, trg, *p;
  vector< bool > vis;
  list< int > T, *G;
  list< int >::reverse_iterator rit, next;

  scanf( "%d %d", &n, &k );
  p = new int[ n ];
  G = new list< int >[ n ];
  vis.resize( n );

  for ( i = 0; i < k; ++i ) {
    scanf( "%d", &w );
    while ( w-- ) {
      scanf( "%d", &trg );
      --trg;
      G[ i ].push_back( trg );
    }
  }

  for ( i = 0; i < n; ++i ) {
    dfs( G, i, vis, T );
  }
  
  for ( rit = T.rbegin(); rit != T.rend(); ++rit ) {
    next = rit;
    ++next;

    if ( next == T.rend() ) {
      p[ *rit ] = 0;
    }
    else {
      p[ *rit ] = *next + 1;
    }
  }
  for ( i = 0; i < n; ++i ) {
    printf( "%d\n", p[ i ] );
  }

  return 0;
}
