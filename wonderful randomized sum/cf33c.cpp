#include <cstdio>
#include <algorithm>

#define MAXN 100100

using namespace std;

int A[ MAXN + 1 ], sum[ MAXN + 1 ];

int main() {
    int T;
    scanf("%d", &T );
    while( T-- ) {
        int N, ans = 0, maxim = 0;
        scanf("%d", &N );
        for( int i = 1; i <= N; i++ ) {
            scanf("%d", &A[ i ] );
            sum[ i ] = sum[ i - 1 ] + A[ i ];
        }
        ans = -sum[ N ];
        for( int i = 1; i <= N; i++ ) {
            ans = max( ans, max( maxim + sum[ i ] - sum[ N ], 2*maxim + 2*sum[ i ] - sum[ N ] ) );
            maxim = max( maxim, -sum[ i ] );
        }
        printf("%d\n", ans );
    }
    return 0;
}
