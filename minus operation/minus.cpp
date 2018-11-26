#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

#define MAXN 100
#define MAXS 1000
#define SUM 10100
#define pb push_back

using namespace std;

int N, M;
int A[ MAXN + 1 ], hash[ 2*SUM + 10 ], cnt = 1;
bool memo[ MAXN + 1 ][ MAXN + 1 ][ 2*MAXS + 1 ], choice[ MAXN + 1 ][ MAXN + 1 ][ 2*MAXS + 1 ], computed[ MAXN + 1 ][ MAXN + 1 ][ 2*MAXS + 1 ];
vector< int > sol;

int hashit( int sum ) {
    if( !hash[ sum ] ) hash[ sum ] = cnt++;
    return hash[ sum ];
}

int dp( int i, int j, int k ) {
    bool& ret = memo[ i ][ j ][ hashit( k + SUM ) ];
    if( computed[ i ][ j ][ hashit( k + SUM ) ] ) return ret;
    if( i == j ) return ret = k == A[ i ];
    ret = 0;
    if( dp( i + 1, j, A[ i ] - k ) ) {
        ret = 1;
        choice[ i ][ j ][ hashit( k + SUM ) ] = 0;
    }
    else if( dp( i, j - 1, k + A[ j ] ) ) {
        ret = 1;
        choice[ i ][ j ][ hashit( k + SUM ) ] = 1;
    }
    computed[ i ][ j ][ hashit( k + SUM ) ] = true;
    return ret;
}

void produce( int i, int j, int k ) {
    if( i == j ) {
        return;
    }
    if( choice[ i ][ j ][ hashit( k + SUM ) ] == 0 ) {
        produce( i + 1, j, A[ i ] - k );
        sol.pb( i );
    } else {
        produce( i, j - 1, k + A[ j ] );
        sol.pb( i );
    }
}

int main() {
    int T;
    scanf("%d", &T );
    while( T-- ) {
        cnt = 1;
        memset( computed, 0, sizeof( computed ) );
        memset( hash, 0, sizeof( hash ) );
        
        scanf("%d%d", &N, &M );
        for( int i = 1; i <= N; i++ ) {
            scanf("%d", &A[ i ] );
        }
        dp( 1, N, M );
        produce( 1, N, M );
        for( int i = 0; i < sol.size(); i++ ) {
            printf("%d\n", sol[ i ] );
        }
        sol.clear();
        printf("\n");
    }
    return 0;
}
