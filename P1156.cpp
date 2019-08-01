#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

const int G=110;
struct rub{
    int tim,hei,ful;
}r[G];

bool cmp(rub a,rub b){
    return a.tim<b.tim;
}

int dp[G][120];
int main(){
    memset(dp,0x80,sizeof dp);
    int d,g;
    scanf("%d %d",&d,&g);
    for(int i=1;i<=g;++i)   scanf("%d %d %d",&r[i].tim,&r[i].ful,&r[i].hei);
    for(int i=1;i<=g;++i){
        for(int j=0;j<=110;++j){
            if(j-r[i].hei>=0&&dp[i-1][j-r[i].hei]>=r[i].tim)    dp[i][j]=max(dp[i][j],)
        }
    }
    return 0;
}