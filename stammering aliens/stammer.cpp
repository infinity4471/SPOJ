#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>

#define MAXN 50000
#define MOD 1000000007LL
#define AB 256

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef long long ll;
typedef pair< ll, int > pii;

int n, len;
char S[ MAXN + 1 ];

int find( int sz ) {
    vector< pii > V;
    ll hash = 0, power = 1;
    for( int i = 0; i < sz; i++ ) {
        hash = ( ( hash * AB % MOD ) + S[ i ] ) % MOD;
    }
    for( int i = 0; i < sz - 1; i++ ) {
        power = power * AB % MOD;
    }
    V.pb( mp( hash, 0 ) );
    for( int i = sz; i < len; i++ ) {
        hash = ( hash - ( S[ i - sz ] * power % MOD ) ) % MOD;
        hash = hash * AB  % MOD;
        hash = ( hash + S[ i ] ) % MOD;
        if( hash < 0 ) hash = hash + MOD;
        V.pb( mp( hash, i - sz + 1 ) );
    }
    sort( V.begin(), V.end() );
    int app = 1, right = -1;
    if( n == 1 ) right = 0;
    for( int i = 0; i < V.size() - 1; i++ ) {
        if( V[ i ].X == V[ i + 1 ].X ) app++;
        if( V[ i ].X != V[ i + 1 ].X ) app = 1;
        if( app >= n ) right = max( right, V[ i + 1 ].Y );
    }
    return right;
}

int main() {
    do {
        scanf("%d", &n );
        if( !n ) break;
        scanf("%s", S );
        len = strlen( S );
        int lo = 1, hi = len, ans = 0, idx = 0;
        while( lo <= hi ) {
            int mid = ( lo + hi ) / 2;
            int ss = find( mid );
            if( ss != -1 ) {
                lo = mid + 1;
                ans = mid;
                idx = ss;
            } else {
                hi = mid - 1;
            }
        }
        if( ans == 0 ) {
            printf("none\n");
        } else {
            printf("%d %d\n", ans, idx );
        }
    } while( true );
    return 0;
}
