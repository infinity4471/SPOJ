#include <cstdio>
#include <algorithm>

#define MAXN 300010
#define mp make_pair

using namespace std;

struct node {
	int* A, elem, times;
};

struct qq {
	int elem, times;
};

int AA[ MAXN + 1 ];
node segtree[ 3*MAXN + 1 ];

int range( int* arr, int beg, int end, int elem )
{
	int lo = beg, hi = end, idx1 = 0, idx2 = 0;
	while( lo <= hi ) {
		int mid = ( lo + hi ) / 2;
		if( arr[ mid ] < elem ) {
			idx1 = mid;
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}
	lo = beg, hi = end;
	while( lo <= hi ) {
		int mid = ( lo + hi ) / 2;
		if( arr[ mid ] <= elem ) {
			idx2 = mid;
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}
	return idx2 - idx1;
}

void init( int n, int l, int r )
{
	segtree[ n ].A = new int[ r - l + 1 ];
	if( l == r ) {
		segtree[ n ].A[ 1 ] = AA[ l ];
		segtree[ n ].times = 1;
		segtree[ n ].elem = AA[ l ];
	} else {
		int mid = ( l + r ) / 2, myelem = -1, mytimes = 0, len = r - l + 1, i, j, k;
		init( 2*n, l, mid );
		init( 2*n + 1, mid + 1, r );
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
		if( segtree[ 2*n ].elem != -1 ) {
			int rang = range( segtree[ 2*n + 1 ].A, 1, r - mid, segtree[ 2*n ].elem );
			int total = rang + segtree[ 2*n ].times;
			if( total > len / 2 ) {
				mytimes = total;
				myelem = segtree[ 2*n ].elem;
			}
		}
		if( segtree[ 2*n + 1 ].elem != -1 ) {
			int rang = range( segtree[ 2*n ].A, 1, mid - l + 1, segtree[ 2*n + 1 ].elem );
			int total = rang + segtree[ 2*n + 1 ].times;
			if( total > len / 2 ) {
				if( total > mytimes ) {
					mytimes = total;
					myelem = segtree[ 2*n + 1 ].elem;
				}
			}
		}
		segtree[ n ].elem = myelem;
		segtree[ n ].times = mytimes;
	}
}

int count_seg( int n, int l, int r, int i, int j, int k )
{
	if( r < i || l > j ) {
		return 0;
	}
	else if( i <= l && r <= j ) {
		return range( segtree[ n ].A, 1, r - l + 1, k );
	} else {
		return count_seg( 2*n, l, ( l + r ) / 2, i, j, k ) + count_seg( 2*n + 1, ( l + r ) / 2 + 1, r, i, j, k );
	}
}

qq query( int n, int l, int r, int i, int j )
{
	if( r < i || l > j ) {
		qq A;
		A.elem = -1;
		A.times = 0;
		return A;
	}
	else if( i <= l && r <= j ) {
		qq A;
		A.elem = segtree[ n ].elem;
		A.times = segtree[ n ].times;
		return A;
	} else {
		int mid = ( l + r ) / 2, mytimes = 0, myelem = -1;
		qq A = query( 2*n, l, mid, i, j );
		qq B = query( 2*n + 1, mid + 1, r, i, j );
		qq C;
		if( A.elem != -1 ) {
			int total = A.times;
			if(  max( i, mid + 1 ) <= min( j, r ) ) {
				total += count_seg( n, l, r, max( i, mid + 1 ), min( j, r ), A.elem );
			}
			mytimes = total;
			myelem = A.elem;
		}
		if( B.elem != -1 ) {
			int total = B.times;
			if( max( l, i ) <= min( j, mid ) ) {
				total += count_seg( n, l, r, max( l, i ), min( j, mid ), B.elem );
			}
			if( mytimes < total ) {
				mytimes = total;
				myelem = B.elem;
			}
		}
		C.elem = myelem;
		C.times = mytimes;
		int len = min( j, r ) - max( l, i ) + 1;
		if( 2*C.times <= len ) {
			C.elem = -1;
			C.times = 0;
		}
		return C;
	}
}

int main( void )
{
	int N,C, Q;
	scanf("%d%d", &N, &C );
	for( int i = 1; i <= N; i++ ) {
		scanf("%d", &AA[ i ] );
	}
	init( 1, 1, N );
	scanf("%d", &Q );
	for( int i = 1; i <= Q; i++ ) {
		int u,v;
		scanf("%d%d", &u, &v );
		qq q = query( 1, 1, N, u, v );
		if( 2*q.times > v - u + 1 ) {
			printf("yes %d\n", q.elem );
		} else {
			printf("no\n");
		}
	}
	return 0;
}
