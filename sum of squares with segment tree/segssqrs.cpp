#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

struct node {
	long long sum,ssum;
	int flag1,flag2;
	bool up1,up2;
};

node* segtree;

void init( int i , int l , int r,int* A )
{
	if( l == r ) {
		segtree[ i ].sum = A[ l ];
		segtree[ i ].ssum = A[ l ] * A[ l ];
	} else {
		init( 2*i, l, ( l + r ) / 2, A );
		init( 2*i + 1, ( l + r ) / 2 + 1, r, A );
		segtree[ i ].sum = segtree[ 2*i ].sum + segtree[ 2*i + 1 ].sum;
		segtree[ i ].ssum = segtree[ 2*i ].ssum + segtree[ 2*i + 1 ].ssum;
	}
	segtree[ i ].flag1 = 0;
	segtree[ i ].flag2 = 0;
	segtree[ i ].up1 = false;
	segtree[ i ].up2 = false;
}

bool refresh2( int i, int l, int r )
{
	if( segtree[ i ].up2 ) {
		segtree[ i ].flag1 = 0;
		segtree[ i ].up1 = false;
                segtree[ i ].ssum = ( r - l + 1 )*pow( segtree[ i ].flag2, 2 );
                segtree[ i ].sum = ( r - l + 1 ) * segtree[ i ].flag2;
		if( l != r ) {
			segtree[ 2*i ].flag2 = segtree[ i ].flag2;
			segtree[ 2*i ].up2 = true;
			segtree[ 2*i + 1 ].flag2 = segtree[ i ].flag2;
			segtree[ 2*i + 1 ].up2 = true;
			segtree[ 2*i ].flag1 = segtree[ 2*i ].up1 = 0;
			segtree[ 2*i + 1 ].flag1 = segtree[ 2*i + 1 ].up1 = 0;
		}
		segtree[ i ].up2 = false;
		return true;
	}
	return false;
}

void refresh1( int i, int l,int r )
{
	if( segtree[ i ].up1 ) {
		segtree[ i ].ssum += 2*segtree[ i ].flag1*segtree[ i ].sum + pow( segtree[ i ].flag1, 2 )*( r - l + 1 );
		segtree[ i ].sum +=  ( r - l + 1 ) * segtree[ i ].flag1;
		if( l != r ) {
			segtree[ 2*i ].flag1 += segtree[ i ].flag1;
			segtree[ 2*i + 1 ].flag1 += segtree[ i ].flag1;
			segtree[ 2*i ].up1 = true;
			segtree[ 2*i + 1 ].up1 = true;
		}
		segtree[ i ].flag1 = 0;
		segtree[ i ].up1 = false;
	}
}

void update2( int n, int l, int r, int i,int j, int k ) // set everything to k
{
	if( r < i || l > j ) {
		refresh2( n, l, r );
	}
	else if( i <= l && r <= j ) {
		segtree[ n ].flag2 = k;
		segtree[ n ].up2 = true;
		refresh2( n, l, r );
	} else {
		refresh2( n, l, r );
		update2( 2*n, l, ( l + r ) / 2, i, j , k );
		update2 ( 2*n + 1, ( l + r ) / 2 + 1, r, i, j , k );
		if( l != r ) {
			segtree[ n ].sum = segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum;
			segtree[ n ].ssum = segtree[ 2*n ].ssum + segtree[ 2*n + 1 ].ssum;
		}
	}
}

void update1( int n, int l, int r, int i, int j, int k ) // increment by k
{
	if( r < i || l > j ) {
		refresh1( n, l, r );
	}
	else if( i <= l && r <= j ) {
		refresh2( n, l, r );
		segtree[ n ].flag1 += k;
		segtree[ n ].up1 = true;
		refresh1( n, l , r );
	} else {
		refresh1( n, l, r );
		update1( 2*n, l , ( l + r ) / 2, i, j , k );
		update1( 2*n + 1, ( l + r ) / 2 + 1,r , i, j , k );
		if( l != r ) {
			segtree[ n ].sum = segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum;
                        segtree[ n ].ssum = segtree[ 2*n ].ssum + segtree[ 2*n + 1 ].ssum;
                }
	}
}

long long query( int n, int l, int r, int i, int j )
{
	if( r < i || l > j ) {
		return 0;
	}
	refresh1( n , l, r );
	if( i <= l && r <= j ) {
		return segtree[ n ].ssum;
	} else {
		return query( 2*n, l, ( l + r ) / 2, i, j ) + query( 2*n + 1 , ( l + r ) / 2 + 1, r, i , j );
	}
}

int main( void )
{
	int T;
	scanf("%d",&T);
	for( int z = 1; z <= T; z++ ) {
		int N,Q,*A,i,j,k,l;
		scanf("%d%d",&N,&Q);
		segtree = new node[ 5*N ];
		A = new int[ N + 1 ];
		for( int i = 1; i <= N; i++ ) {
			scanf("%d",A + i );
		}
		init( 1, 1, N, A );
		printf("Case %d:\n",z);
		while( Q-- ) {
			scanf("%d",&i);
			if( i == 0 ) {
				scanf("%d%d%d",&j,&k,&l);
				update2( 1, 1, N, j, k, l );
			}
			else if( i == 1 ) {
				scanf("%d%d%d",&j,&k,&l);
				update1( 1, 1, N, j, k, l );
			}
			else if( i == 2 ) {
				scanf("%d%d",&j,&k);
				printf("%lld\n",query(1, 1, N,j , k ) );
			}
		}
	}
	return 0;
}
