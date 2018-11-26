#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <stack>
#include <algorithm>

#define MAX 100000

using namespace std;

struct trie {
	int digits[10];
};

int nodecnt;
struct trie tree[MAX+1];

void init()
{
	for(int i=1; i<=MAX; i++) {
		for(int j=0; j<=9; j++) {
			tree[i].digits[j]=0;
		}
	}
	nodecnt=1;
}

void add(char number[])
{
	int node,current=1;
	for(int i=0; i<strlen(number); i++) {
		node=tree[current].digits[number[i]-'0'];
		if( !node ) {
			//cout << "there is no: " << s.top() << " accessible from node: " << current << endl;
			nodecnt++;
			tree[current].digits[number[i]-'0']=nodecnt;
			current=nodecnt;
		}
		else {
			current=node;
		}
	}
}

bool find(char number[])
{
	int node,current=1;
	for(int i=0; i<strlen(number); i++) {
		node=tree[current].digits[number[i]-'0'];
		//cout << "moving to: " << node << " with digit value= " << s.top() << endl;
		if( !node ) {
			//cout << "number: " << tmpnum << " has not bee added to trie!" << endl;
			return false;
		}
		current=node;
	}
	for(int i=0; i<10; i++) {
		if(tree[current].digits[i]) {
			return true;
		}
	}
	return false;
}

int main(void)
{
	int T;
	scanf("%d",&T);
	for(int k=0; k<T; k++) {
		int N;
		bool status=true;
		scanf("%d",&N);
		char array[N][10];
		init();
		for(int i=0; i<N; i++) {
			scanf("%s",&array[i]);
			add(array[i]);
		}
		for(int i=0; i<N; i++) {
			//cout << "trying to find: " << array[i] << " at trie!" << endl;
			if(find(array[i])) {
				//cout << "found " << array[i] << " or a part of it" << endl;
				status=false;
			}
		}
		printf("%s\n",status?"YES":"NO");
	}
	return 0;
}
