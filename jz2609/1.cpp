#include<cstdio>
#include<cstring>
#include<string>

using namespace std;

#define max(a,b)    (a>b?a:b)
// struct BNum{
//     int va[110];
//     BNum(){memset(va,0,sizeof(va));}
//     BNum(int val):BNum(){
//         while(val){
//             va[++va[0]]=val%10;
//             val/=10;
//         }
//     }   
//     BNum(string val):BNum(){
//         va[0]=val.length();
//         for(int i=1;i<=va[0];++i)   va[i]=val[va[0]-i]-'0';
//     }
//     void operator += (BNum b){
//         va[0]=max(va[0],b.va[0]);
//         for(int i=1;i<=va[0];++i){
//             va[i]+=b.va[i];
//             if(va[i]>9) va[i]-=10,va[i+1]++;
//         }
//         if(va[va[0]+1]) ++va[0];
//     }
//     void operator *= (BNum b){
//         // va[0]=va[0]+b.va[0]-1;
//         BNum tmp(*this);
//         memset(va,0,sizeof(va));
//         for(int i=1;i<=b.va[0];++i){
//             for(int j=1;j<=tmp.va[0];++j){
//                 va[i+j-1]+=b.va[i]*tmp.va[j];
//                 va[i+j]+=va[i+j-1]/10;
//                 va[i+j-1]%=10;
//             }
//         }
//         va[0]=tmp.va[0]+b.va[0]-1;
//         while(va[va[0]+1])    ++va[0];
//     }
//     void print(){
//         for(int i=va[0];i;--i)  putchar('0'+va[i]);
//     }
// };

// BNum lis[103];

long long lis[40];
int main(){
    freopen("recruitment.in","r",stdin);
    freopen("recruitment.out","w",stdout);
    int n,k;
    long long ans;

    lis[0]=1;
    for(int i=1;i<=35;++i){
        lis[i]+=lis[i-1];
        lis[i]*=3;
    }

    scanf("%d",&n);
    int j;
    for(int i=0;i<n;++i){
        // memset(ans.va,0,sizeof(ans.va));
        ans=0;
        scanf("%d",&k);
        j=0;
        while(k){
            if(k&1) ans += lis[j];
            ++j,k>>=1;
            // ans.print();1
        }
        printf("%lld\n",ans);
        // putchar('\n');
    }
    return 0;
}