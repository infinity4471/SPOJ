#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define INF 1000000000

using namespace std;

struct edge {
	int u,w;
};

int V,E;
long long dist[100001];

bool operator<(const edge& a,const edge& b)
{
	return a.w<b.w;
}

void initdist()
{
	for(int i=0; i<=V; i++) {
		dist[i]=INF;
	}
}

void dijkstra(vector<edge> graph[],int start)
{
	initdist();
	priority_queue<edge> q;
	q.push((edge) { start, 0 } );
	dist[start]=0;
	while( !q.empty() )
	{
		edge p=q.top();
		q.pop();
		for(int i=0; i<graph[p.u].size(); i++) {
			if(dist[graph[p.u][i].u]>dist[p.u] + graph[p.u][i].w ) {
				q.push(graph[p.u][i]);
				dist[graph[p.u][i].u]=dist[p.u] + graph[p.u][i].w;
			}
		}
	}
}

int main(void)
{
	int N;
	cin >> N;
	for(int k=0; k<N; k++) {
		int u,v,weight,u1,v1;
		cin >> V >> E >> u1 >> v1;
		vector<edge> graph[V+1];
		for(int i=0; i<E; i++) {
			cin >> u >> v >> weight;
			graph[u].push_back( ( edge) { v , weight } );
			graph[v].push_back ( ( edge ) { u, weight } );
		}
		dijkstra(graph,u1);
		if(dist[v1]!=INF) cout << dist[v1] << endl;
		else cout << "NONE" << endl;
	}
	return 0;
}
