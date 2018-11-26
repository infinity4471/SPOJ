#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <functional>

using namespace std;

struct node {
	int l,r;
	int maxim;
	int right,left;
};

node tree[2500000];
vector<int> keys;
int maxi=0;

void built_tree(int i,int start,int end)
{
	if(i>maxi) {
		maxi=i;
		//cout << maxi << endl;
	}
	if(start==end) {
		tree[i].l=tree[i].r=start;
		tree[i].left=-1;
		tree[i].right=-1;
		tree[i].maxim=keys[start];
		return;
	}
	int mid=(start+end)/2;
	tree[i].l=start;
	tree[i].r=end;
	tree[i].right=2*i+1;
	tree[i].left=2*i;
	built_tree(tree[i].left,start,mid);
	built_tree(tree[i].right,mid+1,end);
	tree[i].maxim=max(tree[tree[i].left].maxim,tree[tree[i].right].maxim);
	//cout << "tree[" << i << "] = (" << tree[i].l << " , " << tree[i].r << ") " << endl;
}

int query(int node,int i,int j)
{
	//cout << "tree[" << node << "] = ( " << tree[node].l << " , " << tree[node].r << " ) " << endl;
	if(tree[node].l>=i && tree[node].r<=j) {
		return tree[node].maxim;
	}
	if(tree[tree[node].left].r>=j) {
		return query(tree[node].left,i,j);
	}
	else if(tree[tree[node].right].l<=i) {
		return query(tree[node].right,i,j);
	}
	else if(tree[tree[node].left].r>=i && tree[tree[node].right].l<=j) {
		return max(query(tree[node].left,i,tree[tree[node].left].r), query(tree[node].right,tree[tree[node].right].l,j) );
	}
}

int main(void)
{
	//freopen("sub.in","rt",stdin);
	//freopen("sub.out","wt",stdout);
	int N,K,d;
	scanf("%d",&N);
	keys.push_back(-1);
	for(int i=0; i<N; i++) {
		scanf("%d",&d);
		keys.push_back(d);
	}
	scanf("%d",&K);
	built_tree(1,1,N);
	//cout << maxi << endl;
	//cout << "searching for max in diastema: 2,4" << endl;
	for(int i=1; i<=N-K+1; i++) {
		int max=0;
		//cout << "querying diastema: " << i << " , " << i+K << endl;
		max=query(1,i,i+K-1);
		printf("%d ",max);
	}
	printf("\n");
	return 0;
}
