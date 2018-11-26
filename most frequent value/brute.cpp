#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 100100

using namespace std;

int A[ MAXN + 1 ], occ[ MAXN + 1 ];

int main() {
    int N, Q, u, v;
    freopen("test.in","rt",stdin);
    freopen("test1.out","wt",stdout);
    scanf("%d%d", &N, &Q );
    for( int i = 1; i <= N; i++ ) {
        scanf("%d", &A[ i ] );
    }
    while( Q-- ) {
        int ans = 0;
        memset( occ, 0, sizeof( occ ) );
        scanf("%d%d", &u, &v );
        for( int i = u + 1; i <= v + 1; i++ ) {
            occ[ A[ i ] ]++;
            ans = max( ans, occ[ A[ i ] ] );
        }
        printf("%d\n", ans );
    }
    return 0;
}
