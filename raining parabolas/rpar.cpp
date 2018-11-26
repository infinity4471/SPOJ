#include <cstdio>
#include <cassert>
#include <algorithm>
 
#define MAXN 100000
#define INF 10000000000
#define MOD 10007
 
using namespace std;
 
struct node {
	int sq;
	int sum;
	int a,b,c;
	int A,B,C;
	bool flag;
};
 
struct node* segtree;
 
void init( int n, int i, int j )
{
	if( i == j ) {
		segtree[ n ].sq = ( i % MOD )*( i % MOD ) % MOD;
		segtree[ n ].sum = i % MOD;
	} else {
		init( 2*n, i, ( i + j ) / 2 );
		init( 2*n + 1, ( i + j ) / 2 + 1, j );
		segtree[ n ].sum = ( segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum ) % MOD;
		segtree[ n ].sq = ( segtree[ 2*n ].sq + segtree[ 2*n + 1 ].sq ) % MOD;
	}
	segtree[ n ].a = 0;
	segtree[ n ].b = 0;
	segtree[ n ].c = 0;
	segtree[ n ].A = 0;
	segtree[ n ].B = 0;
	segtree[ n ].C = 0;
	segtree[ n ].flag = false;
}
 
void unflag( int n, int i, int j )
{
	int a = ( segtree[ n ].A % MOD );
	int b = ( segtree[ n ].B % MOD );
	int c = ( segtree[ n ].C % MOD ); 
	if( segtree[ n ].flag ) {
		segtree[ n ].a = ( segtree[ n ].a + segtree[ n ].sq*a ) % MOD;
		segtree[ n ].b = ( segtree[ n ].b + segtree[ n ].sum*b ) % MOD;
		segtree[ n ].c = ( segtree[ n ].c + ( ( j - i + 1 ) % MOD )*c ) % MOD;
		if( i != j ) {
			segtree[ 2*n ].A = ( segtree[ 2*n ].A + a ) % MOD;
			segtree[ 2*n ].B = ( segtree[ 2*n ].B + b ) % MOD;
			segtree[ 2*n ].C = ( segtree[ 2*n ].C + c ) % MOD;
			segtree[ 2*n + 1 ].A = ( segtree[ 2*n + 1 ].A + a ) % MOD;
			segtree[ 2*n + 1 ].B = ( segtree[ 2*n + 1 ].B + b ) % MOD;
			segtree[ 2*n + 1 ].C = ( segtree[ 2*n + 1 ].C + c ) % MOD;
			segtree[ 2*n ].flag = true;
			segtree[ 2*n + 1 ].flag = true;
		}
		segtree[ n ].A = 0;
		segtree[ n ].B = 0;
		segtree[ n ].C = 0;
		segtree[ n ].flag = false;
	}
}
 
void update( int n, int i, int j, int l, int r, int a, int b, int c )
{
	if( i > r || j < l ) {
		unflag( n, i, j );
		return;
	}
	else if( l <= i && j <= r ) {
		segtree[ n ].A = ( segtree[ n ].A + a ) % MOD;
		segtree[ n ].B = ( segtree[ n ].B + b ) % MOD;
		segtree[ n ].C = ( segtree[ n ].C + c ) % MOD;
		segtree[ n ].flag = true;
		unflag( n, i, j );
	} else {
		unflag( n, i, j );
		update( 2*n, i, ( i + j ) / 2, l, r, a, b, c );
		update( 2*n + 1, ( i + j ) / 2 + 1, j, l, r, a, b , c );
		if( i != j ) {
			segtree[ n ].a = ( segtree[ 2*n ].a + segtree[ 2*n + 1 ].a ) % MOD;
			segtree[ n ].b = ( segtree[ 2*n ].b + segtree[ 2*n + 1 ].b ) % MOD;
			segtree[ n ].c = ( segtree[ 2*n ].c + segtree[ 2*n + 1 ].c ) % MOD;
		}
	}
}
 
node query( int n, int i, int j, int l, int r )
{
	unflag( n, i, j );
	if( i == l && j == r ) {
		return segtree[ n ];
	}
	else if( r <= ( i + j ) / 2 ) {
		return query( 2*n, i, ( i + j ) / 2, l, r );
	}
	else if( l > ( i + j ) / 2 ) {
		return query( 2*n + 1, ( i + j ) / 2 + 1, j, l , r );
	} else {
		node A = query( 2*n, i, ( i + j ) / 2, l, ( i + j ) / 2 );
		node B = query( 2*n + 1, ( i + j ) / 2 + 1, j, ( i + j ) / 2 + 1, r );
		return ( node ) { ( A.sq + B.sq ) % MOD, ( A.sum + B.sum ) % MOD, ( A.a + B.a ) % MOD, 
				( A.b + B.b ) % MOD, ( A.c + B.c ) % MOD, ( A.A + B.A ) % MOD, ( A.B + B.B ) % MOD, 
				( A.C + B.C ) % MOD, A.flag || B.flag };
	}
}
 
int main( void )
{
	int N,Q;
	scanf("%d%d", &N, &Q );
	segtree = new node[ 4*N ];
	init( 1, 0, N - 1 );
	for( int i = 0; i < Q; i++ ) {
		int q;
		scanf("%d", &q);
		if( q == 0 ) {
			int u,v;
			int a,b,c;
			scanf("%d%d%d%d%d", &u, &v, &a, &b, &c );
			update( 1, 0, N - 1, u, v, a, b, c );
		} else {
			int u,v;	
			scanf("%d%d", &u, &v );
			node qq = query( 1, 0, N - 1, u, v );
			printf("%d\n", ( qq.a + qq.b + qq.c ) % MOD );
		}
	}
	delete [] segtree;
	return 0;
}
