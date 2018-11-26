#include <cstdio>
 
int main( void )
{
	int t;
	scanf("%d",&t);
	while( t-- ) {
		int c;
		scanf("%d",&c);
		printf("%d\n",c/2 + c %2 );
	}
	return 0;
}
