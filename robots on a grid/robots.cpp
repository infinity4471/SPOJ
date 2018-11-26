#include <iostream>
#include <cstdio>
#include <algorithm>
#include <functional>
#include <queue>

#define MAX 2147483647LL

using namespace std;

typedef pair<int ,int > pii;

bool visited[2001][2001];
bool grid[2001][2001];
int N;

queue< pii > q;

void check(int x,int y)
{
	if(x<0 || y<0 || visited[x][y] || !grid[x][y] || x>=N || y>=N) {
		return;
	}
	pii a;
	a.first=x;
	a.second=y;
	q.push(a);
	visited[x][y]=true;
}

void init()
{
	for(int i=0; i<=N; i++) {
		for(int j=0; j<=N; j++) {
			visited[i][j]=false;
		}
	}
}

void bfs(int x,int y)
{
	pii a;
	a.first=x;
	a.second=y;
	q.push(a);
	while( !q.empty() ) {
		pii b=q.front();
		q.pop();
		int k=b.first;
		int l=b.second;
		visited[k][l]=true;
		check(k+1,l);
		check(k-1,l);
		check(k,l+1);
		check(k,l-1);
	}
}

int main(void)
{	
	char d;
	scanf("%d",&N);
	long long dp[N][N];
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			cin >> d;
			if(d=='.') {
				grid[i][j]=true;
			} 
			else if(d=='#') {
				grid[i][j]=false;
			}
		}
	}
	for(int i=0; i<N; i++) {
		dp[i][0]=0;
		dp[0][i]=0;
	}
	for(int i=0; i<N; i++) {
		if(!grid[0][i]) {
			break;
		}
		dp[0][i]=1;
	}
	for(int i=0;i<N; i++) {
		if(!grid[i][0]) {
			break;
		}
		dp[i][0]=1;
	}
	for(int i=1; i<N; i++) {
		for(int j=1; j<N; j++) {
			dp[i][j]=0;
			if(!grid[i][j]) {
				continue;
			}
			if(grid[i-1][j]) {
				dp[i][j] += dp[i-1][j] % MAX;
			}
			if(grid[i][j-1]) {
				dp[i][j] += dp[i][j-1] % MAX;
			}
			dp[i][j]=dp[i][j] % MAX;
		}
	}
	if(dp[N-1][N-1]==0) {
		init();
		bfs(0,0);
		if(!visited[N-1][N-1]) {
			printf("INCONCEIVABLE\n");
		} else {
			printf("THE GAME IS A LIE\n");
		}
	} else {
		printf("%lld\n",dp[N-1][N-1] % MAX);
	}
	return 0;
}
