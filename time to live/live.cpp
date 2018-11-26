#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

void bfs(vector<int> graph[],int N,int dist[],int start)
{
	queue<int> q;
	q.push(start);
	bool visited[N];
	for(int i=0; i<N; i++) {
		visited[i]=dist[i]=0;
	}
	dist[start]=0;
	while( !q.empty() ) {
		int p=q.front();
		q.pop();
		visited[p]=true;
		for(int i=0; i<graph[p].size(); i++) {
			if(!visited[graph[p][i]]) {
				dist[graph[p][i]]=dist[p]+1;
				q.push(graph[p][i]);
			}
		}
	}
}

int main(void)
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		int N;
		scanf("%d",&N);
		int u,v,max=0;
		vector<int> graph[N];
		int dist[N];
		for(int i=0; i<N-1; i++) {
			scanf("%d%d",&u,&v);
			graph[u].push_back(v);
			graph[v].push_back(u);
		}
		bfs(graph,N,dist,0); 
		for(int i=0; i<N; i++) {
			if(dist[max]<dist[i]) {
				max=i;
			}
		}
		bfs(graph,N,dist,max);
		max=0;
		for(int i=0; i<N; i++) {
			if(dist[i]>max) {
				max=dist[i];
			}
		}
		printf("%d\n", ( max / 2 ) + max % 2 );
	}
	return 0;
}
