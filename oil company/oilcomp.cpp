#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXH 20
#define MAXN 17715

using namespace std;

int W, H, grid[ MAXH ][ MAXH ], memo[ MAXH + 1 ][ MAXH + 2 ][ MAXN ];

int hash[ 1 << MAXH ], cnt = 1;

int hashit( int bit ) {
    if( !hash[ bit ] ) hash[ bit ] = cnt++;
    return hash[ bit ];
}

int dp1( int n, int c, int bit ) {
    int& ret = memo[ n ][ c ][ hashit( bit ) ];
    if( ret != -1 ) return ret;
    if( n == H ) return ret = 0;
    if( c >= W ) return ret = dp1( n + 1, 0, bit );
    ret = 0;
    if( bit & ( 1 << c ) ) ret = dp1( n, c + 1, bit ^ ( 1 << c ) );
    else {
        int newbit = bit | ( 1 << c );
        if( newbit & ( 1 << ( c + 1 ) ) ) newbit ^= ( 1 << ( c + 1 ) );
        ret = max( grid[ n ][ c ] + dp1( n, c + 2, newbit ), dp1( n, c + 1, bit ) );
    }
    return ret;
}

int dp2( int n, int c, int bit ) {
    int& ret = memo[ n ][ c ][ hashit( bit ) ];
    if( ret != -1 ) return ret;
    if( c == W ) return ret = 0;
    if( n >= H ) return ret = dp2( 0, c + 1, bit );
    ret = 0;
    if( bit & ( 1 << n ) ) ret = dp2( n + 1, c, bit ^ ( 1 << n ) );
    else {
        int newbit = bit | ( 1 << n );
        if( newbit & ( 1 << ( n + 1 ) ) ) newbit ^= ( 1 << ( n + 1 ) );
        ret = max( grid[ n ][ c ] + dp2( n + 2, c, newbit ), dp2( n + 1, c, bit ) );
    }
    return ret;
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
    int T, c = 0, ans;
    T = readint();
    while( T-- ) {
        memset( memo, -1, sizeof( memo ) );
        W = readint();
        H = readint();
        for( int i = 0; i < H; i++ ) {
            for( int j = 0; j < W; j++ ) {
                grid[ i ][ j ] = readint();
            }
        }
        if( W > H ) ans = dp2( 0, 0, 0 );
        else ans = dp1( 0, 0, 0 );
        printf("Case %d: %d\n", ++c, ans );
    }
    return 0;
}
