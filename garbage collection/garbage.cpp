#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    do {
        int ans = 0;
        scanf("%d%d", &N, &M );
        if( N == -1 && M == -1 ) break;
        if( N < M ) swap( N, M );
        if( M % 2 && N % 2 ) {
            ans = 52 + 13*N*M + 38 * N * M + 38;
        } else {
            ans = 52 + 13*N*M + 38*N*M;
        }
        printf("%d\n", ans );
    } while( true );
    return 0;
}
