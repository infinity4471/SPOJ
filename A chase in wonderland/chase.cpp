#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

#define MAXN 2500
#define INF 123456789

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

double coef[ MAXN + 1 ];

double coef_calc( pii A, pii B ) {
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

int main() {
    int T;
    T = readint();
    while( T-- ) {
        int N, x, y, ans = 0;
        N = readint();
        pii A[ N + 1 ];
        for( int i = 1; i <= N; i++ ) {
            x = readint();
            y = readint();
            A[ i ] = mp( x, y );
        }
        for( int i = 1; i <= N; i++ ) {
            int cnt = 1, res = 0, noslope = 0;
            for( int j = i + 1; j <= N; j++ ) {
                if( A[ i ].X == A[ j ].X ) noslope++;
                else coef[ cnt++ ] = ( double )( A[ j ].Y - A[ i ].Y ) / ( double )( A[ j ].X - A[ i ].X );
            }
            sort( coef + 1, coef + cnt );
            for( int j = 1; j < cnt; j++ ) {
                if( coef[ j ] != coef[ j - 1 ] ) res = 1;
                else res++;
                ans = max( ans, res );
            }
            ans = max( ans, noslope );
        }
        printf("%d\n", ans );
    }
    return 0;
}
