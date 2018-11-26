#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
 
#define MAXN 1000001
 
using namespace std;
 
typedef long long ll;
typedef pair< ll, ll > pii;
 
vector< pii > S;
int point = 0;
ll sum[ MAXN + 1 ], dp[ MAXN + 1 ];
 
inline ll intersect( pii a, pii b )
{
	return ( b.second - a.second ) / ( a.first - b.first );
}
 
inline ll evaluate( int idx, ll x )
{
	return S[ idx ].first * x + S[ idx ].second;
}
 
ll find( ll x )
{
	int lo = 0, hi = S.size() - 1;
	while( lo < hi ) {
		int mid = ( lo + hi ) / 2;
		if( evaluate( mid, x ) >= evaluate( mid + 1, x ) ) {
			hi = mid;
		} else {
			lo = mid + 1;
		}
	}
	return evaluate( lo, x );
}
 
void insert( pii A )
{
	while( S.size() >= 2 && intersect( A, S[ S.size() - 2 ] ) > intersect( S[ S.size() - 2 ], S[ S.size() - 1 ] ) ) {
		S.pop_back();
	}
	S.push_back( A );
}
 
int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int N, u, a, b, c;
		while( !S.empty() ) {
			S.pop_back();
		}
		scanf("%d%d%d%d", &N, &a, &b, &c );
		sum[ 0 ] = 0;
		for( int i = 1; i <= N; i++ ) {
			scanf("%d", &u );
			sum[ i ] = sum[ i - 1 ] + ( ll )u;
		}
		dp[ 1 ] = a*sum[ 1 ]*sum[ 1 ] + b*sum[ 1 ] + c;
		insert( make_pair( -sum[ 1 ], a*sum[ 1 ]*sum[ 1 ] + dp[ 1 ] ) );
		for( int i = 2; i <= N; i++ ) {
			dp[ i ] = max( ( ll ) 0, find( b + 2*a*sum[ i ] ) ) + sum[ i ]*( a*sum[ i ] + b ) + c;
			insert( make_pair( -sum[ i ], ( ll )a*sum[ i ]*sum[ i ] + dp[ i ] ) );
		}
		printf("%lld\n", dp[ N ] );
	}
	return 0;
}
