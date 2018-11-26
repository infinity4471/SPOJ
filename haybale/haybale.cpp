#include <cstdio>
#include <vector>
#include <algorithm>

#define MAX 1000000

using namespace std;

int main( void )
{
	int N,K,value[ MAX + 1 ] = {0},cost = 0;
	vector< int > vals;
	scanf("%d%d",&N,&K);
	for( int i = 0; i < K; i++ ) {
		int u,v;
		scanf("%d%d",&u,&v);
		value[ u ]++;
		value[ v + 1 ]--;
	}
	for( int i = 1; i <= N; i++ ) {
		cost+=value[ i ];
		vals.push_back( cost );
	}
	sort(vals.begin(),vals.end());
	printf("%d\n",vals[ vals.size() / 2 ]);
	return 0;
}
