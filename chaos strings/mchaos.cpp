#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
 
#define MAX 100010
 
long long BIT[ MAX + 1 ] = { 0 };
 
using namespace std;

struct str {
	char s[ 10 ];
	int idx;
};

str v[ MAX + 1 ], vreg[ MAX + 1 ];

bool cmp( str a, str b )
{
	int v = strcmp( a.s, b.s );
	if( v < 0 ) {
		return true;
	} else {
		return false;
	}
}
 
void add( int i, int N )
{
	while( i <= MAX ) {
		BIT[ i ]++;
		i += ( i & -i );
	}
}
 
long long query( int i )
{
	long long ans = 0;
	while( i > 0 ) {
		ans += BIT[ i ];
		i -= ( i & -i );
	}
	return ans;
}
 
int main( void )
{
	int N;
	long long ans = 0;
	scanf("%d",&N);
	for( int i = 0 ; i < N ; i++ ) {
        	scanf("%s",vreg[ i ].s );
	}
	for ( int i = 0 ; i < N ; i++ ) {
        	int len = strlen( vreg[i].s );
       	 	for (int j = len-1 ; j >= 0 ; j-- ) {
         		v[ i ].s[ (len - 1) - j ] = vreg[ i ].s[ j ];
		}
      	 	v[ i ].idx = i + 1;
	}
	sort( v, v + N, cmp );
	for( int i = 0; i < N; i++ ) {
		vreg[ v[ i ].idx - 1 ].idx = i + 1;
	}
	sort( vreg, vreg + N, cmp );
	for( int i = 0; i < N; i++ ) {
		ans += query( vreg[ i ].idx - 1 );
		add( vreg[ i ].idx, N );
	}
	printf("%lld\n", ( long long ) N*(N - 1 ) / 2 - ans  );
	return 0;
}
