#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstring>

#define MAXN 310
#define INF 123456789

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

vector< pii > T[ MAXN + 1 ];

int N, M, K, nodes[ MAXN + 1 ][ 2 ], cost[ MAXN + 1 ][ MAXN + 1 ], parent[ MAXN + 1 ];

int dp[ MAXN + 1 ][ MAXN + 1 ][ 2 ];

/* dp[ n, k, bit ] -> minimum cost to built the subtree rooted at n,
 * take k fruits with my parent either bit == 0 ? taken or not taken */

void clear_tree( int root, int par ) {
  parent[ root ] = par;
  for( int i = 0; i < T[ root ].size(); i++ ) {
    int u = T[ root ][ i ].X, w = T[ root ][ i ].Y;
    if( u == par ) {
      T[ root ].erase( T[ root ].begin() + i );
      i--;
    } else {
      clear_tree( u, root );
    }
  }
}

void transform_tree( int root, int par ) {
  if( !T[ root ].size() ) return;

  nodes[ root ][ 0 ] = T[ root ][ 0 ].X;
  for( int i = 0; i < T[ root ].size(); i++ ) {
    int u = T[ root ][ i ].X, w = T[ root ][ i ].Y;
    if( u == par ) continue;
    transform_tree( u, root );
    if( i + 1 < T[ root ].size() ) nodes[ u ][ 1 ] = T[ root ][ i + 1 ].X;
  }
}

int dp_val( int n, int k, int idx ) {
  if( k < 0 ) return INF;
  return dp[ n ][ k ][ idx ];
}

void run_dp( int n ) {
  if( nodes[ n ][ 0 ] ) run_dp( nodes[ n ][ 0 ] );
  if( nodes[ n ][ 1 ] ) run_dp( nodes[ n ][ 1 ] );

  int par = parent[ n ];
  for( int i = 0; i <= K; i++ ) dp[ n ][ i ][ 0 ] = dp[ n ][ i ][ 1 ] = INF;

  if( !nodes[ n ][ 0 ] && !nodes[ n ][ 1 ] ) {
    dp[ n ][ 0 ][ 0 ] = M == 2 ? cost[ par ][ n ]: 0;
    dp[ n ][ 0 ][ 1 ] = 0;
    dp[ n ][ 1 ][ 0 ] = 0;
    dp[ n ][ 1 ][ 1 ] = cost[ par ][ n ];
    return;
  }


  if( !nodes[ n ][ 1 ] ) {
    int l = nodes[ n ][ 0 ];
    for( int k = 0; k <= K; k++ ) {
      int addcost = M == 2 ? cost[ par ][ n ]: 0;
      if( par != 1 ) dp[ n ][ k ][ 0 ] = min( n == 1 ? INF: ( addcost + dp_val( l, k, 0 ) ), dp_val( l, k - 1, 1  ) );
      dp[ n ][ k ][ 1 ] = min( ( n == 1 ? INF: ( dp_val( l, k, 0 ) ) ), cost[ par ][ n ] + dp_val( l, k - 1, 1 ) );
    }
    return;
  }

  if( !nodes[ n ][ 0 ] ) {
    int r = nodes[ n ][ 1 ];
    for( int k = 0; k <= K; k++ ) {
      int addcost = M == 2 ? cost[ par ][ n ]: 0;
      if( par != 1 ) dp[ n ][ k ][ 0 ] = min( ( n == 1 ? INF: ( addcost + dp_val( r, k, 0 ) ) ), dp_val( r, k - 1, 0 ) );
      dp[ n ][ k ][ 1 ] = min( ( n == 1 ? INF: ( dp_val( r, k, 1 ) ) ), cost[ par ][ n ] + dp_val( r, k - 1, 1 ) );
    }
    return;
  }

  for( int k = 0; k <= K; k++ ) {
    dp[ n ][ k ][ 0 ] = dp[ n ][ k ][ 1 ] = INF;
    for( int n1 = 0; n1 <= k; n1++ ) {

      int l = nodes[ n ][ 0 ], r = nodes[ n ][ 1 ];
      int val1 = n1, val2 = k - n1;

      if( k > 0 ) {
        dp[ n ][ k ][ 1 ] = min( dp[ n ][ k ][ 1 ], ( cost[ n ][ par ] ) + dp_val( l, val1 - 1, 1 ) + dp_val( r, val2, 1 ) );
      }

      if( n != 1 ) dp[ n ][ k ][ 1 ] = min( dp[ n ][ k ][ 1 ], dp_val( l, val1, 0 ) + dp_val( r, val2, 1 ) );

      if( k > 0 && par != 1 ) {
        dp[ n ][ k ][ 0 ] = min( dp[ n ][ k ][ 0 ], dp_val( l, val1 - 1, 1 ) + dp_val( r, val2, 0 ) );
      }

      if( par != 1 && n != 1 ) dp[ n ][ k ][ 0 ] = min( dp[ n ][ k ][ 0 ], ( M == 2 ? cost[ n ][ par ]: 0 )
                                                    + dp_val( l, val1, 0 ) + dp_val( r, val2, 0 ) );
    }
  }
}

int main( void ) {
  for( int t = 0; t < 10; t++ ) {
    int u, v, w;
    scanf("%d%d%d", &N, &M, &K );
    for( int i = 0; i < N - 1; i++ ) {
      scanf("%d%d%d", &u, &v, &w );
      T[ u ].pb( mp( v, w ) );
      T[ v ].pb( mp( u, w ) );

      cost[ u ][ v ] = cost[ v ][ u ] = w;
    }
    clear_tree( 1, 0 );
    transform_tree( 1, 0 );
    run_dp( 1 );
    if( K > N - M + 1 ) printf("-1\n");
    else printf("%d\n", dp[ 1 ][ K ][ 0 ] );

    for( int i = 1; i <= N; i++ ) {
      T[ i ].clear();
    }
    memset( nodes, 0, sizeof( nodes ) );
    memset( parent, 0, sizeof( parent ) );
    memset( cost, 0, sizeof( cost ) );
  }
  return 0;
}
