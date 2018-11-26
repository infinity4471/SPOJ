#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

queue<int> q;

void toposort(vector<int> graph[],bool visited[],int N,int node)
{
	if(visited[node]) {
		return;
	}
	visited[node]=true;
	for(int i=0; i<graph[node].size(); i++) {
		toposort(graph,visited,N,graph[node][i]);
	}
	q.push(node);
}

void dfs(vector<int> graph[],int N)
{
	bool visited[N+1];
	for(int i=0; i<=N; i++) {
		visited[i]=false;
	}
	for(int i=1; i<=N; i++) {
		toposort(graph,visited,N,i);
	}
}

int main(void)
{
	int N,K;
	scanf("%d%d",&N,&K);
	vector<int> graph[N+1];
	for(int i=1; i<=K; i++) {
		int n;
		scanf("%d",&n);
		for(int j=0; j<n; j++) {
			int m;
			scanf("%d",&m);
			graph[i].push_back(m);
		}
	}
	dfs(graph,N);
	int topology[N+1],array[N+1];
	for(int i=1; !q.empty(); i++) {
		array[i]=q.front();
		q.pop();
	}
	for(int i=1; i<=N; i++) {
		int next=i+1;
		if(next>N) {
			topology[array[i]]=0;
		} else {
			topology[array[i]]=array[next];
		}
	}
	for(int i=1; i<=N; i++) {
		printf("%d\n",topology[i]);
	}
	return 0;
}
