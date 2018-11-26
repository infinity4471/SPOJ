#include <cstdio>
#include <algorithm>
#include <vector>
#include <stack>
#include <cassert>

#define pb push_back
#define MAXN 10100

using namespace std;

vector< int > T[ MAXN + 1 ], groups[ MAXN + 1 ];

int dp[ MAXN + 1 ][ 2 ], head[ MAXN + 1 ], visited[ MAXN + 1 ], next[ MAXN + 1 ][ 2 ][ 2 ], type[ MAXN + 1 ], cnt = 1;

void dfs( int u, int p )
{
    int sum1 = 0, chil = 0, inter1 = 0, inter2 = 0, node = 0;
    visited[ u ] = true;
    dp[ u ][ 0 ] = dp[ u ][ 1 ] = MAXN;
    for( int i = 0; i < ( int )T[ u ].size(); ++i ) {
        int v = T[ u ][ i ];
        if( v == p ) continue;
        dfs( v, u );
        chil++;
        sum1 += min( dp[ v ][ 0 ], dp[ v ][ 1 ] );
    }
    dp[ u ][ 0 ] = sum1 + 1;
    //printf("sum1 for node %d -> %d\n", u, sum1 );
    for( int i = 0; i < ( int )T[ u ].size(); i++ ) {
        int v = T[ u ][ i ], val1, val2;
        if( v == p ) continue;
        val1 = sum1 - min( dp[ v ][ 0 ], dp[ v ][ 1 ] ) + dp[ v ][ 0 ];
        if( val1 < dp[ u ][ 0 ] ) {
            node = v;
            dp[ u ][ 0 ] = val1;
        }
        for( int j = i + 1; j < ( int )T[ u ].size(); j++ ) {
            int vv = T[ u ][ j ];
            if( vv == p ) continue;
            val2 = sum1 - min( dp[ v ][ 0 ], dp[ v ][ 1 ] ) - min( dp[ vv ][ 0 ], dp[ vv ][ 1 ] ) + dp[ v ][ 0 ] + dp[ vv ][ 0 ] - 1;
            if( val2 < dp[ u ][ 1 ] ) {
                dp[ u ][ 1 ] = val2;
                inter1 = v;
                inter2 = vv;
            }
        }
    }
    if( !chil ) {
        dp[ u ][ 0 ] = 1;
        dp[ u ][ 1 ] = MAXN;
    }
    next[ u ][ 0 ][ 0 ] = node;
    next[ u ][ 1 ][ 0 ] = inter1;
    next[ u ][ 1 ][ 1 ] = inter2;
    if( dp[ u ][ 0 ] <= dp[ u ][ 1 ] ) {
        //printf("for node %d i continue the chain with node %d!\n", u, node );
        type[ u ] = 1;
        type[ node ] = 1;
        for( int i = 0; i < ( int )T[ u ].size(); i++ ) {
            int v = T[ u ][ i ];
            if( v == p || v == node ) continue;
            head[ cnt++ ] = v;
        }
    }
    else if( dp[ u ][ 0 ] > dp[ u ][ 1 ] ) {
        //printf("for node %d i break to %d and %d\n", u, inter1, inter2 );
        type[ u ] = 2;
        type[ inter1 ] = 1;
        type[ inter1 ] = 1;
        for( int i = 0; i < ( int )T[ u ].size(); i++ ) {
            int v = T[ u ][ i ];
            if( v == p || v == inter1 || v == inter2 ) continue;
            head[ cnt++ ] = v;
        }
    }
    //printf("type[ %d ] = %d\n", u, type[ u ] );
    //printf("dp[ %d ][ 0 ] = %d, dp[ %d ][ 1 ] = %d\n", u, dp[ u ][ 0 ], u, dp[ u ][ 1 ] );
}

void type1( int group )
{
    int node = head[ group ];
    groups[ group ].pb( node );
    while( next[ node ][ 0 ][ 0 ] ) {
        node = next[ node ][ 0 ][ 0 ];
        groups[ group ].pb( node );
    }
}

void type2( int group )
{
    int node = head[ group ];
    stack< int > path;
    path.push( node );
    if( next[ node ][ 1 ][ 0 ] ) path.push( next[ node ][ 1 ][ 0 ] );
    node = next[ node ][ 0 ][ 0 ];
    while( next[ node ][ 0 ][ 0 ] ) {
        node = next[ node ][ 0 ][ 0 ];
        path.push( node );
    }
    while( !path.empty() ) {
        groups[ group ].pb( path.top() );
        path.pop();
    }
    node = next[ head[ group ] ][ 1 ][ 1 ];
    while( next[ node ][ 0 ][ 0 ] ) {
        groups[ group ].pb( node );
        node = next[ node ][ 0 ][ 0 ];
    }
    groups[ group ].pb( node );
}

int main() {
    int numcase;
    scanf("%d", &numcase );
    while( numcase-- ) {
        int N, u, v, ans = 0;
        scanf("%d", &N );

        cnt = 1;
        for( int i = 1; i <= N; i++ ) {
            T[ i ].clear();
            groups[ i ].clear();
            type[ i ] = 0;
            next[ i ][ 0 ][ 0 ] = next[ i ][ 0 ][ 1 ] = next[ i ][ 1 ][ 0 ] = next[ i ][ 1 ][ 1 ] = 0;
            head[ i ] = 0;
            visited[ i ] = false;
        }
        for( int i = 1; i < N; i++ ) {
            scanf("%d%d", &u, &v );
            T[ u ].pb( v );
            T[ v ].pb( u );
        }
        for( int i = 1; i <= N; i++ ) {
            if( !visited[ i ] ) {
                head[ cnt++ ] = i;
                dfs( i, -1 );
                ans += min( dp[ i ][ 0 ], dp[ i ][ 1 ] );
            }
        }
        for( int i = 1; i < cnt; i++ ) {
            //printf("head[ %d ] = %d\n", i, head[ i ] );
            int node = head[ i ];
            if( type[ node ] == 1 ) type1( i );
            else type2( i );
        }
        assert( ans == cnt - 1 );
        printf("%d\n", ans );
        for( int i = 1; i <= ans; i++ ) {
            for( int j = 0; j < ( int )groups[ i ].size(); j++ ) {
                int node = groups[ i ][ j ];
                printf("%d", node );
                if( j != ( int )groups[ i ].size() - 1 ) printf(" ");
            }
            printf("\n");
        }
    }
    return 0;
}
