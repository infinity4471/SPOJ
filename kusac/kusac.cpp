#include <cstdio>

int gcd( int x, int y )
{
	if( y == 0 ) {
		return x;
	}
	return gcd( y, x % y );
}

int main( void )
{
	int x,y;
	scanf("%d%d", &x, &y );
	printf("%d\n", y - gcd( x, y ) );
	return 0;
}
