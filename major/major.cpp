#include <cstdio>
#include <algorithm>
#include <map>

using namespace std;

int main(void)
{
	int T;
	scanf("%d",&T);
	for(int k=0; k<T; k++) {
		int N;
		map<signed int, int > m;
		scanf("%d",&N);
		int A[N];
		bool status=false;
		int req=0;
		for(int i=0; i<N; i++) {
			scanf("%d",&A[i]);
			m[A[i]]++;
		}
		for(int i=0; i<N; i++) {
			if(2*m[A[i]]>N) {
				status=true;
				req=A[i];
			}
		}
		if(status) {
			printf("YES %d\n",req);
		} else printf("NO\n");
	}
	return 0;
}
