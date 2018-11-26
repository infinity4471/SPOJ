#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

#define MAXN 1001000
#define INF 12345678901567LL

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair< ll, int > pii;

int N, ncomp = 0, par[ MAXN + 1 ], next[ MAXN + 1 ], mycycle[ MAXN + 1 ], visited[ MAXN + 1 ], mycomp[ MAXN + 1 ], parweight[ MAXN + 1 ];
ll diameter[ MAXN + 1 ], root_dist[ MAXN + 1 ], maxdiam[ MAXN + 1 ];
int start, end;

vector< pii > G[ MAXN + 1 ];
vector< int > cycle[ MAXN + 1 ];

void dfs( int u, int p, int w ) {
  int cnt = 0;
  visited[ u ] = 1;
  par[ u ] = p;
  parweight[ u ] = w;
  mycomp[ u ] = ncomp;
  for( int i = 0; i < G[ u ].size(); i++ ) {
    int v = G[ u ][ i ].Y;
    if( v == par[ u ] && !cnt ) {
      cnt++;
      continue;
    }
    if( !visited[ v ] ) dfs( v, u, G[ u ][ i ].X );
    else if( visited[ v ] == 1 ) {
      end = v;
      start = u;
      next[ end ] = G[ u ][ i ].X;
    }
  }
  visited[ u ] = 2;
}

pii find_diam( int node, int root, int val ) {
  queue< pii > q;
  q.push( mp( 0LL, node ) );
  pii maxim;
  maxim = mp( 0LL, node );
  visited[ node ] = val;
  while( !q.empty() ) {
    pii A = q.front();
    q.pop();
    maxim = max( maxim, A );
    for( int i = 0; i < G[ A.Y ].size(); i++ ) {
      ll d = A.X;
      ll w = G[ A.Y ][ i ].X;
      int v = G[ A.Y ][ i ].Y;
      if(  ( !mycycle[ v ] || root == v ) && visited[ v ] != val ) {
        visited[ v ] = val;
        q.push( mp( d + w, v ) );
      }
    }
  }
  return maxim;
}

ll find_path( int comp ) {
  ll total = 0LL, maxpath = 0LL, minval = INF, maxval = 0LL, prefw = 0LL;
  for( int i = 0; i < cycle[ comp ].size(); i++ ) {
    int node = cycle[ comp ][ i ];
    int node2 = cycle[ comp ][ ( i + 1 ) % cycle[ comp ].size() ];
    total += next[ node ];
  }
  for( int i = 0; i < cycle[ comp ].size(); i++ ) {
    int node = cycle[ comp ][ i % cycle[ comp ].size() ];
    maxpath = max( maxpath, root_dist[ node ] + total -(  prefw + minval ) );
    maxpath = max( maxpath, root_dist[ node ] + prefw + maxval );
    maxval = max( maxval, root_dist[ node ] - prefw );
    minval = min( minval, -root_dist[ node ] - prefw );
    prefw += next[ node ];
  }
  return maxpath;
}

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

int main( void ) {
  int u;
  ll v;
  N = readint();
  for( int i = 0; i < N; i++ ) {
    u = readint();
    v = readint();
    G[ i + 1 ].pb( mp( v, u ) );
    G[ u ].pb( mp( v, i + 1 ) );
    int n1 = i + 1, n2 = u;
  }
  for( int i = 1; i <= N; i++ ) {
    if( !visited[ i ] ) {
      start = end = 0;
      ncomp++;
      dfs( i, -1, 0 );
      for( int j = start;; j = par[ j ] ) {
        mycycle[ j ] = ncomp;
        cycle[ ncomp ].pb( j );
        if( j == end ) break;
        next[ j ] = parweight[ j ];
      }
    }
  }

  for( int cc = 1; cc <= ncomp; cc++ ) {
    for( int i = 0; i < cycle[ cc ].size(); i++ ) {
      int node = cycle[ cc ][ i ];
      pii A = find_diam( node, node, 1 );
      root_dist[ node ] = A.X;
      diameter[ node ] = find_diam( A.Y, node, 0 ).X;
      maxdiam[ cc ] = max( ( ll )maxdiam[ cc ], ( ll )diameter[ node ] );
    }
  }

  ll ans = 0LL;
  for( int cc = 1; cc <= ncomp; cc++ ) ans += max( maxdiam[ cc ], find_path( cc ) );
  printf("%lld\n", ans );
  return 0;
}
