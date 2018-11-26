#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
 
#define MOD 1000000007LL
#define AB 256
 
using namespace std;
 
typedef long long ll;
 
int N;
string S, H;
 
void rabin_karp() {
int n1 = S.length(), n2 = H.length();
if( n1 > n2 ) return;
ll hash1 = 0, hash2 = 0, mult = 1;
for( int i = 0; i < n1; i++ ) {
hash1 = ( ( hash1 * AB ) % MOD + S[ i ] ) % MOD;
hash2 = ( ( hash2 * AB ) % MOD + H[ i ] ) % MOD;
}
if( hash1 == hash2 ) printf("0\n");
for( int i = 0; i < n1 - 1; i++ ) {
mult = ( mult * AB ) % MOD;
}
for( int i = n1; i < n2; i++ ) {
hash2 = ( hash2 - ( ll )( mult * H[ i - n1 ] ) % MOD ) % MOD;
hash2 = hash2 * AB % MOD;
hash2 = ( hash2 + H[ i ] ) % MOD;
if( hash2 < 0 ) hash2 += MOD;
if( hash1 == hash2 ) printf("%d\n", i - n1 + 1 );
}
}

int main( void ) {
  scanf("%d", &N );
  do {

    cin >> S >> H;
    rabin_karp();

    if( scanf("%d", &N ) == 1 ) printf("\n");
    else break;
  } while( true );
  return 0;
}
