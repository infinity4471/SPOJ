#include <cstdio>
#include <algorithm>
#include <vector>

#define MAX 1000

using namespace std;

int par[ MAX + 1 ],num[ MAX + 1 ];
long long cost[ MAX + 1 ];

void makenode(int u,int w)
{
	par[ u ] = u;
	cost[ u ] = w;
	num[ u ] = 1;
}

int find(int u)
{
	if( par[ u ] == u ) {
		return par[ u ];
	} else {
		return par[ u ] = find( par[ u ] );
	}
}

void Union(int u,int v)
{
	u = find( u );
	v = find( v );
	par[ v ] = u;
	cost[ u ] += cost[ v ];
	num[ u ] += num[ v ];
}

int main( void )
{
	while( true ) {
		int N,C;
		scanf("%d%d",&N,&C);
		if( !N && !C ) {
			break;
		}
		int dp[ C + 1][ N + 1 ],val[ N + 1 ], found[ N + 1 ];
		vector< int > comp;
		for(int i = 1; i <= N; i++ ) {
			found[ i ] = false;
		}
		for(int i = 1; i <= N; i++ ) {
			scanf("%d",&val[ i ]);
			makenode( i, val[ i ] );
		}
		for(int i = 1; i <= N; i++ ) {
			int n,v;
			scanf("%d",&n);
			for(int j = 0; j < n; j++ ) {
				scanf("%d",&v);
				if( find( v ) != find( i ) ) {
					Union( i , v );
				}
			}
		}
		for(int i = 0; i <= C; i++ ) {
			dp[ i ][ 0 ] = 0;
		}
		for(int i = 0; i <= N; i++ ) {
			dp[ 0 ][ i ] = 0;
		}
		for(int i = 1; i <= N; i++ ) {
			if( !found[ find( i ) ] ) {
				comp.push_back( find( i  ) );
			}
			found[ find( i ) ] = true;
		}
		/* dp[ i ][ j ] = the optimal way to select persons from the j first valid nodes using capaciy i */
		for(int i = 1; i <= C; i++ ) {
			for(int j = 0; j < comp.size(); j++ ) {
				int k = j + 1;
				if( i - cost[ comp[ j ] ] < 0 ) {
					dp[ i ][ k ] = dp[ i ][ j ];
				} else {
					dp[ i ][ k ] = max( dp[ i ][ j ],dp[ i - cost[ comp[ j ] ] ][ j ] + num[ comp[ j ] ] );
				}
			}
		}
		printf("%d\n",dp[ C ][ comp.size() ] );
	}
	return 0;
}
