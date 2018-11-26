#include <cstdio>
#include <cstring>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
 
using namespace std;
 
int main( void )
{
	int cnt = 1;
	do {
		int N,K;
		scanf("%d%d",&K,&N);
		if( !K && !N ) {
			break;
		}
		getchar();
		vector< vector< int > > flow( 2*N , vector< int > ( 2*N,  0 ) );
		vector< vector< int > > cap( flow );
		int mysize = 2*N;
		vector< int > graph[ mysize + 1 ];
		int p[ 2*N ], visited[ 2*N ];
		for( int i = 0; i < N; i++ ) {
			char n;
			graph[ 2*i ].push_back( 2*i + 1 );
			cap[ 2*i ][ 2*i + 1] = 1;
			while( n != '\n' ) {
				int cnt = 0,arr[ 5 ],j = 0;
				while( isdigit( n = getchar() ) ) {
					arr[ cnt++ ] = n - '0';
				}
				for( int l = 0; l < cnt; l++ ) {
					j += pow( 10, cnt - l - 1 ) * arr[ l ];
				}
				j--;
				graph[ 2*i + 1 ].push_back( 2*j );
				cap[ 2*i + 1][ 2*j ] = 1;
			}
			n = 0;
		}
		printf("Case %d:\n",cnt++);
		int k = 0;
        	for( ; k < K; k++ ) {
        		for( int i = 0; i < 2*N; i++ ) {
                		p[ i ] = -1;
                		visited[ i ] = false;
        		}
        		queue< int > q;
        		q.push( 1 );
        		while( !q.empty() ) {
                		int u = q.front();
                		q.pop();
				visited[ u ] = true;
                		for( int i = 0; i < graph[ u ].size(); i++ ) {
                        		int v = graph[ u ][ i ];
                        		if( !visited[ v ] && cap[ u ][ v ] > flow[ u ][ v ] ) {
                                		q.push( v );
                                		p[ v ] = u;
                        		}
                		}
        		}
			if( !visited[ 2 ] ) {
				break;
			}
               		for( int i = 2; p[ i ] != -1; i = p[ i ] ) {
              			flow[ p[ i ] ][ i ]++;
               		     	flow[ i ][ p[ i ] ]--;
      	 		}
		}
		if( k == K ) {
			int pos;
			for( int i = 0; i < 2*N + 1; i++ ) {
				if( flow[ 1 ][ i ] == 1 ) {
					printf("1 %d",i / 2 + 1 );
					pos = i;
					while( pos != 2 ) {
						for( int j = 0; j < 2*N + 1; j++ ) {
							if( flow[ pos ][ j ] == 1 ) {
								pos = j;
								if( j % 2 == 0 ) {
									printf(" %d", j / 2 + 1 );
								}
								break;
							}
						}
					}
					printf("\n");
				}
			}
		}  else {
			printf("Impossible\n");
		}
		printf("\n");
	} while( true );
	return 0;
}
