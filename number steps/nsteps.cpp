#include <iostream>
#include <algorithm>

using namespace std;

int explore(int x1,int y1)
{
	int x=0,y=0;
	int sum=0;
	if(x1==y1+2) {
		x=2;
		sum=2;
	} else if(x1==y1) {
		x=0;
		sum=0;
	}
	else {  return -1; }
	//cout << "starting position: <" << x << " , " << y << ">" << endl;
	for(int i=0; x!=x1 && y!=y1; i++) {
		if(i%2==0) {
			sum++;
			x++,y++;
		} else {
			sum+=3;
			x++,y++;
		}
	}
	return sum;
}

int main(void)
{
	int N,x,y;
	cin >> N;
	for(int i=0; i<N; i++) {
		cin >> x >> y;
		int ans=explore(x,y);
		if( ans == -1 ) cout << "No Number" << endl;
		else cout << ans << endl;
	}
	return 0;
}
