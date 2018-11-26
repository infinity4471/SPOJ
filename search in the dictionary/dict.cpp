#include <cstdio>
#include <cstring>

#define MAXN 200000

using namespace std;

struct node {
	int ab[ 26 ];
	char* word;
	bool isword;
};

node trie[ MAXN + 1 ];
int nodecnt = 1,size = 0;
char* str[ MAXN + 1 ];

void init()
{
	for( int i = 0; i <= MAXN; i++ ) {
		trie[ i ].isword = false;
		trie[ i ].word = new char[ 100 ];
		str[ i ] = new char[ 100 ];
		for( int j = 0; j < 26; j++ ) {
			trie[ i ].ab[ j ] = 0;
		}
	}
}

void insert( char* word )
{
	int node = 0;
	for( int i = 0; i < strlen( word ); i++ ) {
		if( trie[ node ].ab[ word[ i ] - 'a' ] ) {
			node = trie[ node ].ab[ word[ i ] - 'a' ];
		} else {
			trie[ node ].ab[ word[ i ] - 'a' ] = nodecnt;
			node = nodecnt;
			nodecnt++;
		}
	}
	trie[ node ].isword = true;
	strcpy ( trie[ node ].word , word );
}

void dfs( int start, int node )
{
	if( trie[ node ].isword && node != start ) {
		str[ size++ ] = trie[ node ].word;
	}
	for( int i = 0; i < 26; i++ ) {
		int v = trie[ node ].ab[ i ];
		if( v ) {
			dfs( start, v );
		}
	}
}

void find_pref( char word[] )
{
	int node = 0;
	for( int i = 0; i < strlen( word ); i++ ) {
		if( !trie[ node ].ab[ word[ i ] - 'a' ] ) {
			return;
		} else {
			node = trie[ node ].ab[ word[ i ] - 'a' ];
		}
	}
	dfs( node, node );
}

int main( void )
{
	int N,Q;
	scanf("%d",&N);
	char  newstr[ 30 ];
	init();
	for( int i = 0; i < N; i++ ) {
		scanf("%s",&newstr);
		insert( newstr );
	}
	scanf("%d",&Q);
	for( int i = 1; i <= Q; i++ ) {
		scanf("%s",&newstr);
		size = 0;
		printf("Case #%d:\n",i);
		find_pref( newstr );
		for( int j = 0; j < size; j++ ) {
			printf("%s\n",str[ j ] );
		}
		if( !size ) {
			printf("No match.\n");
		}
	}
	return 0;
}
