#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 20000
#define MOD 1000000007
#define AB 127

using namespace std;

typedef long long ll;

int N, suffix[ MAXN + 1 ];
ll sufhash[ MAXN + 1 ], pows[ MAXN + 1 ];
char S[ MAXN + 1 ];

void hashit() {
  sufhash[ N ] = 0LL;
  pows[ 0 ] = 1LL;
  for( int i = N - 1; i >= 0; i-- ) {
    sufhash[ i ] = ( ( ll )AB * sufhash[ i + 1 ] ) % MOD;
    sufhash[ i ] = ( ll )( sufhash[ i ] + S[ i ] ) % MOD;
    pows[ N - i ] = ( pows[ N - i - 1 ] * AB ) % MOD;
  }
}

inline bool myhash( int A, int B, int len ) {
  return ( sufhash[ A ] + ( pows[ len ] * sufhash[ B + len ] % MOD ) ) % MOD == ( sufhash[ B ] + ( pows[ len ] * sufhash[ A + len ] % MOD ) ) % MOD;
}

int find_lcp( int A, int B ) {
  int lo = 1, hi = N - max( A, B ), idx = 0;
  while( lo <= hi ) {
    int mid = ( lo + hi ) >> 1;
    if( myhash( A, B, mid ) ) {
      idx = mid;
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  }
  return idx;
}

int cmp( const void* AA, const void* BB ) {
  int A = ( *(int*) AA );
  int B = ( *( int* ) BB );
  if( S[ A ] != S[ B ] ) return S[ A ] - S[ B ];
  int lcp = find_lcp( A, B );
  if( lcp == N - A || lcp == N - B ) return A - B;
  return S[ A + lcp ] - S[ B + lcp ];
}

int main( void ) {
  int T;
  scanf("%d\n", &T );
  while( T-- ) {
    N = -1;
    do {
      S[ ++N ] = getchar_unlocked();
    } while( S[ N ] != '\n' );
    for( int i = N; i < ( N << 1 ); i++ ) {
      S[ i ] = S[ i - N ];
	    suffix[ i - N ] = i - N;
    }
    N <<= 1;
    hashit();
    qsort( suffix, N, sizeof( int ), cmp );
    int i = 0;
    while( ( suffix[ i ] << 1 ) >= N ) i++;
    printf("%d\n", suffix[ i ] + 1 );
  }
  return 0;
}
