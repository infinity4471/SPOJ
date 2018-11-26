#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
 
using namespace std;
 
int ans;
int num[30001];
 
void merge(int p,int q,int r,int N)
{
	queue<int> q1,q2,q3;
	for(int i=p; i<=q; i++) q1.push(num[i]);
	for(int i=q+1; i<=r && i<N; i++) q2.push(num[i]);
	while(!q1.empty() && !q2.empty()) {
		if(q1.front()<=q2.front()) {
			q3.push(q1.front());
			q1.pop();
		} else {
			ans+=q1.size();
			q3.push(q2.front());
			q2.pop();
		}
	}
	while(!q1.empty()) {
		q3.push(q1.front());
		q1.pop();
	}
	while(!q2.empty()) {
		q3.push(q2.front());
		q2.pop();
	}
	int i=p;
	while(!q3.empty()) {
		num[i++]=q3.front();
		q3.pop();
	}
}
 
void mergesort(int p,int q,int N)
{
	if(p<q) {
		int mid=(p+q)/2;
		mergesort(p,mid,N);
		mergesort(mid+1,q,N);
		merge(p,mid,q,N);
	}
}
int main(void)
{
	int T;
	scanf("%d",&T);
	for(int k=0; k<T; k++) {
		int N;
		ans=0;
		scanf("%d",&N);
		string original[N],yoda[N];
		map<string, int> bitmap;
		for(int i=0; i<N; i++) {
			char test[20];
			scanf("%s",&test);
			for(int j=0; j<strlen(test); j++) {
				yoda[i]+=test[j];
			}
		}
		for(int i=0; i<N; i++) {
			char test[20];
			scanf("%s",&test);
			for(int j=0; j<strlen(test); j++) {
				original[i]+=test[j];
			}
			bitmap[original[i]]=i+1;
			//cout << "bitmap[" << original[i] << "]=" << i+1 << endl;
		}
		for(int i=0; i<N; i++) {
			num[i]=bitmap[yoda[i]];
			//printf("num[%d]=%d\n",i,num[i]);
		}
		mergesort(0,N-1,N);
		printf("%d\n",ans);
		for(int i=0; i<N; i++) {
			num[i]=0;
		}
	}
	return 0;
}
