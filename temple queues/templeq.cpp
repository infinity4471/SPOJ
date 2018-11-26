#include <cstdio>
#include <algorithm>
#include <utility>
 
#define MAXN 100100
#define INF 100000000
 
using namespace std;
 
struct node {
	int minim, maxim, flag;
};
 
typedef pair< int, int > pii;
 
node segtree[ 4*MAXN + 1 ];
 
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
 
void init( int n, int l, int r, int* A )
{
	if( l == r ) {
		segtree[ n ].minim = A[ l ];
		segtree[ n ].maxim = A[ l ];
		segtree[ n ].flag = 0;
	} else {
		init( 2*n, l, ( l + r ) / 2, A );
		init( 2*n + 1, ( l + r ) / 2 + 1, r, A );
		segtree[ n ].minim = min( segtree[ 2*n ].minim, segtree[ 2*n + 1 ].minim );
		segtree[ n ].maxim = max( segtree[ 2*n ].maxim, segtree[ 2*n + 1 ].maxim );
		segtree[ n ].flag = 0;
	}
}
 
void unflag( int n, int l, int r )
{
	if( segtree[ n ].flag ) {
		segtree[ n ].minim += segtree[ n ].flag;
		segtree[ n ].maxim += segtree[ n ].flag;
		if( l != r ) {
			segtree[ 2*n ].flag += segtree[ n ].flag;
			segtree[ 2*n + 1 ].flag += segtree[ n ].flag;
		}
		segtree[ n ].flag = 0;
	}
}
 
void update( int n, int l, int r, int i, int j, int v )
{
	if( r < i || l > j ) {
		unflag( n, l, r );
	}
	else if( i <= l && r <= j ) {
		segtree[ n ].flag += v;
		unflag( n, l, r );
	} else {
		unflag( n, l, r );
		update( 2*n, l, ( l + r ) / 2, i, j, v );
		update( 2*n + 1, ( l + r ) / 2 + 1, r, i, j, v );
		if( l != r ) {
			segtree[ n ].maxim = max( segtree[ 2*n ].maxim, segtree[ 2*n + 1 ].maxim );
			segtree[ n ].minim = min( segtree[ 2*n ].minim, segtree[ 2*n + 1 ].minim );
		}
	}
}
 
int query( int n, int l, int r, int node )
{
	unflag( n, l, r );
	if( l == r ) {
		return segtree[ n ].maxim;
	}
	else if( node <= ( l + r ) / 2 ) {
		return query( 2*n, l, ( l + r ) / 2, node );
	} else {
		return query( 2*n + 1, ( l + r ) / 2 + 1, r, node );
	}
}
 
int deter( int n, int l, int r, int X, int N )
{
	if( l == r && segtree[ n ].maxim >= X ) {
		return l;
	}
	else if( l == r && segtree[ n ].maxim < X ) {
		return l + 1;
	}
	else if( l != r ) {
		unflag( 2*n, l, ( l + r ) / 2 );
		unflag( 2*n + 1, ( l + r ) / 2 + 1, r );
		if( segtree[ 2*n ].maxim >= X ) {
			return deter( 2*n, l, ( l + r ) / 2, X, N );
		} else {
			return deter( 2*n + 1, ( l + r ) / 2 + 1, r, X, N );
		}
	}
}
 
int main( void )
{
	int N,Q;
	N = readint();
	Q = readint();
	pii AA[ N + 1 ];
	for( int i = 1; i <= N; i++ ) {
		int k;
		k = readint();
		AA[ i ] = make_pair( k, i );
	}
	int A[ N + 1 ], idxi[ N + 1 ], idxii[ N + 1 ];
	sort( AA + 1, AA + N + 1 );
	for( int i = 1; i <= N; i++ ) {
		A[ i ] = AA[ i ].first;
		idxi[ AA[ i ].second ] = i;
		idxii[ i ] = AA[ i ].second;
	}	
	int cnt = 1;
	// idxii[ u ] gives the index of the element in pos u in the original array
	// idxi[ u ] gives the position of the element with index u in the sorted array
	init( 1, 1, N, A );
	while( Q-- ) {
		int q, u;
		q = readint();
		u = readint();
		if( q == 1 ) {
			int q1,q2, q3, prev = idxi[ u ];
			q1 = query( 1, 1, N, idxi[ u ] ) + 1;
			q3 = query( 1, 1, N, idxi[ u ] + 1 );
			if( q1 == q3 + 1 ) {
				int pos = deter( 1, 1, N, q1 , N ) - 1;
				update( 1, 1, N, idxi[ u ], idxi[ u ], 1 );
				q2 = query( 1, 1, N, pos );
				update( 1, 1, N, idxi[ u ], idxi[ u ], q2 - q1 );
				update( 1, 1, N, pos, pos, q1 - q2 );
				swap( idxii[ idxi[ u ] ], idxii[ pos ] );
				idxi[ idxii[ idxi[ u ] ] ] = prev;
				idxi[ u ] = pos;
			} else {
				update( 1, 1, N, idxi[ u ], idxi[ u ], 1 );
			}
		}
		else if( q == 2 ) {
			unflag( 1, 1, N );
			int pos = deter( 1, 1, N, u, N );
			printf("%d\n", N - pos + 1 );
		}
		else if( q == 3 ) {
			unflag( 1, 1, N );
			int pos = deter( 1, 1, N, u, N );
			if( pos <= N ) {
				update( 1, 1, N, pos, N, -1 );
			}
		}
	} 
	return 0;
}
