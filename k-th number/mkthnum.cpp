#include <cstdio>
#include <algorithm>

#define INF 1000000001
#define MAXN 100001

using namespace std;

struct node {
	int* A;
};

node* segtree;

void init( int n, int l, int r, int* AA )
{
	segtree[ n ].A = new int[ r - l + 1 ];
	if( l == r ) {
		segtree[ n ].A[ 1 ] = AA[ l ];
	} else {
		init( 2*n, l, ( l + r ) / 2, AA );
		init( 2*n + 1, ( l + r ) / 2 + 1, r, AA );
		int i, j, k;
		int n1 = ( l + r ) / 2 - l + 1, n2 = r - ( l + r ) / 2;
		for( i = 1, j = 1, k = 1; i <= n1 && j <= n2; k++ ) {
			if( segtree[ 2*n ].A[ i ] <= segtree[ 2*n + 1 ].A[ j ] ) {
				segtree[ n ].A[ k ] = segtree[ 2*n ].A[ i++ ];
			} else {
				segtree[ n ].A[ k ] = segtree[ 2*n + 1 ].A[ j++ ];
			}
		}
		while( i <= n1 ) {
			segtree[ n ].A[ k++ ] = segtree[ 2*n ].A[ i++ ];
		}
		while( j <= n2 ) {
			segtree[ n ].A[ k++ ] = segtree[ 2*n + 1 ].A[ j++ ];
		}
	}
}

int query( int n, int l, int r, int i, int j, int x )
{
	if( l > j || r < i ) {
		return 0;
	}
	else if( i <= l && r <= j ) {
		int lo = 1, hi = r - l + 1;
		while( lo < hi ) {
			int mid = ( lo + hi ) / 2;
			if( segtree[ n ].A[ mid ] < x ) {
				lo = mid + 1;
			} else {
				hi = mid;
			}
		}
		if( segtree[ n ].A[ lo ] > x ) {
			lo--;
		}
		return lo;
	} else {
		return query( 2*n, l, ( l + r ) / 2, i, j, x ) + query( 2*n + 1, ( l + r ) / 2 + 1, r, i, j , x );
	}
}

int main( void )
{
	int N,Q, minim = INF, maxim = 0;
	scanf("%d%d", &N, &Q );
	segtree = new node[ 4*N + 1 ];
	int A[ N + 1 ];
	for( int i = 1; i <= N; i++ ) {
		scanf("%d", &A[ i ] );
		minim = min( A[ i ], minim );
	}
	for( int i = 1; i <= N; i++ ) {
		A[ i ] += abs( minim ) + 1;
		maxim = max( A[ i ] , maxim );
	}
	init( 1, 1, N, A );
	while( Q-- ) {
		int u,v,k;
		scanf("%d%d%d", &u, &v, &k );
		long long lo = 1, hi = maxim;
		while( lo < hi ) {
			int mid = ( lo + hi ) / 2;
			int ll = query( 1, 1, N, u, v, mid );
			if( ll < k ) {
				lo = mid + 1;
			} else {
				hi = mid;
			}
		}
		printf("%d", lo - abs( minim ) - 1 );
		puts("");
	}
	delete [] segtree;
	return 0;
}
