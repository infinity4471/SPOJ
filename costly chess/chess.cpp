#include <iostream>
#include <algorithm>
#include <functional>
#include <queue>
#include <map>

#define INF 100000000

using namespace std;

typedef pair<int,int> pii;

map<pii,int> dist;

bool operator<(pii a, pii b)
{
	return dist[a]<dist[b];
}

priority_queue< pii > pq;

void init()
{
	while(!pq.empty()) pq.pop();
	for(int i=0; i<8; i++) {
		for(int j=0; j<8; j++) {
			pii a;
			a.first=i;
			a.second=j;
			dist[a]=INF;
		}
	}
}

void check(int i,int j,int depth)
{
	pii a;
	a.first=i;
	a.second=j;
	//cout << "coming to check with i=" << i << " and j = " << j << endl;
	//cout << "dist of a = " << dist[a] << endl;
	if(i>7 || j>7 || i<0 || j<0 || dist[a]<=depth) return;
	else {
		//cout << "pusing a to priority queue" << endl;
		dist[a]=depth;
		pq.push(a);
	}
}

void dijkstra(pii start)
{
	pq.push(start);
	dist[start]=0;
	while(!pq.empty()) {
		pii a=pq.top();
		int i=a.first;
		int j=a.second;
		pq.pop();
		//cout << "visiting square: (" << i << "," << j << ")" << endl;
		check(i+1,j+2,dist[a]+i*(i+1)+j*(j+2));
		check(i+1,j-2,dist[a]+i*(i+1)+j*(j-2));
		check(i-1,j+2,dist[a]+i*(i-1)+j*(j+2));
		check(i-1,j-2,dist[a]+i*(i-1)+j*(j-2));
		check(i+2,j-1,dist[a]+i*(i+2)+j*(j-1));
		check(i+2,j+1,dist[a]+i*(i+2)+j*(j+1));
		check(i-2,j-1,dist[a]+i*(i-2)+j*(j-1));
		check(i-2,j+1,dist[a]+i*(i-2)+j*(j+1));
	}
}

int main(void)
{
	int a,b,c,d;
	while ( cin >> a >> b >> c >> d ) {
		pii start,end;
		start.first=a;
		start.second=b;
		end.first=c;
		end.second=d;
		init();
		dijkstra(start);
		// fuck you thunder! you can suck my dick
		if(dist[end]!=INF) cout << dist[end] << endl;
		else cout << -1 << endl;
	}
	return 0;
}
