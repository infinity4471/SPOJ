#include <cstdio>
#include <algorithm>

#define MAX 100001
#define MOD 5000000

long long BIT[ MAX + 1 ];

using namespace std;

void init()
{
	for(int i = 0; i <= MAX; i++ ) {
		BIT[ i ] = 0;
	}
}

void add(int pos,int dp)
{
	while( pos <= MAX ) {
		BIT[ pos ] += dp;
		BIT[ pos ] = BIT[ pos ] % MOD;
		pos += ( pos & -pos );
	}
}

int query( int pos )
{
	int ans = 0;
	while( pos > 0 ) {
		ans += BIT[ pos ];
		ans = ans % MOD;
		pos -= ( pos & -pos );
	}
	return ans;
}

int main( void )
{
	int N,K;
	long long ans = 0;
	scanf("%d%d",&N,&K);
	int A[ N + 1 ],dp[ N + 1 ][ K + 1 ];
	for(int i = 1; i <= N; i++ ) {
		scanf("%d",&A[ i ] );
		A[ i ]++;
	}
	for(int i = 0; i <= N; i++ ) {
		dp[ i ][ 1 ] = 1;
	}
	for(int k = 2; k <= K; k++ ) {
		init();
		dp[ 1 ][ k ] =0;
		for(int i = 2; i <= N; i++ ) {
			add( A[ i - 1 ], dp[ i - 1][ k - 1] );
			dp[ i ][ k ] = query( A[ i ] - 1 );
			dp[ i ][ k ] = dp[ i ][ k ] % MOD;
		}
	}
	for(int i = 1; i <= N; i++ ) {
		ans += dp[ i ][ K ];
		ans = ans % MOD;
	}
	printf("%d\n",ans);
	return 0;
}
