#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXL 27
#define MAXN 100000

using namespace std;

typedef long long ll;

struct node {
	int valid[ MAXL ];
	ll sum0, sum1, sum2;
};

node segtree[ 4*MAXN + 1 ];
int A[ MAXN + 1 ], N, Q;

void build( int n, int l, int r )
{
	if( l == r ) {
		for( int i = 0; i < MAXL; ++i ) {
			segtree[ n ].valid[ i ] = A[ l ] & ( 1 << i ) ? 1 : 0;
		}
	} else {
		int left = ( n << 1 ), right = ( left | 1 ), mid = ( l + r ) >> 1;
		build( left, l, mid );
		build( right, mid + 1, r );
		segtree[ n ].sum0 = segtree[ left ].sum0 + segtree[ right ].sum0;
		segtree[ n ].sum1 = segtree[ left ].sum1 + segtree[ right ].sum1;
		segtree[ n ].sum2 = segtree[ left ].sum2 + segtree[ right ].sum2;
		for( int i = 0; i < MAXL; ++i ) {
			segtree[ n ].valid[ i ] = segtree[ left ].valid[ i ] + segtree[ right ].valid[ i ];
			
			segtree[ n ].sum0 += ( ll )segtree[ left ].valid[ i ] * ( ll )( r - mid - segtree[ right ].valid[ i ] ) * ( 1 << i ) + 
						( ll )( mid - l + 1 - segtree[ left ].valid[ i ] ) * ( ll )segtree[ right ].valid[ i ] * ( 1 << i );
			segtree[ n ].sum1 += ( ll )segtree[ left ].valid[ i ] * ( ll )( r - mid - segtree[ right ].valid[ i ] ) * ( 1 << i ) + 
						( ll )( mid - l + 1 - segtree[ left ].valid[ i ] ) * ( ll)segtree[ right ].valid[ i ] * ( 1 << i ) +
						( ll )segtree[ left ].valid[ i ] * ( ll )segtree[ right ].valid[ i ] * ( 1 << i );
			segtree[ n ].sum2 += ( ll )segtree[ left ].valid[ i ] * ( ll )segtree[ right ].valid[ i ] * ( 1 << i );
		}
	}
}

void update( int n, int l, int r, int idx, int val )
{
	int mid = ( l + r ) >> 1, left = ( n << 1 ), right = left | 1;
	if( l == r ) {
		for( int i = 0; i < MAXL; ++i ) {
			segtree[ n ].valid[ i ] = val & ( 1 << i )? 1 : 0;
		}
		return;
	}
	if( idx <= mid ) update( left, l, mid, idx, val );
	else update( right, mid + 1, r, idx, val );
	segtree[ n ].sum0 = segtree[ left ].sum0 + segtree[ right ].sum0;
	segtree[ n ].sum1 = segtree[ left ].sum1 + segtree[ right ].sum1;
	segtree[ n ].sum2 = segtree[ left ].sum2 + segtree[ right ].sum2;
	for( int i = 0; i < MAXL; ++i ) {
		segtree[ n ].valid[ i ] = segtree[ left ].valid[ i ] + segtree[ right ].valid[ i ];
		
		segtree[ n ].sum0 += ( ll )segtree[ left ].valid[ i ] * ( ll )( r - mid - segtree[ right ].valid[ i ] ) * ( 1 << i ) + 
					( ll )( mid - l + 1 - segtree[ left ].valid[ i ] ) * ( ll )segtree[ right ].valid[ i ] * ( 1 << i );
		segtree[ n ].sum1 += ( ll )segtree[ left ].valid[ i ] * ( ll )( r - mid - segtree[ right ].valid[ i ] ) * ( 1 << i ) + 
					( ll )( mid - l + 1 - segtree[ left ].valid[ i ] ) * ( ll)segtree[ right ].valid[ i ] * ( 1 << i ) +
					( ll )segtree[ left ].valid[ i ] * ( ll )segtree[ right ].valid[ i ] * ( 1 << i );
		segtree[ n ].sum2 += ( ll )segtree[ left ].valid[ i ] * ( ll )segtree[ right ].valid[ i ] * ( 1 << i );
	}
}

node query( int n, int l, int r, int lx, int rx )
{
	int mid = ( l + r ) >> 1, left = ( n << 1 ), right = left | 1;
	if( l == lx && rx == r ) return segtree[ n ];
	else if( rx <= mid ) return query( left, l, mid, lx, rx );
	else if( lx > mid ) return query( right, mid + 1, r, lx, rx );
	else {
		node A,B,C;
		A = query( left, l, mid, lx, mid );
		B = query( right, mid + 1, r, mid + 1, rx );	
		C.sum0 = A.sum0 + B.sum0;
		C.sum1 = A.sum1 + B.sum1;
		C.sum2 = A.sum2 + B.sum2;
		int rightb = min( r, rx ), leftb = max( l, lx );
		for( int i = 0; i < MAXL; ++i ) {
			C.valid[ i ] = A.valid[ i ] + B.valid[ i ];
			C.sum0 += ( ll )A.valid[ i ] * ( rightb - mid - B.valid[ i ] ) * ( 1 << i ) +
					( ll )( mid - leftb + 1 - A.valid[ i ] ) * B.valid[ i ] * ( 1 << i );
			C.sum1 += ( ll )A.valid[ i ] * ( rightb - mid - B.valid[ i ] ) * ( 1 << i ) +
					( ll )( mid - leftb + 1 - A.valid[ i ] ) * B.valid[ i ] * ( 1 << i ) +
					( ll )A.valid[ i ] * B.valid[ i ] * ( 1 << i );
			C.sum2 += ( ll )A.valid[ i ] * B.valid[ i ] * ( 1 << i );
		}
		return C;
	}
}

inline int ReadInt()

{

 int c=getchar_unlocked();

 int out=0;

 while(c=='\n' || c==' ')

 c=getchar_unlocked();

 while(c!='\n' && c!=' ' && c!=-1)

 {

 out*=10;

 out+=(c-'0');

 c=getchar_unlocked();

 }

 return out;

}
int main( void )
{
	//freopen("test.in","rt",stdin);
	//freopen("test.out","wt",stdout);
	N = ReadInt();
	Q = ReadInt();
	for( int i = 1; i <= N; ++i ) A[ i ] = ReadInt();
	build( 1, 1, N );
	while( Q-- ) {
		int t, l, r, v, cnt = 0, comp;
		char s[ 4 ];
		t = ReadInt();
		if( t == 1 ) {
			v = ReadInt();
			l = ReadInt();
			update( 1, 1, N, l, v );
		} else {
			while( ( s[ cnt++ ] = getchar_unlocked() ) != 0x20 );
			cnt--;
			s[ cnt ] = '\0';
			l = ReadInt();
			r = ReadInt();
			node qq = query( 1, 1, N, l, r );
			comp = strcmp( s, "OR" );
			if( comp > 0) printf("%lld\n", qq.sum0 );
			else if( !comp ) printf("%lld\n", qq.sum1 );
			else printf("%lld\n", qq.sum2 );
		}
	}
	return 0;
}
