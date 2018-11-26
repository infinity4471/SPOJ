#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>

const long double INF = 1000000.0;

using namespace std;

struct edge {
	int v;
	long double weight;
};

edge make_edge(int u,long double w )
{
	edge ed;
	ed. v = u;
	ed.weight = w;
	return ed;
}

bool belford(vector< edge > graph[],int N)
{
	long double dist[ N + 1 ];
	for( int i = 1; i <= N; i++ ) {
		dist[ i ] = INF;
	}
	dist[ 1 ] = 0.0;
	for( int e = 0; e <= N; e++ ) {
    for( int i = 1; i <= N; i++ ) {
      for( int j = 0; j < graph[ i ].size(); j++ ) {
        int v = graph[ i ][ j ].v;
        long double w = graph[ i ][ j ].weight;
        dist[ v ] = min( dist[ v ], dist[ i ] + w );
      }
    }
  }
  for( int i = 1; i <= N; i++ ) {
    for( int j = 0; j < graph[ i ].size(); j++ ) {
      int v = graph[ i ][ j ].v;
      long double w = graph[ i ][ j ].weight;
      if( dist[ v ] > dist[ i ] + w ) return true;
    }
  }
  return false;
}

int main( void )
{
	for( int t = 1;; t++ ) {
		int N,M;
		scanf("%d",&N);
		if( !N ) {
			break;
		}
		map< string,int > hash;
		vector< edge > graph[ N + 1 ];
		for( int i = 0; i < N; i++ ) {
			string str;
			cin >> str;
			hash[ str ] = i + 1;
		}
		scanf("%d",&M);
		for( int i = 0; i < M; i++ ) {
			long double w;
			string u,v;
			cin >> u >> w >> v;
			graph[ hash[ u ] ].push_back( make_edge( hash[ v ], -log( w ) ) );
		}
		/*for( int i = 1; i <= N; i++ ) {
			for( int j = 0; j < graph[ i ].size(); j++ ) {
				printf("for edge (%d,%d) -> %llf\n",i,graph[ i ][j ].v,graph[ i ][ j ].weight);
			}
		}*/
		if( belford( graph, N ) ) {
			printf("Case %d: Yes\n",t);
		} else {
			printf("Case %d: No\n",t);
		}
	}
	return 0;
}
