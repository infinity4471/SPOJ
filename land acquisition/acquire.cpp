#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>

#define MAXN 100100
#define INF 10010000000
#define a first
#define b second

using namespace std;

typedef pair< long long, long long > pii;

int BIT[ MAXN + 1 ] = { 0 };

void add( int i )
{
	while( i > 0 ) {
		BIT[ i ]++;
		i -= ( i & -i );
	}
}

int find( int i )
{
	int ans = 0;
	while( i <= MAXN ) {
		ans += BIT[ i ];
		i += ( i & -i );
	}
	return ans;
}

vector< pii > s;

long long inter( pii x, pii y )
{
	return ( long long )( y.b - x.b ) / ( x.a - y.a );
}

long long evaluate( int idx, int x )
{
	return ( long long )s[ idx ].a * x + ( long long )s[ idx ].b;
}

void add( pii x )
{
	while( s.size() >= 2 && inter( x, s[ s.size() - 2 ] ) <= inter( s[ s.size() - 2 ], s[ s.size() - 1 ] ) ) s.pop_back();
	s.push_back( x );
}

long long Find( int x )
{
	int lo = 0,hi = s.size() - 1, ans = -1;
  while( lo <= hi ) {
		int mid = ( lo + hi ) / 2;
		if( evaluate( mid, x ) > evaluate( mid + 1, x ) ) {
			lo = mid + 1;
      ans = mid;
		} else {
			hi = mid - 1;
		}
	}
	return evaluate( ans, x );
}

int main( void )
{
	int N;
	scanf("%d", &N );
	long long dp[ N + 1 ];
	pii P[ N + 1 ];
	map< int, int > hash1, hash2;
	vector< pii > pp;
	vector< int > val;
	for( int i = 1; i <= N; i++ ) {
		scanf("%d%d", &P[ i ].a, &P[ i ].b );
		val.push_back( P[ i ].a );
		val.push_back( P[ i ].b );
	}
	sort( val.begin(), val.end() );
	for( int i = 0, cnt = 1; i < val.size(); i++ ) {
		if( !hash1[ val[ i ] ] ) {
			hash1[ val[ i ] ] = cnt;
			hash2[ cnt ] = val[ i ];
			cnt++;
		}
	}
	for( int i = 1; i <= N; i++ ) {
		P[ i ].a = hash1[ P[ i ].a ];
		P[ i ].b = hash1[ P[ i ].b ];
	}
	sort( P + 1, P + N + 1, greater< pii >());
	pp.push_back( make_pair( 0, 0 ) );
	for( int i = 1; i <= N; i++ ) {
		if( !find( P[ i ].b ) ) {
			pp.push_back( P[ i ] );
		}
		add( P[ i ].b );
	}
	for( int i = 1; i <= N; i++ ) {
		P[ i ].a = hash2[ P[ i ].a ];
		P[ i ].b = hash2[ P[ i ].b ];
	}
	sort( pp.begin(), pp.end() );
	for( int i = 1; i < pp.size(); i++ ) {
		pp[ i ].a = hash2[ pp[ i ].a ];
		pp[ i ].b = hash2[ pp[ i ].b ];
	}
	N = pp.size() - 1;
	dp[ 0 ] = 0;
	for( int i = 1; i <= N; i++ ) {
		add( make_pair( pp[ i ].b, dp[ i - 1 ] ) );
		dp[ i ] = Find( pp[ i ].a );
	}
	printf("%lld\n", dp[ N ] );
	return 0;
}
