#include <cstdio>
#include <cstring>
#include <algorithm>

#define INF 10000001
#define MAXN 200001

using namespace std;

struct pt {
	int x,y;
};

int BIT[ INF + 1 ];

struct query {
	pt A,B;
	int val;
	int type, idx, tobad;
};

bool cmp( query a, query b )
{
	pt A1,A2;
	if( a.type > 0 ) {
		A1 = a.B;
	} else {
		A1 = a.A;
	}
	if( b.type > 0 ) {
                A2 = b.B;
        } else {
                A2 = b.A;
        }
	if( A1.y == A2.y ) {
		if( A1.x == A2.x ) {
			return a.type < b.type;
		}
		return A1.x < A2.x;
	}
	return A1.y < A2.y;
}

int qq( int x )
{
	int val = 0;
	while( x > 0 ) {
		val += BIT[ x ];
		x -= ( x & -x );
	}
	return val;
}

void update( int x, int val )
{
	while( x <= INF ) {
		BIT[ x ] += val;
		x += ( x & -x );
	}
}

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
	int T;
	T = readint();
	while( T-- ) {
		int* badq = new int[ MAXN + 1 ];
		int* ans = new int[ MAXN + 1 ];
		query Q[ MAXN + 1 ];
		memset( &BIT, 0, sizeof( BIT ) );
		int N,M, size = 0;		
		N = readint();
		for( int i = 1; i <= N; i++ ) {
			Q[ i ].A.x = readint();
			Q[ i ].A.y = readint();
			Q[ i ].val = readint();
			Q[ i ].A.x++;
			Q[ i ].A.y++;
			Q[ i ].type = 0;
			Q[ i ].idx = i;
			size++;
		}
		M = readint();
		for( int i = N + 1, j = 1; j <= M; j++, i+= 2 ) {
			Q[ i ].A.x = readint();
			Q[ i ].A.y = readint();
			Q[ i ].B.x = readint();
			Q[ i ].B.y = readint();
			Q[ i ].type = 2;
			Q[ i + 1 ].A.x = Q[ i ].A.x;
			Q[ i + 1 ].A.y = 1;
			Q[ i + 1 ].B.x = Q[ i ].B.x;
			Q[ i + 1 ].B.y = Q[ i ].A.y - 1;
			Q[ i + 1 ].type = 1;
			Q[ i + 1 ].idx = j;
			Q[ i ].idx = j;
			Q[ i ].tobad = Q[ i + 1 ].idx;
			Q[ i ].A.x++;
                        Q[ i ].A.y++;
                        Q[ i ].B.x++;
                        Q[ i ].B.y++;
			Q[ i + 1 ].A.x++;
			Q[ i + 1 ].B.y++;
                        Q[ i + 1 ].B.x++;
			size+=2;
		}
		sort( Q + 1, Q + size + 1, cmp );
		for( int i = 1; i <= size; i++ ) {
			if( Q[ i ].type == 0 ) {
				update( Q[ i ].A.x, Q[ i ].val );
			}
			else if( Q[ i ].type == 1 ) {
				Q[ i ].val = qq( Q[ i ].B.x ) - qq( Q[ i ].A.x - 1 );
				badq[ Q[ i ].idx ] = Q[ i ].val;
			}
			else if( Q[ i ].type == 2 ) {
				Q[ i ].val = qq( Q[ i ].B.x ) - qq( Q[ i ].A.x - 1 ) - badq[ Q[ i ].tobad ];
				ans[ Q[ i ].idx ] = Q[ i ].val;
			}
		}
		for( int i = 1; i <= M; i++ ) {
			printf("%d\n", ans[ i ] );
		}
		delete [] badq;
		delete [] ans;
	}
	return 0;
}
