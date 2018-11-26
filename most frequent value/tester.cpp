#include <cstdio>
#include <algorithm>
#include <ctime>

using namespace std;

int main() {
    srand( time( NULL ) );
    freopen("test.in","wt",stdout);
    int N = 100000, Q = 100000;
    printf("%d %d\n", N, Q );
    for( int i = 1; i <= N; i++ ) {
        int u = rand() % 100001;
        printf("%d ", u );
    }
    for( int i = 1; i <= Q; i++ ) {
        int u =rand() % N + 1, v = rand() % N + 1;
        if( u > v ) swap( u, v );
        printf("%d %d\n", u, v );
    }
    return 0;
}
