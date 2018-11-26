#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

void bfs(vector<int> graph[],int N,int dist[],int start)
{
	set<int> st;
	st.insert(start);
	bool visited[N+1];
	for(int i=0; i<=N; i++) {
		visited[i]=dist[i]=0;
	}
	dist[start]=0;
	while( !st.empty() ) {
		int p= *st.begin();
		st.erase( st.begin() );
		visited[p]=true;
		for(int i=0; i<graph[p].size(); i++) {
			if(!visited[graph[p][i]]) {
				dist[graph[p][i]]=dist[p]+1;
				st.insert(graph[p][i]);
			}
		}
	}
}
				
int main(void)
{
	int N,u,v,max=0;
	cin >> N;
	vector<int> graph[N+1];
	int dist[N+1];
	for(int i=1; i<N; i++) {
		cin >> u >> v;
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	bfs(graph,N,dist,1); 
	for(int i=1; i<=N; i++) {
		if(dist[max]<dist[i]) {
			max=i;
		}
	}
	bfs(graph,N,dist,max);
	max=0;
	for(int i=1; i<=N; i++) {
		if(dist[i]>max) {
			max=dist[i];
		}
	}
	cout << max << endl;
	return 0;
}
