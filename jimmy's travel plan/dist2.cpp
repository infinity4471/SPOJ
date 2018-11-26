#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

#define MAXN 201000

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

map< pii, int > E[ 3 ];
vector< int > G[ MAXN + 1 ];

int main() {
    int T;
    scanf("%d", &T );
    for( int t = 1; t <= T; t++ ) {
        int N, M, u, v;
        scanf("%d%d", &N, &M );
        for( int i = 1; i <= N; i++ ) {
            E[ 1 ][ mp( i, i ) ] = 1;
        }
        for( int i = 1; i <= M; i++ ) {
            scanf("%d%d", &u, &v );
            if( E[ 1 ].find( mp( u, v ) ) == E[ 1 ].end() ) {
                G[ u ].pb( v );
                G[ v ].pb( u );
            }
            E[ 1 ][ mp( u, v ) ]++;
            E[ 1 ][ mp( v, u ) ]++;
        }
        
        for( int i = 1; i <= N; i++ ) {
            for( int j = 0; j < G[ i ].size(); j++ ) {
                for( int k = j + 1; k < G[ i ].size(); k++ ) {
                    u = G[ i ][ j ], v = G[ i ][ k ];
                    E[ 2 ][ mp( u, v ) ] += E[ 1 ][ mp( u, i ) ] * E[ 1 ][ mp( i, v ) ];
                    E[ 2 ][ mp( v, u ) ] += E[ 1 ][ mp( u, i ) ] * E[ 1 ][ mp( i, v ) ];
                }
            }
        }

        printf("Case #%d:\n", t );
        int Q;
        scanf("%d", &Q );
        while( Q-- ) {
            scanf("%d%d", &u, &v );
            if( E[ 1 ].find( mp( u, v ) ) != E[ 1 ].end() ) {
                if( u == v ) printf("0");
                else printf("1");
                printf(" %d\n", E[ 1 ][ mp( u, v ) ] );
            }
            else if( E[ 2 ].find( mp( u, v ) ) != E[ 2 ].end() ) {
                printf("2 %d\n", E[ 2 ][ mp( u, v ) ] );
            } else {
                printf("The pair of cities are not connected or too far away.\n");
            }
        }
        for( int i = 1; i <= N; i++ ) {
            G[ i ].clear();
        }
        E[ 1 ].clear();
        E[ 2 ].clear();
    }
    return 0;
}
