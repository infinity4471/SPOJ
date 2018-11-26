#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXL 27
#define MAXN 100000

using namespace std;

typedef long long ll;

struct node {
	int bits[ MAXL + 1 ];
	node() {
		memset( bits, 0, sizeof( bits ) );
	}
};

node BIT[ MAXN + 1 ];
int A[ MAXN + 1 ], N, Q;

void update( int pos, int val, int flag )
{
	int prevpos = pos, prevval = A[ pos ];
	A[ pos ] = val;
	while( prevpos <= N && flag ) {
		for( int i = 0; i < MAXL; ++i ) {
			int bit = prevval & ( 1 << i ) ? 1 : 0;
			BIT[ prevpos ].bits[ i ] -= bit;
		}
		prevpos += ( prevpos & -prevpos );
	}
	while( pos <= N ) {
		for( int i = 0; i < MAXL; ++i ) {
			int bit = val & ( 1 << i ) ? 1 : 0;
			BIT[ pos ].bits[ i ] += bit;
		}
		pos += ( pos & -pos );
	}
}

node query( int l, int r )
{
	node qq;
	while( r > 0 ) {
		for( int i = 0; i < MAXL; i++ ) qq.bits[ i ] += BIT[ r ].bits[ i ];
		r -= ( r & -r );
	}
	l--;
	while( l > 0 ) {
		for( int i = 0; i < MAXL; i++ ) qq.bits[ i ] -= BIT[ l ].bits[ i ];
		l -= ( l & -l );
	}
	return qq;
}

inline int ReadInt() {
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
	int u;
	N = ReadInt();
	Q = ReadInt();
	for( int i = 1; i <= N; ++i ) {
		u = ReadInt();
		update( i, u, 0 );
	}
	for( int i = 0; i < Q; ++i ) {
		int comp, t, l, r, v, cnt = 0;
		char s[ 10 ];
		t = ReadInt();
		if( t == 1 ) {
			v = ReadInt();
			l = ReadInt();
			update( l, v, 1 );
		} else {
			while( ( s[ cnt++ ] = getchar_unlocked() ) != 0x20 );
			cnt--;
			ll ans = 0;
			node qq;
			s[ cnt ] = '\0';	
			l = ReadInt();
			r = ReadInt();
			if( s[ 0 ] == 'X' ) {
				qq = query( l, r );
				for( int i = 0; i < MAXL; i++ ) {
					ans += ( ll )( r - l + 1 - qq.bits[ i ] ) * ( ll )qq.bits[ i ] * ( ll )( 1 << i );
				}
			}
			else if( s[ 0 ] == 'O' ) {
				qq = query( l, r );
				for( int i = 0; i < MAXL; i++ ) {
					ans += ( ( ll )( r - l + 1 - qq.bits[ i ] ) * ( ll )qq.bits[ i ] + 
						( ( ll )qq.bits[ i ] * ( ll )( qq.bits[ i ] - 1 ) / 2 ) ) * ( ll )( 1 << i );
				}
			} else {
				qq = query( l, r );
				for( int i = 0; i < MAXL; i++ ) {
					ans += ( ( ll )( qq.bits[ i ] * ( ll )( qq.bits[ i ] - 1 ) ) / 2  ) * ( ll )( 1 << i );
				}
			}
			printf("%lld\n", ans );
		}
	}
	return 0;
}
