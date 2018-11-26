#include <cstdio>
#include <cstring>

using namespace std;

int main(void)
{
	while( true ) {
		int N,multi=0;
		char str[100001];
		scanf("%s",&str);
		if( !strcmp(str,"*") ) {
			break;
		}
		N=strlen(str);;
		int ans=1;
		int mult[N+1];
		for(int i=1; i<=N; i++) {
			if(N % i == 0) {
				mult[multi++] = i;
			}
		}
		for(int i=0; i<multi; i++) {
			bool status=true;
			for(int j=0; j<N-mult[i]; j++) {
				if(str[j] != str[j + mult[i]]) {
					status=false;
				}
			}
			if(status) {
				ans=mult[i];
				break;
			}
		}
		printf("%d\n",N / ans);
	}
	return 0;
}
