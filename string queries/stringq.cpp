#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <set>

#define MAXN 2100
#define MOD 106109099
#define AB 256

#define X first
#define Y second
#define mp make_pair
#define pb push_back

using namespace std;

typedef pair< int, int > pii;

string S;
int fact[ MAXN + 1 ];

void calc_fact() {
    fact[ 0 ] = 1;
    for( int i = 1; i <= MAXN; i++ ) {
        fact[ i ] = i * fact[ i - 1 ] % MOD;
    }
}

int query( int u, int v ) {
    set< int > SS;
    int app[ AB + 1 ] = { 0 }, status = 0;
    for( int i = u - 1; i < v; i++ ) {
        SS.insert( S[ i ] );
        app[ S[ i ] ]++;
    }
    int len = ( v - u + 1 );
    for( set< int >::iterator it = SS.begin(); it != SS.end(); ++it ) {
        if( app[ *it ] % 2 && status ) return 0;
        else if( app[ *it ] % 2 ) status = true;
    }
    if( len % 2 == 0 && status ) return 0;
    if( len % 2 == 1 && !status ) return 0;
    if( len % 2 == 0 ) return fact[ SS.size() ];
    else return fact[ SS.size() - 1 ];
}

void update( int u, int v ) {
    vector< int > V;
    for( int i = u - 1; i < v; i++ ) V.pb( S[ i ] );
    sort( V.begin(), V.end() );
    for( int i = u - 1; i < v; i++ ) S[ i ] = V[ i - u + 1 ];
}

int main() {
    int T;
    freopen("test.in","rt",stdin);
    freopen("test.out","wt",stdout);
    calc_fact();
    scanf("%d", &T );
    while( T-- ) {
        int Q, n;
        cin >> S >> Q;
        n = S.length();
        while( Q-- ) {
            char q;
            int u, v;
            cin >> q >> u >> v;
            if( q == 'Q' ) printf("%d\n", query( u, v ) );
            else if( q == 'U' ) update( u, v );
        }
        cout << S << endl;
    }
    return 0;
}
