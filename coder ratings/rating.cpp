#include <cstdio>
#include <algorithm> 

const int INF = 100000;
int BIT[ INF + 1 ];

struct coder {
	int x,y,id;
};

void init()
{
	for(int i = 0; i <= INF; i++ ) {
		BIT[ i ] = 0;
	}
}

void add(int idx)
{
	while( idx <= INF ) {
		BIT[ idx ]++;
		idx += ( idx & -idx );
	}
}

int sum(int idx)
{
	int S = 0;
	while( idx > 0 ) {
		S += BIT[ idx ];
		idx -= (idx & -idx);
	}
	return S-1;
}

bool cmp(coder a, coder b)
{
	if( a.x == b.x ) {
		return a.y < b.y;
	} else {
		return a.x < b.x;
	}
}

int main( void )
{
	int N;
	scanf("%d",&N);
	int pos[ N ];
	coder A[ N ];
	for(int i = 0; i < N; i++ ) {
		scanf("%d%d",&A[ i ].x,&A[ i ].y);
		A[ i ].id = i;
	}
	std::sort(A,A+N,cmp);
	for(int i = 0; i < N; i++ ) {
		add(A[ i ].y);
		if( A[ i ].x == A[ i - 1 ].x && A[ i ].y == A[ i - 1].y) {
			pos[ A[ i ].id ] = pos [ A[ i - 1].id ];
		} else {
			pos[ A[ i ].id ] = sum(A[ i ].y);
		}
	}
	for(int i = 0; i < N; i++ ) {
		printf("%d\n",pos[ i ]);
	}
	return 0;
}
