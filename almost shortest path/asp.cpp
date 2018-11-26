#include <cstdio>
#include <vector>
#include <list>
#include <set>
#include <functional>
#include <algorithm>
 
#define INF 1000000000

using namespace std;

struct edge {
	int u,v,w;
};
 
void dijkstra( list< pair< int, int > > *G, int* w, int src ) 
{
	pair< int, int > e;
	set< pair< int, int > > s;
	list< pair< int, int > >::iterator it;
	w[ src ] = 0;
	s.insert( make_pair( 0 , src ) );
	while ( !s.empty() ) {
		e = *s.begin();
		s.erase( s.begin() );
		for ( it = G[ e.second ].begin(); it != G[ e.second ].end(); ++it ) {
			if ( w[ it->second ] > e.first + it->first ) {
				if ( w[ it->second ] != INF ) {
					s.erase( make_pair( w[ it->second ], it->second ) );
				}
				w[ it->second ] = e.first + it->first;
				s.insert( make_pair( w[ it->second ], it->second ) );
			}
		}
	}
}
 
int main(void)
{
	list< pair< int , int >  >* graph , *trans,*newr;
	vector< edge > edges;
	int *ds,*dt,w,u,v,s,t,V,E;
	graph = new list < pair<int , int > >[10000];
	trans = new list < pair<int, int > >[10000];
	newr = new list < pair < int , int > > [10000];
	ds = new int[10000];
	dt = new int[10000];
	while( true ) {
		scanf("%d%d",&V,&E);
		if( V==0 && E==0 ) {
			break;
		}
		edges.clear();
		scanf("%d%d",&s,&t);
		for(int i=0; i<V; i++) {
			graph[ i ].clear();
			trans[ i ].clear();
			newr[ i ].clear();
			ds[ i ] = INF;
			dt[ i ] = INF;
		}
		for(int i = 0; i<E; i++) { 
			edge a;
			scanf("%d%d%d",&u,&v,&w);
			a.u = u; a.v = v; a.w = w;
			edges.push_back( a );
			graph[ u ].push_back( make_pair( w,v ) );
			trans[ v ].push_back( make_pair( w,u ) );
		}
		dijkstra(graph,ds,s);
		dijkstra(trans,dt,t);
		for(int i=0; i<E; i++) {
			if( ds[edges[i].u] + edges[i].w + dt[edges[i].v] > ds[ t ] ) {
				newr[edges[i].u].push_back( make_pair( edges[i].w, edges[i].v ) );
			}
		}
		for(int i=0; i<V; i++) {
			ds[ i ] = INF;
		}
		dijkstra(newr,ds,s);
		if( ds[ t ] == INF) {
			printf("-1\n");
		} else {
			printf("%d\n",ds[ t ] );
		}
	}
	return 0;
}
