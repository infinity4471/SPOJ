#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 210

using namespace std;

int N, memo[ MAXN + 1 ][ MAXN + 1 ], A[ MAXN + 1 ];

int dp( int pos, int black, int white )
{
    int& sol = memo[ black ][ white ];
    if( sol != -1 ) return sol;
    if( pos == N + 1 ) return sol = 0;

    sol = dp( pos + 1, black, white );
    if( !black || A[ pos ] > A[ black ] ) sol = max( sol, 1 + dp( pos + 1, pos, white ) );
    if( !white || A[ pos ] < A[ white ] ) sol = max( sol, 1 + dp( pos + 1, black, pos ) );
    return sol;
}

int main() {
    do {
        scanf("%d", &N );
        if( N == -1 ) break;
        
        memset( memo, -1, sizeof( memo ) );
        for( int i = 1; i <= N; i++ ) {
            scanf("%d", &A[ i ] );
        }
    
        printf("%d\n", N - dp( 1, 0, 0 ) );
    } while( true );
    return 0;
}
