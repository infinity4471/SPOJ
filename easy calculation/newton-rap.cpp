#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>

#define MAXN 101000

using namespace std;

double A, B, C;

double f( double x ) {
  return ( double )( A * x + B * sin( x ) - C );
}

double derivative_f( double x ) {
  return A + B * ( double )cos( x );
}

int main( void ) {
  int T;
  scanf("%d", &T );
  while( T-- ) {
    scanf("%lf%lf%lf", &A, &B, &C );
    double xs = ( double )6.5;
    for( int i = 0; i < 40; i++ ) {
      xs = xs - ( double )( f( xs ) / derivative_f( xs ) );
    }
    printf("%0.6lf\n", xs );
  }
}
