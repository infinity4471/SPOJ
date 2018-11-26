#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXN 100100

#define pb push_back

using namespace std;

typedef long long llu;

struct node {
    llu minim, sum, flag;
};

llu salary[ MAXN + 1 ];
int parent[ MAXN + 1 ], linear[ MAXN + 1 ], b[ MAXN + 1 ], e[ MAXN + 1 ], size = 0;
vector< int > T[ MAXN + 1 ];

node segtree[ 4*MAXN + 1 ];

void dfs( int u )
{
    linear[ ++size ] = u;
    b[ u ] = size;
    for( int i = 0; i < ( int )T[ u ].size(); i++ ) {
        int v = T[ u ][ i ];
        if( v == parent[ u ] ) continue;
        dfs( v );
    }
    e[ u ] = size;
}

void init( int n, int l, int r )
{
    segtree[ n ].flag = ( llu )0;
    if( l == r ) {
        segtree[ n ].minim = segtree[ n ].sum = ( llu )salary[ linear[ l ] ];
    } else {
        int mid = ( l + r ) / 2;
        init( 2*n, l, mid );
        init( 2*n + 1, mid + 1, r );
        segtree[ n ].minim = min( segtree[ 2*n ].minim, segtree[ 2*n + 1 ].minim );
        segtree[ n ].sum = ( llu )( segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum );
    }
}

void unflag( int n, int l, int r )
{
    if( segtree[ n ].flag ) {
        segtree[ n ].sum = ( llu )( segtree[ n ].sum + ( llu )( r - l + 1 ) * ( llu )segtree[ n ].flag );
        segtree[ n ].minim = ( llu )( segtree[ n ].minim + segtree[ n ].flag );
        if( l != r ) {
            segtree[ 2*n ].flag = ( llu )( segtree[ 2*n ].flag + segtree[ n ].flag );
            segtree[ 2*n + 1 ].flag = ( llu )( segtree[ 2*n + 1 ].flag + segtree[ n ].flag );
        }
        segtree[ n ].flag = ( llu )0;           
    }
}

void update( int n, int l, int r, int i, int j, llu val )
{
    if( r < i || l > j ) {
        unflag( n, l, r );
    }
    else if( i <= l && r <= j ) {
        segtree[ n ].flag = ( llu )( segtree[ n ].flag + val );
        unflag( n, l, r );
    } else {
        int mid = ( l + r ) / 2;
        unflag( n, l, r );
        update( 2*n, l, mid, i, j, val );
        update( 2*n + 1, mid + 1, r, i, j, val );
        if( l != r ) {
            segtree[ n ].sum = ( llu )( segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum );
            segtree[ n ].minim = ( llu )min( segtree[ 2*n ].minim, segtree[ 2*n + 1 ].minim );
        }
    }
}

node query( int n, int l, int r, int i, int j )
{
    unflag( n, l, r );
    int mid = ( l + r ) / 2;
    if( l == i && r == j ) return segtree[ n ];
    else if( j <= mid ) return query( 2*n, l, mid, i, j );
    else if( i > mid ) return query( 2*n + 1, mid + 1, r, i, j );
    else {
        node A = query( 2*n, l, mid, i, mid );
        node B = query( 2*n + 1, mid + 1, r, mid + 1, j );
        node C;
        C.sum = ( llu )( A.sum + B.sum );
        C.minim = ( llu )min( A.minim, B.minim );
        return C;
    }
}

int main( void )
{
	int numcase;
	scanf("%d", &numcase );
	for( int z = 1; z <= numcase; z++ ) {
		int N, Q, u, v;
        llu s;
		scanf("%d%d", &N, &Q );
        
        size = 0;
        for( int i = 0; i <= N; i++ ) {
            T[ i ].clear();
            salary[ i ] = parent[ i ] = 0;
            b[ i ] = e[ i ] = 0;
        }

		for( int i = 1; i <= N; i++ ) {
			scanf("%d%llu", &u, &s );
            parent[ i ] = u;
            salary[ i ] = s;
            T[ u ].pb( i );
		}
        
        printf("Case %d:\n", z );
        dfs( 1 );
        init( 1, 1, N );

        while( Q-- ) {
            scanf("%d%d", &u, &v );
            node A = query( 1, 1, N, b[ v ], e[ v ] );
            if( u == 1 ) {
                printf("%llu\n", A.sum );
            } else {
                update( 1, 1, N, b[ v ], e[ v ], min( ( llu )1000, A.minim ) );
            }
        }
	    
    }
	return 0;
}
