#include <cstdio>
#include <set>
#include <list>
#include <algorithm>
 
using namespace std;
 
const int INF  = 987654321;
 
void dijkstra( list< pair< int, short > > *G, int *w, short src ) 
{
	pair< int, short > e;
	set< pair< int, short > > s;
	list< pair< int, short > >::iterator it;
	w[ src ] = 0;
	s.insert( make_pair( w[ src ], src ) );
	while ( !s.empty() ) {
		e = *s.begin();
		s.erase( s.begin() );
		for ( it = G[ e.second ].begin(); it != G[ e.second ].end(); ++it ) {
			if ( w[ it->second ] > e.first + it->first ) {
				if ( w[ it->second ] != 987654321 ) {
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
	list< pair< int , short >  >* graph , *trans;
	int *distA , *distB ,w,M,ans=INF;
	short T,N,k,s,t,u,v;
	distA = new int[10000];
	distB = new int[10000];
	graph = new list< pair < int , short > >[10000];
	trans = new list< pair< int,short > >[10000];
	scanf("%hd",&T);
	while( T-- ) {
		scanf("%hd%d%hd%hd%hd",&N,&M,&k,&s,&t);
		s--; t--;
		for(int i=0; i<N; i++) {
			graph[ i ].clear();
			trans[ i ].clear();
			distA[ i ] = distB[ i ] = INF;
		}
		while( M-- ) {
			scanf("%hd%hd%d",&u,&v,&w);
			u--; v--;
			graph[u].push_back( make_pair(w,v) );
			trans[v].push_back( make_pair(w,u) );
		}
		dijkstra(graph,distA,s);
		dijkstra(trans,distB,t);
		ans=distA[t];
		while( k-- ) {
			scanf("%hd%hd%d",&u,&v,&w);
			u--; v--;
			ans=min(ans,min(distA[u]+w+distB[v],distB[u]+w+distA[v]));
		}
		if(ans==INF) {
			printf("-1\n");
		} else {
			printf("%d\n",ans);
		}
	}
	return 0;
}
