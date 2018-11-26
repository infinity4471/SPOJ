#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

map< int,bool > used;

int breakit(int num)
{
	int result = 0;
	while( num > 0 ) {
		result += (num%10)*(num%10);
		num /= 10;
	}
	if( used[ result ] ) {
		return -1;
	} else {
		return result;
	}
}

int main( void )
{
	int N,cnt=0;
	scanf("%d",&N);
	//printf("%d\n",N);
	while( N != 1 ) {
		int num = breakit(N);
		if( num == -1 ) {
			printf("%d\n",num);
			return 0;
		}
		used[ num ] = true;
		N = num;
		cnt++;
	}
	printf("%d\n",cnt);
	return 0;
}
