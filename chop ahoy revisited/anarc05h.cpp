#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
#include <utility>
 
#define MAXN 30
 
using namespace std;
 
typedef pair< char,char > pii;
 
map< pii, int > dp;
char str[ MAXN + 1 ];

void DP( char i, char sum, char N )
{
	char newsum = 0;
	if( dp.find( make_pair( i, sum ) ) != dp.end() ) {
		return;
	}
	if( i >= N ) {
		dp[ make_pair( i, sum ) ] = 1;
		return;
	}
	dp[ make_pair( i, sum ) ] = 0;
	for( char j = i; j < N; j++ ) {
		newsum += str[ j ] - '0';
		//printf("newsum -> %d\n", newsum );
		if( sum <= newsum ) {
			//printf("newsum -> %d, sum -> %d, j -> %d\n", newsum, sum, j );
			DP( j + 1, newsum, N );
			dp[ make_pair( i, sum ) ] += dp[ make_pair( j + 1 , newsum ) ];
		}
	}
}
 
int main( void )
{
	int Case = 1;
	while( true ) {
		scanf("%s",&str);
		if( !strcmp( str, "bye" ) ) {
			break;
		}
		int N = strlen( str );
		DP( 0, 0, N );
		printf("%d. %d\n", Case++, dp[ make_pair( 0, 0 ) ] ) ;
		dp.clear();
	}
	return 0;
}
