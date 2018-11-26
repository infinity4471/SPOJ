#include <cstdio>
#include <algorithm>
 
#define MAX 100000
 
using namespace std;

int num[4*MAX+1];
bool flag[4*MAX+1];

void init(int i,int b,int e)
{
	if(b==e) {
		flag[i]=false;
		num[i]=0;
		return;
	}
	init( 2*i,b,(b+e)/2 );
	init( 2*i+1,(b+e)/2 + 1, e );
	flag[i]=false;
	num[i]=0;
}

void refresh(int i,int b,int e)
{
	if( flag[i] ) {
		num[i]= e - b + 1 - num[i];
		flag[i]= false;
		if(b!=e) {
			flag[2*i] = !flag[2*i];
			flag[2*i+1] = !flag[2*i+1];
		}
	}
}

int query(int i,int b,int e,int l,int r)
{
	if(b>r || e<l) {
		return 0;
	}
	refresh(i,b,e);
	if(l<=b && e<=r) {
		return num[i];
	}
	else {
		int mid=(b+e)/2;
		return query(2*i,b,mid,l,r) + query(2*i+1,mid+1,e,l,r);
	}
}

void update(int i,int b,int e,int l,int r)
{
	if(b>r || e<l) {
		refresh(i,b,e);
	}
	else if(l<=b && e<=r) {
		flag[i] = !flag[i];
		refresh(i,b,e);
	}
	else {
		refresh(i,b,e);
		int mid=(b+e)/2;
		update(2*i,b,mid,l,r);
		update(2*i+1,mid+1,e,l,r);
		if(b!=e) {
			num[i]=num[2*i] + num[2*i+1];
		}
	}
}

int main(void)
{
	int M,N;
	scanf("%d%d",&N,&M);
	int u,v,w;
	init(1,1,N);
	for(int i=0; i<M; i++) {
		scanf("%d%d%d",&u,&v,&w);
		if(u==0) {
			update(1,1,N,v,w);
		} else {
			printf("%d\n", query(1,1,N,v,w) );	
		}
	}
	return 0;
}
