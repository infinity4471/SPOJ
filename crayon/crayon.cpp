#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

#define MAXN 2101010

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

struct query {
    int type, u, v;
};

int BIT[ MAXN + 1 ][ 2 ]; // 0 for start, 1 for end

void add1( int u, int val, int idx ) {
    while( u <= MAXN ) {
        BIT[ u ][ idx ] += val;
        u += ( u & -u );
    }
}

void add2( int u, int val, int idx ) {
    while( u > 0 ) {
        BIT[ u ][ idx ] += val;
        u -= ( u & -u );
    }
}

int get1( int u, int idx ) {
    int S = 0;
    while( u > 0 ) {
        S += BIT[ u ][ idx ];
        u -= ( u & -u );
    }
    return S;
}

int get2( int u, int idx ) {
  int S = 0;
  while( u <= MAXN ) {
    S += BIT[ u ][ idx ];
    u += ( u & -u );
  }
  return S;
}

inline query make_query( int type, int u, int v ) {
    return ( query ) { type, u, v };
}

vector< query > Q;
map< int, int > M;
vector< pii > seg;
set< int > S;

int main() {
    int N, i = 0;
    scanf("%d", &N );

    for( i = 0; i < N; i++ ) {
        char c;
        int u = 0, v = 0, type;
        scanf("\n%c", &c );
        if( c == 'Q' ) {
            scanf("%d%d", &u, &v );
            type = 0;
        }
        else if( c == 'D' ) {
            scanf("%d%d", &u, &v );
            type = 1;
        } else {
            scanf("%d", &u );
            type = 2;
        }
        if( type != 2 ) {
          S.insert( u );
          S.insert( v );
        }
        if( c == 'D' ) seg.pb( mp( u, v ) );
        Q.pb( make_query( type, u, v ) );
    }

    i = 2;
    for( set< int >::iterator it = S.begin(); it != S.end(); ++it ) M[ *it ] = i++;

    for( i = 0; i < seg.size(); i++ ) {
        seg[ i ].X = M[ seg[ i ].X ];
        seg[ i ].Y = M[ seg[ i ].Y ];
    }
    int num = 0;
    for( i = 0; i < N; i++ ) {
        if( Q[ i ].type != 2 ) {
          Q[ i ].u = M[ Q[ i ].u ];
          Q[ i ].v = M[ Q[ i ].v ];
        }
        int uu = Q[ i ].u;
        int vv = Q[ i ].v;
        if( Q[ i ].type == 2 ) {
		        num--;
            int x = seg[ uu - 1 ].X;
            int y = seg[ uu - 1 ].Y;
            add2( x, -1, 0 );
            add1( y, -1, 1 );
        }
        else if( Q[ i ].type == 1 ) {
		        num++;
            add2( uu, 1, 0 );
            add1( vv, 1, 1 );
        } else {
            int val = num - get2( vv + 1, 0 ) - get1( uu - 1, 1 );
            printf("%d\n", val );
        }
    }
    return 0;
}
