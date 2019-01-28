#include<cstdio>
using namespace std;

const int N=100;
char str[N],mod[N];
int nx[N];
int main(){
    scanf("%s",str+1);
    scanf("%s",mod+1);
    int j,ans=0;nx[0]=nx[1]=0;
    for(int i=2;mod[i];++i){
        j=nx[i-1];
        while(j&&mod[j+1]!=mod[i]) j=nx[j];
        nx[i]=j+(mod[j+1]==mod[i]);
    }
    j=0;
    for(int i=1;str[i];++i){
        while(j&&mod[j+1]!=str[i])    j=nx[j];
        if(!mod[1+(j+=(mod[j+1]==str[i]))]&&j){++ans,j=nx[j];}
    }
    ans+=(j&&!mod[j+1]);
    printf("%d",ans);
    return 0;
}