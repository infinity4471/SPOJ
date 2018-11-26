#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>

#define MAXN 40100
#define INF 10000100
#define L( n ) 2*n
#define R( n ) 2*n + 1

using namespace std;

typedef pair< int, int > pii;

struct node {
	int sum, flag;
};

node* segtree;

void init( int n, int l, int r )
{
	if( l == r ) {
		segtree[ n ].sum = 0;
		segtree[ n ].flag = 0;
	} else {
		init( L( n ), l, ( l + r ) / 2 );
		init( R( n ), ( l + r ) / 2 + 1, r );
		segtree[ n ].sum = 0;
		segtree[ n ].flag = 0;
	}
}

void unflag( int n, int l, int r )
{
	if( segtree[ n ].flag ) {
		segtree[ n ].sum = ( r - l + 1 ) * segtree[ n ].flag;
		if( l != r ) {
			segtree[ L( n ) ].flag = segtree[ n ].flag;
			segtree[ R( n ) ].flag = segtree[ n ].flag;
		}
		segtree[ n ].flag = 0;
	}
}

void update( int n, int l, int r, int i, int j, int val )
{
	if( l > j || r < i ) {
		unflag( n, l, r );
	}
	else if( i <= l && r <= j ) {
		segtree[ n ].flag = val;
		unflag( n, l, r );
	} else {
		unflag( n, l, r );
		update( L( n ), l, ( l + r ) / 2, i, j, val );
		update( R( n ), ( l + r ) / 2 + 1, r, i, j, val );
		if( l != r ) {
			segtree[ n ].sum = segtree[ L( n ) ].sum + segtree[ R( n ) ].sum;
		}
	}
}

int query( int n, int l, int r, int i, int j )
{
	if( l > j || r < i ) {
		return 0;
	}
	unflag( n, l, r );
	if( i <= l && r <= j ) {
		return segtree[ n ].sum;
	} else {
		return query( L( n ), l, ( l + r ) / 2, i, j ) + query( R( n ), ( l + r ) / 2 + 1, r, i, j );
	}
}

int main( void )
{
	int T;
	scanf("%d", &T );
	while( T-- ) {
		int N, ans = 0, cnt = 1, range;
		scanf("%d", &N );
		bool exist[ 10*MAXN + 1 ] = { 0 };
		int* M = new int[ INF + 1 ];
		exist[ 0 ] = 1;
		vector< pii > queries;
		vector< int > comp;
		for( int i = 1; i <= N; i++ ) {
			int u,v;
			scanf("%d%d", &u, &v );
			queries.push_back( make_pair( u, v ) );
			comp.push_back( u ); comp.push_back( v );
			M[ u ] = 0;
			M[ v ] = 0;
		}
		sort( comp.begin(), comp.end() );
		for( int i = 0; i < comp.size(); i++ ) {
			if( !M[ comp[ i ] ] ) {
				M[ comp[ i ] ] = cnt++;
			}
		}
		range = cnt + 1;
		segtree = new node[ 4*range + 1 ];
		init( 1, 1, range );
		for( int i = 0; i < queries.size(); i++ ) {
			queries[ i ].first = M[ queries[ i ].first ];
			queries[ i ].second = M[ queries[ i ].second ];
			update( 1, 1, range, queries[ i ].first, queries[ i ].second, i + 1 );
		}
		for( int i = 1; i <= range; i++ ) {
			int qq = query( 1, 1, range, i, i );
			if( !exist[ qq ] ) {
				ans++;
				exist[ qq ] = true;
			}
		}
		printf("%d\n", ans );
		delete [] segtree;
		delete [] M;
	}
	return 0;
}
