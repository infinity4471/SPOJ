#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

int N, M, *P;
string pattern, text;

void prefix_function() {
  P[ 0 ] = -1;
  for( int i = 1; i < N; i++ ) {
    int j = P[ i - 1 ];
    do {
      if( pattern[ j + 1 ] == pattern[ i ] ) {
        P[ i ] = j + 1;
        break;
      }
      else if( j == -1 ) {
        P[ i ] = -1;
        break;
      }
      else j = P[ j ];
    } while( true );
  }
}

void KMP() {
  int i = 0, j = -1;
  char c;
  do {
    if( i == M ) break;
    if( text[ i ] == pattern[ j + 1 ] ) {
      j++;
      if( j == N - 1 ) {
        printf("%d\n", i - N + 1 );
        j = P[ N - 1 ];
      }
      i++;
    }
    else if( j < 0 ) i++;
    else j = P[ j ];
  } while( true );
}

int main( void ) {
  int cnt = 0;
  scanf("%d", &N );
  do {
    P = new int[ N + 2 ];

    cin >> pattern >> text;
    M = text.length();
    prefix_function();
    KMP();

    if( scanf("%d", &N ) == 1 ) printf("\n");
    else break;
  } while( true );
  return 0;
}
