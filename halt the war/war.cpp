#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAX  500000

using namespace std;

struct node {
	long long val;
	long long flag;
};
 
node segtree[MAX+1];
 
void unflag(int i,int l,int r)
{
	if( segtree[ i ].flag ) {
		segtree[ i ].val += (r - l + 1)*segtree[ i ].flag;
		if(l != r) {
			segtree[ 2 * i ].flag+=segtree[ i ].flag;
			segtree[ 2 *i + 1].flag+= segtree[ i ].flag;
		}
		segtree[ i ].flag = 0;
	}
}
 
void update(int n,int i,int j,int l, int r)
{
	if(l > j || r < i ) {
		unflag(n,l,r);
	}
	else if( i <= l && r <= j ) {
		segtree[ n ].flag++;
		unflag(n,l,r);
	}
	else {
		unflag(n,l,r);
		update(2*n,i,j,l,(l + r ) / 2 );
		update(2*n + 1,i, j, (l + r ) / 2 + 1, r);
		if( l != r ) {
			segtree[ n ].val = segtree[ 2*n ].val + segtree[ 2*n + 1].val;
		}
	}
}
 
long long query(int n,int i,int j,int l,int r)
{
	if( l > j || r < i ) {
		return 0;
	}
	unflag(n,l,r);
	if( i <= l && r <= j) {
		return segtree[ n ].val;
	} else {
		return query(2*n,i,j,l,( l + r ) /2 ) + query(2*n + 1,i,j, (l + r) /2 + 1, r);
	}
}

int main( void )
{
	int T,cnt = 1;	
	scanf("%d",&T);
	while( T-- ) {
		printf("Scenario #%d:\n",cnt++);
		int N,Q;
		scanf("%d%d",&N,&Q);
		for(int i = 0; i<=5*N; i++) {
			segtree[i].val = 0;
			segtree[i].flag = 0;
		}
		for(int i = 0; i < Q; i++) {
			char cmd[20];
			int u,v;
			scanf("%s%d%d",&cmd,&u,&v);
			if(!strcmp(cmd,"answer")) {
				printf("%lld\n",query(1,u,v,1,N));
			} else {
				update(1,u,v,1,N);
				printf("OK\n");
			}
		}
	}
	return 0;
}
