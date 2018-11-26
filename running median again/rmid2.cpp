#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>

#define MAXN 101000

using namespace std;

int A[ MAXN + 1 ], B[ MAXN + 1 ];
int BIT[ MAXN + 1 ];
map< int, int > M, R;

void add( int x, int val ) {
    while( x <= MAXN ) {
        BIT[ x ] += val;
        x += ( x & -x );
    }
}

int get( int x ) {
    int S = 0;
    while( x > 0 ) {
        S += BIT[ x ];
        x -= ( x & -x );
    }
    return S;
}

int median( int S ) {
    int lo = 1, hi = MAXN, ans = 0;
    if( S % 2 ) S = ( S + 1 ) / 2;
    else S /= 2;
    //printf("looking for %d\n", S );
    while( lo <= hi ) {
        int mid = ( lo + hi ) / 2;
        //printf("mid -> %d, get( %d ) = %d\n", mid, mid, get( mid ) );
        if( get( mid ) < S ) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
            ans = mid;
        }
    }
    return ans;
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
    int t;
    scanf("%d", &t );
    while( t-- ) {
        int x, n = 0, cnt = 1, size = 0;
        do {
           scanf("%d", &x );
           if( x == 0 ) break;
           A[ ++n ] = x;
           B[ n ] = x;
        } while( true );
        sort( A + 1, A + n + 1 );
        for( int i = 1; i <= n; i++ ) {
            if( A[ i ] != -1 && !M[ A[ i ] ] ) {
                M[ A[ i ] ] = cnt;
                R[ cnt ] = A[ i ];
                cnt++;
            }
        }
        for( int i = 1; i <= n; i++ ) {
            if( B[ i ] != -1 ) {
                size++;
                add( M[ B[ i ] ], 1 );
            } else {
                int med = median( size );
                printf("%d\n", R[ med ] );
                add( med, -1 );
                size--;
            }
        }
        memset( BIT, 0, sizeof( BIT ) );
        M.clear();
        R.clear();
    }
    return 0;
}
