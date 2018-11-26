#include <cstdio>
#include <ctime>
#include <algorithm>

#define NUMWIT 3

using namespace std;

typedef unsigned long long ll;

int witness[ NUMWIT ];

ll mod_exp( ll n, ll a, ll p ) {
  ll res = 1;
  while( a ) {
    if( a & 1 ) res = ( res * n ) % p;
    n = ( n * n ) % p;
    a >>= 1;
  }
  return res;
}

bool miller_rabin( ll n ) {
  if( n == 1 ) return false;
  if( n == 2 ) return true;
  if( n % 2 == 0 ) return false;

  ll m = 0LLU, s;
  while( ( n & 1LLU ) == 0 ) {
    m++;
    n >>= 1;
  }
  s = n;
  for( ll i = 0; i < NUMWIT; i++ ) {
    ll a = mod_exp( witness[ i ], m, n );
    if( a == 1 || a == n - 1 ) continue;
    bool status = false;
    for( int j = 0; j < s; j++ ) {
      a = a * a % n;
      if( a == 1 ) return false;
      else if( a == n - 1 ) {
        status = true;
        break;
      }
    }
    if( !status ) return false;
  }
  return true;
}

int main( void ) {
  int T;
  scanf("%d", &T );
  for( int i = 0; i < T; i++ ) {
    ll n;
    scanf("%llu", &n );
    witness[ 0 ] = 2;
    witness[ 1 ] = 7;
    witness[ 2 ] = 61;
    printf("%s\n", miller_rabin( n ) ? "YES" : "NO" );
  }
  return 0;
}
