#include <cstdio>
#include <algorithm>
#include <cstring>

#define MAXN 513
#define MAXL 9
#define INF 1234567890

using namespace std;

int N, A[ MAXN + 1 ][ MAXN + 1 ], S[ MAXN + 1 ][ MAXN + 1 ], memo[ MAXL + 1 ][ MAXN + 1 ][ MAXN + 1 ][ 3 ];
int sol[ MAXN + 1 ][ MAXN + 1 ], choice[ MAXL + 1 ][ MAXN + 1 ][ MAXN + 1 ];

void precompute()
{
	for( int i = 1; i <= N; i++ ) {
		for( int j = 1; j <= N; j++ ) {
			S[ i ][ j ] = S[ i - 1 ][ j ] + S[ i ][ j - 1 ] - S[ i - 1 ][ j - 1 ] + A[ i ][ j ];
		}
	}
}

int get_sum( int i, int j, int k, int l )
{
	int sum1 = S[ i - 1 ][ j - 1 ];
	int sum2 = S[ k ][ j - 1 ];
	int sum3 = S[ i - 1 ][ l ];
	int sum4 = S[ k ][ l ];
	return sum4 - sum3 - sum2 + sum1;
}

int dp( int n, int i, int j, int col )
{
	int nn = 1 << n;
	if( memo[ n ][ i ][ j ][ col + 1 ] != -1 ) return memo[ n ][ i ][ j ][ col + 1 ];
	if( col == 1 ) return memo[ n ][ i ][ j ][ col + 1 ] = nn*nn - get_sum( i, j, i + nn - 1, j + nn - 1 );
	else if( col == 0 ) return memo[ n ][ i ][ j ][ col + 1 ] = get_sum( i, j, i + nn - 1, j + nn - 1 );
	if( n == 0 ) return memo[ n ][ i ][ j ][ col + 1 ] = 0;
	int& ans = memo[ n ][ i ][ j ][ col + 1 ] = INF;
	int ans1 = dp( n - 1, i, j, 0 ) + dp( n - 1, i + nn / 2, j, 1 ) + dp( n - 1, i, j + nn / 2, -1 ) + dp( n - 1, i +  nn / 2, j + nn / 2, -1 );
	int ans2 = dp( n - 1, i, j, 0 ) + dp( n - 1, i + nn / 2, j, -1 ) + dp( n -1, i, j + nn / 2, 1 ) + dp( n - 1, i +  nn / 2, j + nn / 2, -1 );
	int ans3 = dp( n - 1, i, j, 0 ) + dp( n - 1, i + nn / 2, j, -1 ) + dp( n - 1, i, j + nn / 2, -1 ) + dp( n - 1, i +  nn / 2, j + nn / 2, 1 );
	int ans4 = dp( n - 1, i, j, -1 ) + dp( n - 1, i + nn / 2, j, 0 ) + dp( n - 1, i, j + nn / 2, 1 ) + dp( n - 1, i +  nn / 2, j + nn / 2, -1 );
	int ans6 = dp( n - 1, i, j, -1 ) + dp( n - 1, i + nn / 2, j, 0 ) + dp( n - 1, i, j + nn / 2, -1 ) + dp( n - 1, i +  nn / 2, j + nn / 2, 1 );
	int ans7 = dp( n - 1, i, j, -1 ) + dp( n - 1, i + nn / 2, j, -1 ) + dp( n - 1, i, j + nn / 2, 0 ) + dp( n - 1, i +  nn / 2, j + nn / 2, 1 );
	int ans8 = dp( n - 1, i, j, 1 ) + dp( n - 1, i + nn / 2, j, 0 ) + dp( n - 1, i, j + nn / 2, -1 ) + dp( n - 1, i +  nn / 2, j + nn / 2, -1 );
	int ans9 = dp( n - 1, i, j, 1 ) + dp( n - 1, i + nn / 2, j, -1 ) + dp( n - 1, i, j + nn / 2, 0 ) + dp( n - 1, i +  nn / 2, j + nn / 2, -1 );
	int ans10 = dp( n - 1, i, j, 1 ) + dp( n - 1, i + nn / 2, j, -1 ) + dp( n - 1, i, j + nn / 2, -1 ) + dp( n - 1, i +  nn / 2, j + nn / 2, 0 );
	int ans11 = dp( n - 1, i, j, -1 ) + dp( n - 1, i + nn / 2, j, 1 ) + dp( n - 1, i, j + nn / 2, 0 ) + dp( n - 1, i +  nn / 2, j + nn / 2, -1 );
	int ans12 = dp( n - 1, i, j, -1 ) + dp( n - 1, i + nn / 2, j, 1 ) + dp( n - 1, i, j + nn / 2, -1 ) + dp( n - 1, i +  nn / 2, j + nn / 2, 0 );
	int ans13 = dp( n - 1, i, j, -1 ) + dp( n - 1, i + nn / 2, j, -1 ) + dp( n - 1, i, j + nn / 2, 1 ) + dp( n - 1, i +  nn / 2, j + nn / 2, 0 );
	
	if( ans1 < ans ) {
		ans = ans1;
		choice[ n ][ i ][ j ] = 1;
	}
	if( ans2 < ans ) {
		ans = ans2;
		choice[ n ][ i ][ j ] = 2;
	}
	if( ans3 < ans ) {
		ans = ans3;
		choice[ n ][ i ][ j ] = 3;
	}
	if( ans4 < ans ) {
		ans = ans4;
		choice[ n ][ i ][ j ] = 4;
	}
	if( ans6 < ans ) {
		ans = ans6;
		choice[ n ][ i ][ j ] = 6;
	}
	if( ans7 < ans ) {
		ans = ans7;
		choice[ n ][ i ][ j ] = 7;
	}
	if( ans8 < ans ) {
		ans = ans8;
		choice[ n ][ i ][ j ] = 8;
	}
	if( ans9 < ans ) {
		ans = ans9;
		choice[ n ][ i ][ j ] = 9;
	}
	if( ans10 < ans ) {
		ans = ans10;
		choice[ n ][ i ][ j ] = 10;
	}
	if( ans11 < ans ) {
		ans = ans11;
		choice[ n ][ i ][ j ] = 11;
	}
	if( ans12 < ans ) {
		ans = ans12;
		choice[ n ][ i ][ j ] = 12;
	}
	if( ans13 < ans ) {
		ans = ans13;
		choice[ n ][ i ][ j ] = 13;
	}
	return ans;
}

