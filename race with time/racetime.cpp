#include <cstdio>
#include <algorithm>
#include <utility>

#define val first
#define id second
#define mp make_pair
#define BUCKET 317
#define MAXN BUCKET*BUCKET + 15
#define INF 1234567890

using namespace std;

typedef pair< int, int > pii;

pii cows[ MAXN + 1 ];
int mybucket[ MAXN + 1 ];
int N,Q;

void init()
{
	for( int i = 1; i <= MAXN; i++ ) {
		cows[ i ] = mp( INF, INF );
		if( i % BUCKET == 0 ) mybucket[ i ] = mybucket[ i - 1 ];
		else mybucket[ i ] = i / BUCKET + 1;
	}
}

int bsearch( int bucket, int X )
{
	int lo = ( bucket - 1 )*BUCKET + 1, hi = bucket*BUCKET, pos = lo - 1;
	if( cows[ lo ].val > X ) {
		return 0;
	}
	while( lo <= hi ) {
		int mid = ( lo + hi ) / 2;
		if( cows[ mid ].val > X ) {
			hi = mid - 1;
		} else {
			pos = mid;
			lo = mid + 1;
		}
	}
	return pos - ( bucket - 1 ) * BUCKET;
}

void update( int id, int val )
{
	int buck = mybucket[ id ];
	for( int i = ( buck - 1 )*BUCKET + 1; i <= buck*BUCKET; i++ ) {
		if( cows[ i ].id == id ) {
			cows[ i ].val = val;
			break;
		}
	}
	sort( cows + ( buck - 1 )*BUCKET + 1, cows + buck*BUCKET + 1 );
}

int query( int l, int r, int X )
{
	int buck1 = mybucket[ l ], buck2 = mybucket[ r ], ans = 0;
	if( buck1 == buck2 ) {
		for( int i = (buck1 - 1 )*BUCKET + 1; i <= buck1*BUCKET; i++ ) {
			if( cows[ i ].id >= l && cows[ i ].id <= r && cows[ i ].val <= X ) {
				ans++;
			}
		}
		return ans;
	}
	for( int i = ( buck1 - 1 )*BUCKET + 1; i <= buck1*BUCKET; i++ ) {
		if( cows[ i ].id >= l && cows[ i ].id <= r && cows[ i ].val <= X ) {
			ans++;
		}
	}
	for( int i = ( buck2 - 1 )*BUCKET + 1; i <= buck2*BUCKET; i++ ) {
		if( cows[ i ].id >= l && cows[ i ].id <= r && cows[ i ].val <= X ) {
			ans++;
		}
	}
	for( int i = buck1 + 1; i < buck2; i++ ) {
		ans += bsearch( i, X );
	}
	return ans;
}

void read()
{
	int cowi;
	scanf("%d%d", &N, &Q );
	for( int i = 1; i <= N; i++ ) {
		scanf("%d", &cowi );
		cows[ i ] = mp( cowi, i );
	}
	for( int i = 1; i <= BUCKET; i++ ) {
		sort( cows + ( i - 1 )*BUCKET + 1, cows + i*BUCKET + 1 );
	}
}

void solve()
{
	char c;
	int u,v,w;
	for( int i = 1; i <= Q; i++ ) {
		scanf("\n");
		scanf("%c", &c );
		if( c == 'M' ) {
			scanf("%d%d", &u, &v );
			update( u, v );
		} else {
			scanf("%d%d%d", &u, &v, &w );
			printf("%d\n", query( u, v, w ) );
		}
	}
}

int main( void )
{
	init();
	read();
	solve();
	return 0;
}
