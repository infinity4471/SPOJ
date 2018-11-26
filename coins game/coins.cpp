#include <cstdio>

int main(void)
{
        int N,K,L,q,dp[1000001];
        scanf("%d%d%d",&K,&L,&N);
        for(int i = 1; i<=1000000; i++) {
                dp[ i ] = false;
        }
        for(int i=1; i<=1000000; i++)
        {
                if( dp[ i - 1] == false || ( dp[ i - K ] == false && i - K >= 0 ) || ( dp[ i - L ] == false && i - L >= 0 ) ) {
                        dp[ i ] = true;
                }
        }
        for(int i=0; i<N; i++) {
                scanf("%d",&q);
                printf("%s",dp[q]?"A":"B");
        }
        printf("\n");
        return 0;
}
