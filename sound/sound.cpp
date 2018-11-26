#include <stdio.h>
#include <algorithm>

using namespace std;

struct node {
	int first;
	int second;
};

node** rmq;
int* A, lg2;

int readint() {
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

void proc( int N, int K )
{
	for( int i = 1; i <= N; i++ ) {
		rmq[ 0 ][ i ].first = A[ i ];
		rmq[ 0 ][ i ].second = A[ i ];
	}
	for( int j = 1; 1 << j <= K; j++ ) {
		for( int i = 1; i + ( 1 << j ) - 1<= N; i++ ) {
			rmq[ j ][ i ].first = min( rmq[ j - 1 ][ i ].first, rmq[ j - 1 ][ i + ( 1 << ( j - 1 ) ) ].first );
			rmq[ j ][ i ].second = max( rmq[ j - 1 ][ i ].second, rmq[ j - 1 ][ i + ( 1 << ( j - 1 ) ) ].second );
		}
	}
}

int main( void )
{
	freopen("sound.in","rt",stdin);
	freopen("sound.out","wt",stdout);
	int N,K,C;
	bool status = false;
	N = readint();
	K = readint();
	C = readint();
	for( lg2 = 0; 1 << lg2 <= K; lg2++ );
	lg2--;
	rmq = new node*[ lg2 + 1 ];
	A = new int[ N + 1 ];
	for( int i = 0; i <= lg2; i++ ) {
		rmq[ i ] = new node[ N + 1 ];
	}
	for( int i = 1; i <= N; i++ ) {
		A[ i ] = readint();
	}
	proc( N,  K );
	for( int i = 1; i <= N - K + 1; i++ ) {
		int j = i + K - 1;
		if( max( rmq[ lg2 ][ i ].second, rmq[ lg2 ][ j - ( 1 << lg2 ) + 1 ].second ) - 
			min( rmq[ lg2 ][ i ].first, rmq[ lg2 ][ j - ( 1 << lg2 ) + 1 ].first ) <= C ) {
			fprintf(stdout , "%d\n", i );
			status = true;
		}
	}
	if( !status ) {
		fprintf(stdout, "NULL\n");
	}
	return 0;
}
