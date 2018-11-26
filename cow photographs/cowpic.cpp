#include <cstdio>
#include <algorithm>

#define MAXN 100100
#define INF 1234567890123456LL

using namespace std;

typedef long long ll;

int A[ MAXN + 1 ], pos[ MAXN + 1 ], BIT[ MAXN + 1 ];

void add( int u )
{
    while( u <= MAXN ) {
        BIT[ u ]++;
        u += ( u & -u );
    }
}

int get( int u )
{
    int ans = 0;
    while( u > 0 ) {
        ans += BIT[ u ];
        u -= ( u & -u );
    }
    return ans;
}

int main() {
    int N;
    ll inv = 0, ans = INF;
    scanf("%d", &N );
    for( int i = 1; i <= N; i++ ) {
        scanf("%d", &A[ i ] );
        pos[ A[ i ] ] = i;
        inv += ( ll )get( A[ i ] );
        add( A[ i ] );
    }
    inv = ( ( ll )N * ( ll )( N - 1 ) / 2 ) - inv;
    for( int i = 1; i <= N; i++ ) {
        inv += ( ll )( N + 1 - 2*pos[ i ] );
        ans = min( ans, inv );
    }
    printf("%lld\n", ans );
    return 0;
}
