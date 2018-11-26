#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <set>

#define AB 26
#define MAXL 100

using namespace std;

multiset< string > S;
string morse[ AB + 1 ];

void precompute()
{
	morse[ 0 ] = ".-";
	morse[ 1 ] = "-...";
	morse[ 2 ] = "-.-.";
	morse[ 3 ] = "-..";
	morse[ 4 ] = ".";
	morse[ 5 ] = "..-.";
	morse[ 6 ] = "--.";
	morse[ 7 ] = "....";
	morse[ 8 ] = "..";
	morse[ 9 ] = ".---";
	morse[ 10 ] = "-.-";
	morse[ 11 ] = ".-..";
	morse[ 12 ] = "--";
	morse[ 13 ] = "-.";
	morse[ 14 ] = "---";
	morse[ 15 ] = ".--.";
	morse[ 16 ] = "--.-";
	morse[ 17 ] = ".-.";
	morse[ 18 ] = "...";
	morse[ 19 ] = "-";
	morse[ 20 ] = "..-";
	morse[ 21 ] = "...-";
	morse[ 22 ] = ".--";
	morse[ 23 ] = "-..-";
	morse[ 24 ] = "-.--";
	morse[ 25 ] = "--..";
}

string make( string A )
{
	string M;
	for( int i = 0; i < ( int )A.length(); i++ ) {
		M.append( morse[ A[ i ] - 'A' ] );
	}
	return M;
}

int main( void )
{
	precompute();
	int T;
	scanf("%d", &T );
	while( T-- ) {
		S.clear();
		string code;
		cin >> code;
		int M, N = ( int )code.length();
		cin >> M;
		for( int i = 0; i < M; i++ ) {
			string str;
			cin >> str;
			S.insert( make( str ) );
		}
		int dp[ N + 1 ];
		dp[ 0 ] = 1;
		for( int i = 1; i <= N; i++ ) {
			dp[ i ] = 0;
			for( int d = 1; d <= min( i, MAXL ); d++ ) {
				int idx = i - d + 1;
				dp[ i ] += S.count( code.substr( idx - 1, d ) ) * dp[ idx - 1 ];
			}
		}
		printf("%d\n", dp[ N ] );
	}
	return 0;
}
