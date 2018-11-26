#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

#define MAXN 100100
#define INF 1001000
#define MOD 1000000007LLU

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef unsigned long long llu;
typedef pair< int, int > pii;

vector< pii > bucket[ INF + 1 ];

int par[ MAXN + 1 ];

int find( int u ) {
    if( u == par[ u ] ) return par[ u ];
    return par[ u ] = find( par[ u ] );
}

int main() {
    ll cost = 0;
    llu ways = 1LLU;
    int N, M, uu, vv, ww;
    scanf("%d%d", &N, &M );
    for( int i = 1; i <= N; i++ ) par[ i ] = i;
    for( int i = 1; i <= M; i++ ) {
        scanf("%d%d%d", &uu, &vv, &ww );
        bucket[ ww ].pb( mp( uu, vv ) );
    }
    for( int i = 1; i <= INF; i++ ) {
        ll w = ( ll )i;
        int cc = 0, valid = 0, diff = 0;
        map< pii, bool > M;
        for( int j = 0; j < bucket[ w ].size(); j++ ) {
            int u = bucket[ w ][ j ].X, v = bucket[ w ][ j ].Y;
            u = find( u );
            v = find( v );
            if( u != v ) {
                valid++;
                if( M.find( mp( u, v ) ) == M.end() && M.find( mp( v, u ) ) == M.end() ) {
                    M[ mp( u, v ) ] = true;
                    diff++;
                }
            }
        }
        for( int j = 0; j < bucket[ w ].size(); j++ ) {
            int u = bucket[ w ][ j ].X, v = bucket[ w ][ j ].Y;
            u = find( u );
            v = find( v );
            if( u != v ) {
                par[ v ] = u;
                cost += w;
                cc++;
            }
        }
        llu coef = 1LLU;
        if( valid == 3 ) {
            if( diff == 3 && cc == 2 ) coef = 3LLU;
            if( cc == 1 ) coef = 3LLU;
            if( cc == 2 && diff == 2 ) coef = 2LLU;
        }
        if( valid == 2 && cc == 1 ) coef = 2LLU;
        ways = ( ways * ( llu )coef ) % MOD;
    }
    printf("%lld %llu\n", cost, ways % MOD );
    return 0;
}
