#include <cstdio>
#include <algorithm>
#include <list>

using namespace std;

typedef pair< int, int > pii;

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

int main( void )
{
	//freopen("sound.in","rt",stdin );
	list< pii > minim, maxim;
	int N, K, M;
	bool status = false;
	N = readint(); M = readint(); K = readint();
	int A[ N + 1 ];
	for( int i = 1; i <= N; i++ ) {
		A[ i ] = readint();
		//printf("A[ %d ] = %d\n", i, A[ i ] );
	}
	for( int i = 1; i < M; i++ ) {
		while( !maxim.empty() && A[ i ] >= maxim.front().first ) {
			maxim.pop_front();
		}
		maxim.push_front( make_pair( A[ i ], i ) );
		while( !minim.empty() && A[ i ] <= minim.front().first ) {
			minim.pop_front();
		}
		minim.push_front( make_pair( A[ i ], i ) );
	}
	for( int i = M; i <= N; i++ ) {
		if( !maxim.empty() && maxim.back().second < i - M + 1 ) {
			maxim.pop_back();
		}
		if( !minim.empty() && minim.back().second < i - M + 1 ) {
			minim.pop_back();
		}
		while( !maxim.empty() && A[ i ] >= maxim.front().first ) {
			maxim.pop_front();
		}
		maxim.push_front( make_pair( A[ i ], i ) );
		while( !minim.empty() && A[ i ] <= minim.front().first ) {
			minim.pop_front();
		}
		minim.push_front( make_pair( A[ i ], i ) );
		if( maxim.back().first - minim.back().first <= K ) {
			status = true;
			printf("%d\n", i - M + 1 );
		}
	}
	if( !status ) {
		printf("NONE\n");
	}
	return 0;
}
