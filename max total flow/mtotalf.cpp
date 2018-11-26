#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>

#define MAX_N 60
#define INF 1000000000

typedef std::pair<int,int> pii;

using namespace std;

int flow[MAX_N][MAX_N],cap[MAX_N][MAX_N];

void init()
{
	for(int i=0; i<MAX_N; i++) {
		for(int j=0; j<MAX_N; j++) {
			flow[i][j] = cap[i][j] = 0;
		}
	}
}

bool bfs(vector< pii > graph[],int p[],int s,int t)
{
	bool visited[MAX_N];
	for(int i=0; i<MAX_N; i++) {
		visited[ i ] = false;
	}
	queue< int > q;
	q.push( s );
	p[ s ] = -1;
	while( !q.empty() ) {
		int u = q.front();
		q.pop();
		visited[ u ] = true;
		for(int i=0; i<graph[u].size(); i++) {
			int k = graph[u][i].first;
			if( !visited[ k ] && cap[u][k] - flow[u][k] > 0 ) {
				q.push( k );
				p[ k ] = u;
			}
		}
	}
	return visited[ t ];
}

int ff(vector< pii > graph[],int s,int t)
{
	int p[MAX_N],maxflow = 0,cnt=1;
	while( bfs(graph,p,s,t) ) {
		//printf("iteration %d\n",cnt++);
		int increment = INF;
		//printf("found augmenting path from %d - %d:\n",s,t);
		for(int i=t;p[ i ] >= 0; i = p[ i ]) {
			//printf("%d\n",i);
			increment = min(increment,cap[p[i]][i] - flow[p[i]][i]);
		}
		for(int i=t; p[ i ] >= 0; i = p[ i ] ) {
			flow[i][p[i]] -= increment;
			flow[p[i]][i] += increment;
		}
		maxflow += increment;
	}
	return maxflow;
}

bool lowercase(char a) {
	return a>=97 && a<=122;
}

bool uppercase(char a) {
	return a>=65 && a<=90;
}

int main(void)
{
	int N,w;
	char u ,v;
	scanf("%d",&N);
	vector< pii > graph[MAX_N];
	init();
	for(int i=0; i<N; i++) {
		int k,l;
		cin >> u >> v >> w;
		if(lowercase(u) ) {
			k = u - 'a' + 26;
		}
		else if( uppercase( u ) ) {
			k = u - 'A';
		}
		if( lowercase(v) ) {
			 l = v - 'a'+26;
		}
		else if( uppercase( v ) ) {
			l = v - 'A';
		}
		if( !cap[k][l] ) {
			graph[k].push_back( make_pair( l,w ) );
			cap[k][l] = w;
		} else {
			cap[k][l] += w;
		}
		//printf("k -> %d, l -> %d\n",k,l);
	}
	printf("%d\n",ff(graph,0,25));
	return 0;
}
