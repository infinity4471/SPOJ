#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <cstring>

#define MAXN 100010

using namespace std;

int P[ MAXN + 1 ];

void prefix( string pattern )
{
	int N = pattern.length();
	P[ 0 ] = P[ 1 ] = 0;
	for( int i = 2; i <= N; i++ ) {
		int j = P[ i - 1 ];
		while( true ) {
			if( pattern[ i - 1 ] == pattern[ j ] ) {
				P[ i ] = j + 1;
				break;
			}
			else if( j == 0 ) {
				P[ i ] = 0;
				break;
			} else {
				j = P[ j ];
			}
		}
	}
}

int KMP( string text, string pattern )
{
	int N = text.length(), M = pattern.length();
	int i = 0, j = 0;
	while( true ) {
		if( i == N ) {
			break;
		}
		if( text[ i ] == pattern[ j ] ) {
			if( j == M - 1 ) {
				return M;
			}
			i++;
			j++;
		}
		else if( j == 0 ) {
			i++;
		} else {
			j = P[ j ];
		}
	}
	return j;	
}

int main( void )
{
	while( !feof( stdin ) ) {
		string text, rev;
		int N;
		cin >> text;
		if( feof( stdin ) ) break;
		memset( P, 0, sizeof( P ) );
		N = text.length();
		for( int i = N - 1; i >= 0; i-- ) {
			rev += text[ i ];
		}
		prefix( rev );
		int ans = KMP( text, rev );
		for( int i = ans; i < N; i++ ) {
			text += rev[ i ];
		}
		cout << text << endl;
	}
	return 0;
}
