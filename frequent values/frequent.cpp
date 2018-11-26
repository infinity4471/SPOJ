#include <cstdio>
#include <algorithm>

#define MAXN 100005
#define INF 100005

using namespace std;

struct node {
	int freq;
	int rfreq;
	int lfreq;
};

int begin[ 2*INF + 2 ],end[ 2*INF + 2 ];

node* segtree;

void init()
{
	for( int i = 0; i <= 2*INF + 1; i++ ) {
		begin[ i ] = 0;
		end[ i ] = 0;
	}
}

void build( int i, int l, int r, int* A )
{
	if( l == r ) {
		segtree[ i ].freq = 1;
		segtree[ i ].rfreq = 1;
		segtree[ i ].lfreq = 1;
	} else {
		build( 2*i, l , ( l + r ) / 2, A );
		build( 2*i + 1, ( l + r ) / 2 + 1, r, A );
		segtree[ i ].rfreq = r - max( begin[ A[ r ] ], l ) + 1;
		segtree[ i ].lfreq = min( end[ A[ l ] ], r  ) - l + 1;
		segtree[ i ].freq = max( max( segtree[ 2*i ].freq, segtree[ 2*i + 1 ].freq ), max( segtree[ i ].rfreq, segtree[ i ].lfreq ) );
		if( A[ ( l + r ) / 2 ] == A[ ( l + r ) / 2 + 1 ] ) {
			segtree[ i ].freq = max( segtree[ i ].freq, segtree[ 2*i ].rfreq + segtree[ 2*i + 1 ].lfreq );
		}
	}
}

node query( int n, int l, int r, int i, int j,int* Ar )
{
	if( l == i && r == j ) {
		return segtree[ n ];
	}
	else if( j <= ( l + r ) / 2 ) {
		return query( 2*n, l, ( l + r ) / 2, i , j, Ar );
	}
	else if( i > ( l + r ) / 2 ) {
		return query( 2*n + 1, ( l + r ) /2 + 1, r, i, j, Ar );
	}
	node A = query( 2*n, l, ( l + r ) / 2, i , ( l + r ) / 2, Ar );
	node B = query( 2*n + 1, ( l + r ) /2 + 1, r, ( l + r ) / 2 + 1, j, Ar );
	node C;
	C.rfreq =  j - max( begin[ Ar[ j ] ], i ) + 1;
	C.lfreq = min( end[ Ar[ i ] ], j  ) - i + 1; 
	C.freq = max( max( A.freq, B.freq) , max( C.rfreq, C.lfreq ) );
	if( Ar[ ( l + r ) / 2 ] == Ar[ ( l + r ) / 2 + 1 ] ) {
		C.freq = max( C.freq, A.rfreq + B.lfreq );
	}
	return C;
}

int main( void )
{
	while( true ) {
		int M,Q,*A,i,j;
		scanf("%d",&M);
		if( !M ) {
			break;
		}
		scanf("%d",&Q);
		segtree = new node[ 4*(M + 1 ) ];
		A = new int[ M + 10 ];
		init();
		scanf("%d",A + 1 );
		A[ 1 ] += INF;
		begin[ A[ 1 ] ] = 1;
		for( int i = 2; i <= M; i++ ) {
			scanf("%d",A + i );
			A[ i ] += INF;
			if( A[ i ] != A[ i - 1 ] ) {
				begin[ A[ i ] ] = i;
				end[ A[ i - 1 ] ] = i - 1;
			}
		}
		end[ A[ M ] ] = M;
		build( 1, 1, M, A );
		for( int k = 0; k < Q; k++ ) {
			scanf("%d%d",&i,&j);
			printf("%d\n",query( 1, 1, M, i, j, A ).freq );
		}
		delete [] segtree;
		delete [] A;
	}
	return 0;
}
