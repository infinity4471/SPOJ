#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
	int N,W;
	while( 1 ) {
		cin >> W >> N;
		if(W==0 && N==0) break;
		int sack[N+1][W+1],val[N+1],cap[N+1],weight[N+1][W+1];
		for(int i=1; i<=N; i++)
			cin >> cap[i] >> val[i];
		for(int i=0; i<=N; i++) {
			weight[i][0]=0;
			sack[i][0]=0;
		}
		for(int i=0; i<=W; i++) {
			weight[0][i]=0;
			sack[0][i]=0;
		}
		for(int i=1; i<=N; i++) {
			for(int j=1; j<=W; j++) {
				if(j-cap[i]>=0) {
					if(sack[i-1][j]>=sack[i-1][j-cap[i]]+val[i]) {
						sack[i][j]=sack[i-1][j];
					} else {
						sack[i][j] = sack[i-1][j-cap[i]]+val[i];
					}
				}
				else {
					sack[i][j]=sack[i-1][j];
				}
			}
		}
		int max=0;
		for(int i=1; i<=W; i++) {
			if(sack[N][i]>sack[N][max]) {
				max=i;
			}
		}
		cout << max << " " << sack[N][W] << endl;
	}
	return 0;
}
