#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>

#define MAX 100000

using namespace std;

vector< int > tree[ MAX + 1 ];
int depth[ MAX + 1 ], visited[ MAX + 1 ],counter = 0;

void init()
{
	for( int i = 0; i <= MAX; i++ ) {
		tree[ i ].clear();
		depth[ i ] = 0;
		visited[ i ] = 0;
	}
	counter = 0;
}

void build( char cmd[], int start )
{
	tree[ start ].push_back( counter );
	if( cmd[ counter ] == 'l' || counter == strlen( cmd ) ) {
		return;
	}
	start = counter;
	counter++;
	build( cmd, start );
	counter++;
	build( cmd,  start );
}

void dfs( int s )
{
	visited[ s ] = 1;
	depth[ s ] = 0;
	for( int i = 0; i < tree[ s ].size(); i++ ) {
		int v = tree[ s ][ i ];
		if( !visited[ v ] ) {
			dfs( v );
			depth[ s ] = max( depth[ s ], depth[ v ] + 1 );
		}
	}
}

int main( void )
{
	int T;
	scanf("%d",&T);
	while( T-- ) {
		char tre[ MAX + 1 ];
		scanf("%s",&tre);
		init();
		build( tre, 0 );
		dfs(0);
		printf("%d\n",depth[ 0 ]);
	}
	return 0;
}
