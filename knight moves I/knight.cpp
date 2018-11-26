#include <cstdio>
#include <iostream>
#include <algorithm>
#include <functional>
#include <queue>

#define INF 10000000

using namespace std;

typedef pair<int,int> pii;

int dist[8][8];
bool visited[8][8];

queue<pii> q;

void init()
{
	while(!q.empty()) {
		q.pop();
	}
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			dist[i][j]=INF;
			visited[i][j]=false;
		}
	}
}

void check(int i,int j,int depth)
{
	if(i>7 || j>7 || i<0 || j<0 || visited[i][j]) {
		return;
	}
	if(dist[i][j]==INF) {
		dist[i][j]=depth+1;
	}
	visited[i][j]=true;
	pii a;
	a.first=i; a.second=j;
	q.push(a);
}

void bfs(int i,int j)
{
	dist[i][j]=0;
	pii a;
	a.first=i;
	a.second=j;
	q.push(a);
	while(!q.empty()) {
		pii b=q.front();
		q.pop();
		int x=b.first,y=b.second;
		check(x+1,y+2,dist[x][y]);
		check(x-1,y+2,dist[x][y]);
		check(x+1,y-2,dist[x][y]);
		check(x-1,y-2,dist[x][y]);
		check(x+2,y+1,dist[x][y]);
		check(x+2,y-1,dist[x][y]);
		check(x-2,y-1,dist[x][y]);
		check(x-2,y+1,dist[x][y]);
	}
}

int main(void)
{
	int N;
	scanf("%d",&N);
	for(int k=0; k<N; k++ ) {
		init();
		char a,b;
		int s,d;
		int x,y,x1,y1;
		cin >> a >> s >> b >> d;
		x=a-'a';
		x1=b-'a';
		y=s-1;
		y1=d-1;
		bfs(x,y);
		//printf("dist from %d,%d to %d,%d\n",x,y,x1,y1);
		printf("%d\n",dist[x1][y1]);
	}
	return 0;
}
