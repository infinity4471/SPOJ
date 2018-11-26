#include <cstdio>
#include <algorithm>
#include <cstring>

#define AB 260
#define MAXN 10100

#define pb push_back

using namespace std;

int APP[ AB + 1 ], cnt[ AB + 1 ];
int* pos[ AB + 1 ];
char S[ MAXN + 1 ], S2[ MAXN + 1 ];

int find_pos( int prev_pos, char c ) {
    int lo = 0, hi = APP[ c ] - 1, ans = MAXN;
    while( lo <= hi ) {
        int mid = ( lo + hi ) / 2;
        if( pos[ c ][ mid ] <= prev_pos ) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
            ans = mid;
        }
    }
    return ans;
}

int main() {
    int T;
    scanf("%d", &T );
    while( T-- ) {
        int n, q;
        scanf("%d%s", &q, S );
        n = strlen( S );
        for( int i = 0; i < n; i++ ) {
            APP[ S[ i ] ]++;
        }
        for( int i = 'A'; i <= 'Z'; i++ ) pos[ i ] = new int[ APP[ i ] + 10 ];
        for( int i = 0; i < n; i++ ) {
            pos[ S[ i ] ][ cnt[ S[ i ] ]++ ] = i;
        }
        for( int i = 'A'; i <= 'Z'; i++ ) {
            sort( pos[ i ], pos[ i ] + APP[ i ] );
        }
        while( q-- ) {
            int prev = -1;
            bool status = true;
            scanf("%s", S2 );
            int nn = strlen( S2 );
            for( int i = 0; i < nn; i++ ) {
                int mynum = 0;
                while( S2[ i ] >= '0' && S2[ i ] <= '9' ) {
                    mynum = 10*mynum + ( S2[ i ] - '0' );
                    i++;
                }
                int posi = find_pos( prev, S2[ i ] );
                if( posi + mynum > APP[ S2[ i ] ] ) {
                    status = false;
                    break;
                } else {
                    prev = pos[ S2[ i ] ][ posi + mynum - 1 ];
                }
            }
            printf("%s\n", status ? "YES": "NO" );
        }
        for( int i = 'A'; i <= 'Z'; i++ ) {
            APP[ i ] = 0;
            cnt[ i ] = 0;
            delete [] pos[ i ];
        }
        printf("\n");
    }
    return 0;
}
