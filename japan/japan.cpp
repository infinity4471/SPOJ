#include <cstdio>
#include <algorithm>

#define MAX 1004

using namespace std;

long long BIT[ MAX + 1],appy[ MAX + 1];

struct bridge {
	int x,y;
};

void init()
{
	for(int i = 0; i <= MAX; i++ ) {
		BIT[ i ] =0;
		appy[ i ] =0;
	}
}

bool cmp(bridge a,bridge b)
{
	if( a.x == b.x ) {
		return a.y > b.y;
	} else {
		return a.x > b.x;
	}
}

void add(int idx)
{
	while( idx <= MAX ) {
		BIT[ idx ]++;
		idx += (idx & -idx);
	}
}

int sum(int idx)
{
	int S = -appy[ idx ];
	while( idx > 0 ) {
		S += BIT[ idx ];
		idx -= (idx & -idx);
	}
	return S;
}

int main( void )
{
	int T;
	scanf("%d",&T);
	for(int k = 1; k<= T; k++ ) {
		init();
		int N,M,K;
		long long ans = 0,prev = 0,cnt = 0;
		scanf("%d%d%d",&N,&M,&K);
		bridge A[ K ];
		for(int i = 0; i < K; i++ ) {
			scanf("%d%d",&A[ i ].x, & A[ i ].y);
		}
		sort(A,A+K,cmp);
		for(int i = 0; i < K; i++ ) {
			add(A[ i ].y);
			appy[ A[ i ].y ]++;
			ans += sum(A[ i ].y);
		}
		printf("Test case %d: %lld\n",k,ans);
	}
	return 0;
}
