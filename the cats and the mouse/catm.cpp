#include <queue>
#include <cstdio>
#include <algorithm>
#include <functional>

#define MAX 100

using namespace std;

typedef pair<int,int> pii;

int dist[3][MAX+1][MAX+1];
bool visited[MAX+1][MAX+1];
queue<pii> q;
int N,M;

void init()
{
	while( !q.empty() ) {
		q.pop();
	}
	for(int k=0; k<3; k++) {
		for(int i=1; i<=N; i++) {
			for(int j=1; j<=M; j++) {
				dist[k][i][j]=0;
			}
		}
	}
}

void check(int i,int j,int depth,int idx)
{
	if(i>N || j>M || i<=0 || j<=0 || visited[i][j]) {
		return;
	}
	pii a;
	a.first = i;
	a.second = j;
	q.push( a );
	visited[i][j]=true;
	dist[idx][i][j]=depth;
}

void bfs(int l,int m,int idx)
{
	pii a;
	a.first = l;
	a.second = m;
	q.push( a );
	dist[idx][l][m]=0;
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=M; j++) {
			visited[i][j]=false;
		}
	}
	while( !q.empty() ) {
		pii a=q.front();
		q.pop();
		int x=a.first,y=a.second;
		check(x+1,y,dist[idx][x][y] + 1,idx);
		check(x-1,y,dist[idx][x][y] + 1,idx);
		check(x,y+1,dist[idx][x][y] + 1,idx);
		check(x,y-1,dist[idx][x][y] + 1,idx);
	}
}

int main(void)
{
	int T;
	scanf("%d%d%d",&N,&M,&T);
	while( T-- ) {
		bool status=false;
		int x,y,x1,y1,x2,y2;
		scanf("%d%d%d%d%d%d",&x,&y,&x1,&y1,&x2,&y2);
		init();
		bfs(x,y,0);
		bfs(x1,y1,1);
		bfs(x2,y2,2);
		for(int i=1; i<=N; i++) {
			if(dist[0][i][1] < dist[1][i][1] && dist[0][i][1] < dist[2][i][1] ) {
				status=true;
			}
			if(dist[0][i][M] < dist[1][i][M] && dist[0][i][M] < dist[2][i][M] ) {
				status=true;
			}
		}
		for(int i=1; i<=M; i++) {
			if(dist[0][1][i] < dist[1][1][i] && dist[0][1][i] < dist[2][1][i] ) {
                                status=true;
                        }
                        if(dist[0][N][i] < dist[1][N][i] && dist[0][N][i] < dist[2][N][i] ) {
                                status=true;
                        }
                }
		if( status ) {
			printf("YES\n");
		} else printf("NO\n");
	}
	return 0;
}
