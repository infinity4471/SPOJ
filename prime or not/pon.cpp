#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

typedef unsigned long long llu;

llu mulmod( llu a, llu b, llu c){
  llu x = 0,y = a%c;
  while(b>0){
    if(b&1) x = (x+y)%c;
    y = (y<<1)%c;
    b >>= 1;
}
return x;
}

llu modexp( llu a, llu b, llu c ) {
  if( b == 0 ) return 1LLU;
  if( b == 1 ) return a;
  else if( b % 2 == 0 ) {
    llu res = modexp( a, b >> 1, c );
    return mulmod( res, res, c );
  } else {
    llu res = modexp( a, ( b - 1 ) >> 1, c );
    return mulmod( a, mulmod( res, res, c ), c );
  }
}

bool little_fermat( llu a, llu p ) {
  llu exxp = modexp( a, ( llu )( p - 1 ), p );
  if( exxp % p == 1 ) return true;
  return false;
}

int main( void ) {
  int T;
  scanf("%d", &T );
  srand( time( NULL ) );
  while( T-- ) {
    int state = 1;
    llu A;
    scanf("%llu", &A );
    for( int i = 0; i < 100; i++ ) {
      llu a = a % ( A - 1 );
      a++;
      int res = little_fermat( a, A );
      if( !res ) {
        state = 0;
        break;
      }
    }
    printf("%s\n", state ? "YES": "NO" );
  }
  return 0;
}