void paint( int x1, int y1, int x2, int y2, int col )
{
	for( int i = x1; i <= x2; i++ ) {
		for( int j = y1; j <= y2; j++ ) {
			sol[ i ][ j ] = col;
		}
	}
}

void make_sol( int n, int i, int j )
{
	if( n == 0 ) {
		sol[ i ][ j ] = A[ i ][ j ];
		return;
	}
	int nn = 1 << n;
	if( choice[ n ][ i ][ j ] == 1 ) {
		paint( i, j, i + nn / 2 - 1, j + nn / 2 - 1, 0 );
		paint( i + nn / 2, j, i + nn - 1, j + nn / 2 - 1, 1 );
		make_sol( n - 1, i, j + nn / 2 );
		make_sol( n - 1, i + nn / 2, j + nn / 2 );
	}
	else if( choice[ n ][ i ][ j ] == 2 ) {
		paint( i, j, i + nn / 2 - 1, j + nn / 2 - 1, 0 );
		make_sol( n - 1, i + nn / 2, j );
		paint( i, j + nn / 2, i + nn / 2 - 1, j + nn - 1, 1 );
		make_sol( n - 1, i + nn / 2, j + nn / 2 );
	}
	else if( choice[ n ][ i ][ j ] == 3 ) {
		paint( i, j, i + nn / 2 - 1, j + nn / 2 - 1, 0 );
		make_sol( n - 1, i + nn / 2, j );
		make_sol( n - 1, i, j + nn / 2 );
		paint( i + nn / 2, j + nn / 2, i + nn - 1, j + nn - 1, 1 );
	}
	else if( choice[ n ][ i ][ j ] == 4 ) {
		make_sol( n - 1, i, j );
		paint( i + nn / 2, j, i + nn - 1, j + nn / 2 - 1, 0 );
		paint( i, j + nn / 2, i + nn / 2 - 1, j + nn - 1, 1 );
		make_sol( n - 1, i + nn / 2, j + nn / 2 );
	}
	else if( choice[ n ][ i ][ j ] == 6 ) {
		make_sol( n - 1, i, j );
		paint( i + nn / 2, j, i + nn - 1, j + nn / 2 - 1, 0 );
		make_sol( n - 1, i, j + nn / 2 );
		paint( i + nn / 2, j + nn / 2, i + nn - 1, j + nn - 1, 1 );
	}
	else if( choice[ n ][ i ][ j ] == 7 ) {
		make_sol( n - 1, i, j );
		make_sol( n - 1, i + nn / 2, j );
		paint( i, j + nn / 2, i + nn / 2 - 1, j + nn - 1, 0 );
		paint( i + nn / 2, j + nn / 2, i + nn - 1, j + nn - 1, 1 );
	}
	else if( choice[ n ][ i ][ j ] == 8 ) {
		paint( i, j, i + nn / 2 - 1, j + nn / 2 - 1, 1 );
		paint( i + nn / 2, j, i + nn - 1, j + nn / 2 - 1, 0 );
		make_sol( n - 1, i, j + nn / 2 );
		make_sol( n - 1, i + nn / 2, j + nn / 2 );
	}
	else if( choice[ n ][ i ][ j ] == 9 ) {
		paint( i, j, i + nn / 2 - 1, j + nn / 2 - 1, 1 );
		make_sol( n - 1, i + nn / 2, j );
		paint( i, j + nn / 2, i + nn / 2 - 1, j + nn - 1, 0 );
		make_sol( n - 1, i + nn / 2, j + nn / 2 );
	}
	else if( choice[ n ][ i ][ j ] == 10 ) {
		paint( i, j, i + nn / 2 - 1, j + nn / 2 - 1, 1 );
		make_sol( n - 1, i + nn / 2, j );
		make_sol( n - 1, i, j + nn / 2 );
		paint( i + nn / 2, j + nn / 2, i + nn - 1, j + nn - 1, 0 );
	}
	else if( choice[ n ][ i ][ j ] == 11 ) {
		make_sol( n - 1, i, j );
		paint( i + nn / 2, j, i + nn - 1, j + nn / 2 - 1, 1 );
		paint( i, j + nn / 2, i + nn / 2 - 1, j + nn - 1, 0 );
		make_sol( n - 1, i + nn / 2, j + nn / 2 );
	}
	else if( choice[ n ][ i ][ j ] == 12 ) {
		make_sol( n - 1, i, j );
		paint( i + nn / 2, j, i + nn - 1, j + nn / 2 - 1, 1 );
		make_sol( n - 1, i, j + nn / 2 );
		paint( i + nn / 2, j + nn / 2, i + nn - 1, j + nn - 1, 0 );
	}
	else if( choice[ n ][ i ][ j ] == 13 ) {
		make_sol( n - 1, i, j );
		make_sol( n - 1, i + nn / 2, j );
		paint( i, j + nn / 2, i + nn / 2 - 1, j + nn - 1, 1 );
		paint( i + nn / 2, j + nn / 2, i + nn - 1, j + nn - 1, 0 );
	}
}

int main( void )
{
	int lg = 0;
	memset( memo, -1, sizeof( memo ) );
	scanf("%d", &N );
	for( int i = 1; i <= N; i++ ) {
		scanf("\n");
		for( int j = 1; j <= N; j++ ) {
			char c;
			scanf("%c", &c );
			A[ i ][ j ] = c - '0';
		}
	}
	while( 1 << lg < N ) lg++;
	precompute();
	printf("%d\n", dp( lg, 1, 1, -1 ) );
	make_sol( lg, 1, 1 );
	for( int i = 1; i <= N; i++ ) {
		for( int j = 1; j <= N; j++ ) {
			printf("%d", sol[ i ][ j ] );
		}
		printf("\n");	
	}
	return 0;
}
