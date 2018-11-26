#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

int V,E,u,v,minim;
bool circle=false;

void dfs(vector<int> graph[],bool visited[],int s,int prev)
{
	if(s==prev) return;
	if(visited[s]) {
		circle=true;
		return;
	}
	visited[s]=true;
	for( int i=0; i< graph[s].size(); i++ ) 
		dfs(graph,visited,i,prev);
	prev=s;
}
		
int main(void)
{
	scanf("%d%d",&V,&E);
	vector<int> graph[V+1];
	bool visited[V+1];
	for( int i=0; i< E; i++ ) {
		scanf( "%d%d", &u, &v);
		graph[u].push_back(v);
		graph[v].push_back(u);
	}
	for(int i=0; i<V; i++)
		if(graph[i].size())
			minim=i;	
	dfs(graph,visited,minim,0);
	if(circle) printf("NO\n");
	else printf("YES\n");
	return 0;
}
