#include <cstdio>
#include <algorithm>
#include <vector>

#define BUCK 325
#define MAXN BUCK * BUCK

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

struct qq {
  pii P;
  int idx;
};

bool operator<( const qq& A, const qq& B ) {
  return A.P < B.P;
}

qq make_qq( int x, int y, int idx ) {
  qq A;
  A.P = mp( x, y );
  A.idx = idx;
  return A;
}

vector< qq > queries[ BUCK + 1 ];

int N, Q, A[ MAXN + 1 ], ans[ MAXN + 1 ], app[ MAXN + 1 ];

int main( void ) {
  freopen("test.in","rt",stdin);
  freopen("test.out1","wt",stdout);
  int u, v;
  scanf("%d%d", &N, &Q );
  for( int i = 1; i <= N; i++ ) {
    scanf("%d", &A[ i ] );
  }
  for( int i = 0; i < Q; i++ ) {
    scanf("%d%d", &u, &v );
    u++, v++;
    queries[ u / BUCK ].pb( make_qq( v, u , i + 1 ) );
  }

  int maxim = 0;
  u = 1, v = 0;
  for( int b = 0; b < BUCK; b++ ) {
    int start = b * BUCK;
    sort( queries[ b ].begin(), queries[ b ].end() );
    for( int i = 0; i < queries[ b ].size(); i++ ) {
      int prevu = u, prevv = v;
      u = queries[ b ][ i ].P.Y, v = queries[ b ][ i ].P.X;
      int id = queries[ b ][ i ].idx;
      start = max( start, u );
      int myprevv = prevv;
      while( u > prevu ) {
        app[ A[ prevu ] ]--;
        prevu++;
      }
      while( u < prevu ) {
        prevu--;
        app[ A[ prevu ] ]++;
      }
      while( v > prevv ) {
        prevv++;
        app[ A[ prevv ] ]++;
      }
      while( v < prevv ) {
        app[ A[ prevv ] ]--;
        prevv--;
      }
      int maxim = 0;
      for( int j = min( prevv, v ); j <= max( prevv, v ); j++ ) maxim = max( app[ A[ j ] ], maxim );
      for( int j = u; j <= min( v, ( b + 1 ) * BUCK ); j++ ) maxim = max( app[ A[ j ] ], maxim );
      ans[ id ] = maxim;
    }
  }
  for( int i = 1; i <= Q; i++ ) {
    printf("%d\n", ans[ i ] );
  }
  return 0;
}
