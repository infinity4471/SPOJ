#include <cstdio>
#include <algorithm>
 
using namespace std;
 
struct node {
	int maxsum;
	int sum;
	int prefsum;
	int sufsum;
};
 
node* segtree;
int A[ 1000001 ];

void init(int n,int l,int r)
{
	if( l == r ) {
		segtree[ n ].sum = A[ l ];
		segtree[ n ].maxsum = A[ l ];
		segtree[ n ].prefsum = A[ l ];
		segtree[ n ].sufsum = A[ l ];
	} else {
		init( 2*n,l,( l + r ) / 2 );
		init( 2*n+1,( l + r ) / 2 + 1, r );
		segtree[ n ].sum = segtree[ 2*n ].sum + segtree[ 2*n + 1 ].sum;
		segtree[ n ].prefsum = max( segtree[ 2*n ].prefsum, segtree[ 2*n ].sum + segtree[ 2*n + 1 ].prefsum );
		segtree[ n ].sufsum = max( segtree[ 2*n + 1].sufsum, segtree[ 2*n + 1].sum + segtree[ 2*n ].sufsum );
		segtree[ n ].maxsum = max( max( segtree[ 2*n ].maxsum, segtree[ 2*n + 1].maxsum), segtree[ 2*n ].sufsum + segtree[2*n+1].prefsum );
	}
}
 
node query(int n,int l,int r,int i,int j)
{
	if( l == i && j == r ) {
		return segtree[ n ];
	}
	if( j <= ( l + r ) / 2 )  {
		return query(2*n,l,( l + r ) / 2,i, j );
	}
	if( i > ( l + r ) / 2 ) {
		return query(2*n+1,( l + r ) / 2 + 1, r ,i, j);
	}
	node left = query(2*n,l,( l + r ) / 2, i, ( l + r ) / 2 );
	node right = query(2*n+1,( l + r ) / 2 + 1,r,( l + r ) / 2 + 1,j);
	node mynode;
	mynode.sum = left.sum + right.sum;
	mynode.prefsum = max( left.prefsum, left.sum + right.prefsum );
	mynode.sufsum = max( right.sufsum, right.sum + left.sufsum );
	mynode.maxsum = max( right.maxsum, max( left.maxsum, right.prefsum + left.sufsum ) );
	return mynode;
}

void Update(int i,int l,int r,int x,int val)
{
	if( l == r && r == x ) {
		segtree[ i ].sum = val;
		segtree[ i ].prefsum = val;
		segtree[ i ].sufsum = val;
		segtree[ i ].maxsum = val;
		return;
	}
	else if( x <= ( l + r ) / 2 ) {
		Update( 2*i,l,( l + r ) / 2,x,val);
	}
	else if( x > ( l + r ) / 2) {
		Update( 2*i + 1,( l + r ) / 2 + 1,r,x,val);
	}
	segtree[ i ].sum = segtree[ 2*i ].sum + segtree[ 2*i + 1 ].sum;
	segtree[ i ].prefsum = max( segtree[ 2*i ].prefsum, segtree[ 2*i ].sum + segtree[ 2*i + 1 ].prefsum );
	segtree[ i ].sufsum = max( segtree[ 2*i + 1].sufsum, segtree[ 2*i + 1].sum + segtree[ 2*i ].sufsum );
	segtree[ i ].maxsum = max( max( segtree[ 2*i ].maxsum, segtree[ 2*i + 1].maxsum), segtree[ 2*i ].sufsum + segtree[2*i+1].prefsum );
}

int main( void )
{
	int N,Q;
	scanf("%d",&N);
	segtree = new node[4*N+1];
	for( int i = 1; i <= N; i++ ) {
		scanf("%d",&A[ i ]);
	}
	init(1,1,N);
	scanf("%d",&Q);
	for(int i = 0; i < Q; i++ ) {
		int u,v,type,x,val;
		scanf("%d",&type);
		if( type == 1 ) {
			node Query;
			scanf("%d%d",&u,&v);
			Query = query( 1, 1 , N, u , v ) ;
			printf("%d\n",Query.maxsum );
		} else {
			scanf("%d%d",&x,&val);
			Update(1,1,N,x,val);
		}
	}
	return 0;
}
