#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXN 1100
#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair< ll, int > pii;

ll ans = 0;

int N, choice[ MAXN + 1 ];
ll D[ MAXN + 1 ], P[ MAXN + 1 ], t;
pii cost[ MAXN + 1 ], W[ MAXN + 1 ];

int main() {
    scanf("%d%lld", &N, &t );
    for( int i = 1; i <= N; i++ ) {
        scanf("%lld", &W[ i ].X );
        W[ i ].Y = i;
    }
    for( int i = 1; i <= N; i++ ) {
        scanf("%lld", &D[ i ] );
    }
    for( int i = 1; i <= N; i++ ) {
        scanf("%lld", &P[ i ] );
        cost[ i ].X = P[ i ] - ( ll )t * D[ i ];
        cost[ i ].Y = i;
    }
    sort( cost + 1, cost + N + 1 );
    sort( W + 1, W + N + 1 );
    for( int i = 1; i <= N; i++ ) {
        ans += ( ll )cost[ i ].X * W[ i ].X;
        choice[ cost[ i ].Y ] = W[ i ].Y;
    }
    //printf("%d\n", ans );
    printf("%d", choice[ 1 ] );
    for( int i = 2; i <= N; i++ ) {
        printf(" %d", choice[ i ] );
    }
    printf("\n");
    return 0;
}
