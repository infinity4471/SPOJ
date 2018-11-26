#include <cstdio>
#include <algorithm>
#include <vector>

#define MAXN 10001
#define WHITE 0
#define GRAY 1
#define BLACK 2

using namespace std;

int num[ MAXN + 1 ], low[ MAXN + 1 ], p[ MAXN + 1 ], cnt = 1, root;
bool A[ MAXN + 1 ] = { 0 };

void dfs( vector< int > graph[], int visited[], int u )
{
	int chil = 0;
	num[ u ] = cnt++;
	low[ u ] = num[ u ];
	visited[ u ] = GRAY;
	for( int i = 0; i < graph[ u ].size(); i++ ) {
		int v = graph[ u ][ i ];
		if( visited[ v ] == WHITE ) {
			p[ v ] = u;
			chil++;
			dfs( graph, visited, v );
			low[ u ] = min( low[ u ], low[ v ] );
			if( num[ u ] <= low[ v ] && u != root ) {
				A[ u ] = true;
			}
		}
		else if( visited[ v ] == GRAY && v != p[ u ] ) {
			low[ u ] = min( low[ u ], num[ v ] );
		}
	}
	if( u == root && chil >= 2 ) {
		A[ u ] = true;
	}
	visited[ u ] = BLACK;
}
void AP( vector< int > graph[], int N )
{
	int visited[ N + 1 ];
	for( int i = 0; i <= N; i++ ) {
		visited[ i ] = WHITE;
	}
	for( int i = 1; i <= N; i++ ) {
		if( visited[ i ] == WHITE ) {
			root = i;
			dfs( graph, visited, i );
		}
	}
}

int main( void )
{
	while( true ) {
		int N,K, ans = 0;
		scanf("%d%d", &N, &K );
		if( !N && !K ) {
			break;
		}
		cnt = 1;
		for( int i = 0; i <= MAXN; i++ ) {
			A[ i ] = 0;
			num[ i ] = 0;
			low[ i ] = 0;
			p[ i ] = 0;
		}
		vector< int > graph[ N + 1 ];
		for( int i = 0; i < K; i++ ) {
			int u,v;
			scanf("%d%d", &u, &v );
			graph[ u ].push_back( v );
			graph[ v ].push_back( u );
		}
		AP( graph, N );
		for( int i = 1; i <= N; i++ ) {
			if( A[ i ] ) {
				ans++;	
			}
		}
		printf("%d\n", ans );
	}
	return 0;
}
