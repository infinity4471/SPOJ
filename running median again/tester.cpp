#include <cstdio>
#include <algorithm>
#include <ctime>

#define MAXN 100100

using namespace std;

int A[ MAXN + 1 ];

int main() {
    freopen("test.in","wt",stdout);
    srand( time( NULL ) );
    int t = rand() % 10;
    while( t-- ) {
        int n = rand() % 100000;
        for( int i = 0; i < n; i++ ) {
            A[ i ] = rand() % 10000000;
        }
        sort( A, A + n );
        for( int i = 0; i < n; i++ ) {
            if( ( i + 1 ) % 5 == 0 ) {
                printf("-1\n");
            }
            printf("%d\n", A[ i ] );
        }
        printf("0\n");
    }
    return 0;
}
