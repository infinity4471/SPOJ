#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;

int main(void)
{
	int T;
	scanf("%d",&T);
	while(T--) {
		char number[30];
		string num;
		scanf("%s",&number);
		for(int i=0; i<strlen(number); i++) {
			num+=number[i];
		}
		num+='a';
		int N=num.length(),prev=0;
		long long ans=1;
		for(int i=1; i<N; i++) {
			if(number[i]!=number[prev]) {
				ans*=pow(2,i-prev-1);
				prev=i;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
