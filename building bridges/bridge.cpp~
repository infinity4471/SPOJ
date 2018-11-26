#include <cstdio>  
#include <algorithm>  
  
#define INF 2010

using namespace std;  

int BIT[ INF + 1 ]; 

struct boat {  
    int x,y;  
};  

void init()
{
	for( int i = 0 ; i <= INF; i++ ) {
		BIT[ i ] = 0;
	}
}

void add(int idx,int val)
{
	while( idx <= INF ) {
		BIT[ idx ] = max(BIT[ idx ], val);
		idx += (idx & -idx);
	}
}
 
int findmax(int idx)
{
	int maxval = 0;
	while( idx > 0 ) {
		maxval = max(maxval,BIT[ idx ]);
		idx -= (idx & -idx);
	}
	return max(maxval,BIT[ 0 ]);
}

bool cmp(boat a,boat b)  
{  
    if(a.y==b.y) {  
        return a.x<b.x;  
    }  
    return a.y<b.y;  
}  
  
int main(void)  
{
    int T;
    scanf("%d", &T);
    while( T-- ) {
	    int N,ans=0;  
	    scanf("%d",&N); 
	    init(); 
	    boat boats[N];
	    int A[ N ],dp[ N ];
	    for(int i=0; i<N; i++) {  
		scanf("%d",&boats[i].x );
		boats[ i ].x += 1001;
	    }  
	    for( int i = 0; i < N; i++ ) {
		scanf("%d",&boats[ i ].y );
		boats[ i ].y += 1001;
	    }
	    sort(boats,boats+N,cmp);  
	    for(int i=0; i<N; i++) {  
		A[ i ] = boats[ i ].x;
	    }
	    for(int i = 0; i < N; i++ ) {
		dp[ i ] = 1 + findmax(A[ i ]);
		add(A[ i ],dp[ i ]);
	    }
	    for(int i=0; i<N; i++) {  
		ans=max(ans,dp[i]);
	    }  
	    printf("%d\n",ans);
    } 
    return 0;  
} 
