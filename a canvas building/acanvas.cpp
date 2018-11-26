#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 63

using namespace std;

int A[ MAXN + 1 ], N;

int memo[ MAXN + 1 ][ MAXN + 1 ][ MAXN + 1 ][ MAXN + 1 ];

int abs( int x ) {
  return x < 0 ? -x: x;
}
bool valid( int i, int j, int k ) {
  int CCW = 2*(A[ k ] - A[ j ] ) - 2*( A[ j ] - A[ i ] );
  return CCW < 0;
}

int dp( int i1, int i2, int i3, int i4, int cur ) {
  int& ret = memo[ i1 ][ i2 ][ i3 ][ i4 ];
  if( ret != -1 ) return ret;
  if( cur == 0 ) {
    return valid( 0, i1, i2 ) && valid( i3, i4, 0 );
  }
  ret = 0;
  if( valid( cur, i1, i2 ) || i1 == i2 ) ret = ret + dp( cur, i1, i3, i4, cur - 1 );
  if( A[ cur ] == A[ cur - 1 ] ) return ret;
  if( valid( i3, i4, cur ) || i3 == i4 ) ret = ret + dp( i1, i2, i4, cur, cur - 1 );
  return ret;
}

int main( void ) {
  while( true ) {
    scanf("%d", &N );
    if( N == -1 ) break;
    for( int i = 1; i <= N; i++ ) {
      scanf("%d", &A[ i ] );
    }

    sort( A + 1, A + N + 1 );
    memset( memo, -1, sizeof( memo ) );
    printf("%d\n", dp( N, N, N, N, N - 1 ) );
  }
  return 0;
}
