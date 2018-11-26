#include <stdio.h>
#include <math.h>
#include <ctype.h>

#define max( a, b ) ( a ) > ( b ) ? ( a ) : ( b )
#define min( a, b ) ( a ) < ( b ) ? ( a ) : ( b )

inline double Read_Double ( void ) // fast IO
{
    bool Negative = false;
    char Ch;
 
    while ( ! isdigit ( Ch = getchar_unlocked( ) ) ) if ( Ch == '-' ) Negative = true;
        else Negative = false;
 
    double Ret = Ch - '0';
 
    while ( isdigit ( Ch = getchar_unlocked( ) ) ) Ret = Ret * 10 + ( Ch - '0' );
 
    double Mul = 1.00;
 
    if ( Ch == '.' )
    {
        while ( isdigit ( Ch = getchar_unlocked( ) ) )
        {
            Mul /= 10.00;
 
            Ret += ( Ch - '0' ) * Mul;
        }
    }
 
    if ( Negative ) Ret *= -1.00;
 
    return Ret;
}

int main( void )
{
	int N;
	scanf("%d",&N);
	double a,b,c,d, ans, minim[ 8 ], maxim[ 8 ];
	for( int i = 0; i < 8; i++ ) {
		minim[ i ] = (INFINITY);
		maxim[ i ] = -(INFINITY);
	}
	for( int i = 0; i < N; i++ ) {
		a = Read_Double();
		b = Read_Double();
		c = Read_Double();
		d = Read_Double();
		minim[ 0 ] = min( minim[ 0 ], a + b + c + d );
		minim[ 1 ] = min( minim[ 1 ], a - b + c + d );
		minim[ 2 ] = min( minim[ 2 ], a + b - c + d );
		minim[ 3 ] = min( minim[ 3 ], a + b + c - d );
		minim[ 4 ] = min( minim[ 4 ], a - b - c + d );
		minim[ 5 ] = min( minim[ 5 ], a + b - c - d );
		minim[ 6 ] = min( minim[ 6 ], a - b + c - d );
		minim[ 7 ] = min( minim[ 7 ], a - b - c - d );
		maxim[ 0 ] = max( maxim[ 0 ], a + b + c + d );
		maxim[ 1 ] = max( maxim[ 1 ], a - b + c + d );
		maxim[ 2 ] = max( maxim[ 2 ], a + b - c + d );
		maxim[ 3 ] = max( maxim[ 3 ], a + b + c - d );
		maxim[ 4 ] = max( maxim[ 4 ], a - b - c + d );
		maxim[ 5 ] = max( maxim[ 5 ], a + b - c - d );
		maxim[ 6 ] = max( maxim[ 6 ], a - b + c - d );
		maxim[ 7 ] = max( maxim[ 7 ], a - b - c - d );
	}
	for( int i = 0; i < 8; i++ ) {
		for( int j = 0; j < 8; j++ ) {
			if( i != j ) {
				ans = max( ans, maxim[ i ] - minim[ i ] );
			}
		}
	}
	printf("%.3lf\n",ans );
	return 0;
}
