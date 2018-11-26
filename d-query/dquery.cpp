#include <cstdio>
#include <algorithm>
#include <map>

#define MAX1 30000
#define MAX2 200000

using namespace std;

struct req {
	int i,j,idx,val;
	bool t;
};

int BIT[ MAX1 + 1 ];

bool cmp( req a, req b )
{
	if( a.j == b.j ) {
		return a.t < b.t;
	} return a.j < b.j;
}

void add(int idx)
{
	while( idx <= MAX1 ) {
		BIT[ idx ]++;
		idx += ( idx & -idx );
	}
}

void rem(int idx)
{
	while( idx <= MAX1 ) {
		BIT[ idx ]--;
		idx += ( idx & -idx );
	}
}

int sum(int i,int j)
{
	int sum1=0,sum2=0;
	while( j > 0 ) {
		sum1 += BIT[ j ];
		j -= ( j & -j );
	}
	i--;
	while( i > 0 ) {
		sum2 += BIT[ i ];
		i -= ( i & -i );
	}
	return sum1 - sum2;
}

int main( void )
{
	int N,Q;
	req requests[ MAX1 + MAX2 + 1];
	scanf("%d",&N);
	map< int,int > pos;
	for(int k = 0; k < N; k++ ) {
		scanf("%d",&requests[ k ].val);
		requests[ k ].idx = k+1;
		requests[ k ].j = k + 1;
		requests[ k ].t = 0;
	}
	scanf("%d",&Q);	
	int ans[ Q ];
	for(int k = N; k < N+ Q; k++ ) {
		scanf("%d%d",&requests[ k].i,&requests[ k ].j);
		requests[ k ].idx = k-N;
		requests[ k ].t = 1;
	}
	sort(requests,requests+Q+N,cmp);
	for(int k = 0; k < N+Q; k++ ) {
		if( requests[ k ].t == 0 ) {
			if( pos[ requests[ k ].val ] ) {
				rem( pos[ requests[ k ].val ] );
			}
			add(requests[ k ].idx);
			pos[ requests[ k ].val ] = requests[ k ].idx;
		} else {
			ans[ requests[ k ].idx ] = sum(requests[ k ].i,requests[ k ].j );
		}
	}
	for(int i = 0; i < Q; i++ ) {
		printf("%d\n",ans[ i ]);
	}
	return 0;
}
