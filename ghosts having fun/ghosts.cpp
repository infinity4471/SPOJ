#include <cstdio>
#include <algorithm>
 
#define MAXN 1010
 
using namespace std;
 
int G[ MAXN + 1 ][ MAXN + 1 ][ 2 ], size[ MAXN + 1 ][ 2 ];
bool visited[ MAXN + 1 ][ 2 ], isthere[ MAXN + 1 ][ MAXN + 1 ];
 
void update_original( int u, int v )
{
	visited[ v ][ 0 ] |= 1;
	isthere[ u ][ v ] = true;
	for( int i = 0; i < size[ v ][ 0 ]; ++i ) {
		if( visited[ G[ v ][ i ][ 0 ] ][ 0 ] ) continue;
		update_original( u, G[ v ][ i ][ 0 ] );
	}
}

void update_transpose( int u, int v )
{
	visited[ v ][ 1 ] |= 1;
	isthere[ v ][ u ] = true;
	for( int i = 0; i < size[ v ][ 1 ]; ++ i ) {
		if( visited[ G[ v ][ i ][ 1 ] ][ 1 ] ) continue;
		update_transpose( u, G[ v ][ i ][ 1 ] );
	}
}

inline int readint() {
    int n = 0;
    char c = getchar_unlocked();
    while ( !( '0' <= c && c <= '9' ) ) {
        c = getchar_unlocked();
    }
    while ( '0' <= c && c <= '9' ) {
        n = n * 10 + c - '0';
        c = getchar_unlocked();
    }
    return n;
}
 
int main( void )
{
	//freopen("test.in","rt",stdin);
	//freopen("test2.out","wt",stdout);
	int N, M, u, v;
	N = readint();
	M = readint();
	for( int i = 1; i <= N; i++ ) isthere[ i ][ i ] = true;
	while( M-- ) {
		u = readint();
		v = readint();
		for( int i = 1; i <= N; i++ ) visited[ i ][ 0 ] = visited[ i ][ 1 ] = false;
		if( isthere[ v ][ u ] ) {
			printf("%d %d\n", u, v );
			continue;
		}
		if( isthere[ u ][ v ] ) continue;
		G[ u ][ size[ u ][ 0 ]++ ][ 0 ] = v;
		G[ v ][ size[ v ][ 1 ]++ ][ 1 ] = u;
		update_original( u, v );
		update_transpose( v, u );
	}
	puts("0 0");
	return 0;
}
