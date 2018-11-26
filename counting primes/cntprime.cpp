#include <cstdio>
#include <algorithm>
#include <cctype>

#define MAX 1000000

using namespace std;

struct node {
	int primes,flag;
};

node* segtree;
bool isprime[ MAX + 1];

void sieve()
{
	for(int i = 0; i <= MAX; i++ ) {
		isprime[ i ] = true;
	}
	for(int i = 2; i <= MAX; i++ ) {
 		for(int j = 2*i; j <= MAX; j+=i) {
			isprime[ j ] = false;
		}
	}
}

void init(int i,int l,int r,int *A)
{
	if( l == r ) {
		segtree[ i ].primes = isprime[ A[ l ] ];
		segtree[ i ].flag = 0;
	} else {
		init(2*i,l,( l + r ) / 2,A);
		init(2*i + 1,( l + r ) / 2 + 1, r , A);
		segtree[ i ].primes = segtree[ 2*i ].primes + segtree[ 2*i + 1].primes;
		segtree[ i ].flag = 0;
	}
}

void unflag(int i,int l,int r)
{
	if( segtree[ i ].flag ) {
		segtree[ i ].primes = (r-l+1)*isprime[ segtree[ i ].flag ];
		if( l != r ) {
			segtree[ 2*i ].flag = segtree[ i ].flag;
			segtree[ 2*i + 1].flag = segtree[ i ].flag;
		}
		segtree[ i ].flag = 0;
	}
}

void update(int n,int l,int r,int i,int j,int val)
{
	if( r < i || l > j ) {
		unflag(n,l,r);
	}
	else if( i <= l && r <= j ) {
		segtree[ n ].flag = val;
		unflag(n,l,r);
	} else {
		unflag(n,l,r);
		update(2*n,l,( l + r ) / 2,i,j,val);
		update(2*n + 1,( l + r ) /2 + 1,r,i,j,val);
		if( l != r ) {
			segtree[ n ].primes = segtree[ 2*n ].primes + segtree[ 2*n + 1].primes;
		}
	}
}

int query(int n,int l,int r,int i,int j)
{
	if( r < i || l > j ) {
		return 0;
	}
	unflag(n,l,r);
	if( i <= l && r <= j ) {
		return segtree[ n ].primes;
	} else {
		return query(2*n,l,(l + r) /2,i,j) + query(2*n+1,( l + r ) / 2 + 1,r,i,j);
	}
}

int main( void )
{
	int T;
	scanf("%d",&T);
	sieve();
	for(int k = 1; k <= T; k++ ) {
		int n,m;
		scanf("%d%d",&n,&m);
		int b, e, op,A[ n + 1];
		segtree = new node[4*n+1];
		for(int i = 1; i <= n; i++ ) {
			scanf("%d",&A[ i ]);
		}
		init(1, 1, n,A);
		printf("Case %d:\n",k);
		for(int i = 0; i < m; ++i){
			scanf("%d%d%d",&op,&b,&e);
			if(op == 1){
				printf("%d\n",query(1,1,n,b,e));
			} else {
				int v;
				scanf("%d",&v);
				update(1,1,n,b,e,v);
			}
		}
		puts("");
	}
	return 0;
}
