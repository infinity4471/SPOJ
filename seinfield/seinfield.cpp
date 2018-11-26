#include <cstdio>
#include <cstring>
#include <stack>

using namespace std;

int main(void)
{
	int cnt=1;
	while( true ) {
		char str[2001];
		int op=0,cl=0;
		scanf("%s",&str);
		if( str[ 0 ] == '-' ) {
			break;
		}
		stack<char> s;
		for(int i=0; i<strlen(str); i++) {
			if(str[i]=='{') {
				s.push('{');
			}
			else if(str[i]=='}' && !s.empty() && s.top()=='{' ) {
				s.pop();
			}
			else  {
				s.push('}');
			}
		}
		while(!s.empty() ) {
			if(s.top() == '}') {
				cl++;
			}
			else if(s.top() == '{' ) {
				op++;
			}
			s.pop();
		}
		//printf("%d %d\n",op,cl);
		if(cl % 2 != 0) cl++;
		if(op % 2 != 0) op++;
		printf("%d. %d\n", cnt++, (op + cl) / 2);
	}
	return 0;
}
