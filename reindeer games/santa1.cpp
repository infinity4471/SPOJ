#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>

#define mp make_pair
#define senior first
#define prod second

using namespace std;

typedef unsigned long long llu;
typedef pair< llu, llu > pll;

set< pll > S;

llu prev( pll val )
{
	 set< pll >::iterator it = S.find( val );
	 if( it != S.begin() && it != S.end() ) {
		return ( llu )( *( --it ) ).prod;
	}
	return ( llu )0;
}

llu next( pll val )
{
	set< pll >::iterator it = S.find( val );
	if( it != --S.end() && it != S.end() ) {
		return ( llu )( *( ++it ) ).prod;
	}
	return ( llu )0;
}

int main( void )
{
	int M;
	llu ans = 0;
	char c, name[ 25 ];
	llu u,v;
	scanf("%d", &M );
	map< string, pll > val;
	map< string, bool > added;
	for( int i = 0; i < M; i++ ) {
		scanf("%*c%c %s", &c, name );
		if( c == 'A' ) {
			scanf("%llu %llu", &u, &v );
			val[ name ] = mp( u, v );
			added[ name ] = true;
			S.insert( val[ name ] );
			ans += ( llu )prev( val[ name ] ) * val[ name ].prod;
			ans += ( llu )next( val[ name ] ) * val[ name ].prod;
			ans -= ( llu )prev( val[ name ] ) * next( val[ name ] );
		} else {
			if( added[ name ] ) {
				pll cur = val[ name ];
				ans -= ( llu )prev( cur ) * cur.prod;
				ans -= ( llu )next( cur ) * cur.prod;
				ans += ( llu )next( cur ) * prev( cur );
				S.erase( cur );
				added[ name ] = false;
			}
		}
		printf("%llu\n", ans );
	}
	return 0;
}
