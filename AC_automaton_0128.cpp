#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

#define max(x,y)    (x>y?x:y)

struct nod{
    char va;bool nu;
    int ap;nod *g;
    nod *ch,*ne,*fail,*fa;
    nod(char _va);
    ~nod();
    nod* add(char _va);
    nod* find(char _va);
    void init();
}Troot(0),*root=&Troot;

nod::nod(char _va):va(_va),nu(false),ap(0){
    ch=ne=NULL,g=fail=root;
}

nod::~nod(){
    if(ch!=NULL)    delete ch;
    if(ne!=NULL)    delete ne;
}

nod* nod::add(char _va){
    nod *tmp=ch;
    while(tmp!=NULL&&tmp->va!=_va)  tmp=tmp->ne;
    if(tmp!=NULL)   return tmp;
    (tmp=new nod(_va))->ne=ch;
    (ch=tmp)->fa=this;
    return ch;
}

nod* nod::find(char _va){
    nod *tmp=ch;
    while(tmp!=NULL&&tmp->va!=_va)  tmp=tmp->ne;
    return tmp;
}

queue<nod*> li;
void nod::init(){
    nod *tmp=fail,*ca;
    for(nod *now=ch;now!=NULL;now=now->ne){
        tmp=fail;
        while(tmp!=NULL&&(ca=tmp->find(now->va))==NULL)    tmp=tmp->fail;
        if(tmp!=NULL)    now->fail=now->g=ca;
        li.push(now);
    }
}

char in[1001000];
vector<char> lis;
vector<nod*> can;
int main(){
    root->fail=NULL;
    int n;
    char tmp;
    nod *now,*ca;
    while(scanf("%d",&n),n){
        delete root->ch;
        lis.clear();
        root->ch=NULL;
        while(n--){
            while((tmp=getchar())<=32);
            now=root;
            do{
                now=now->add(tmp);
            }while((tmp=getchar())>32);
            now->nu=true;
            can.push_back(now);
        }
        li.push(root);
        while(li.size()){
            li.front()->init();
            li.pop();
        }
        scanf("%s",in);
        now=root;
        int ans=0;
        for(int i=0;in[i];++i){
            while(now!=NULL&&(ca=now->find(in[i]))==NULL)   now=now->fail;
            if(ca!=NULL)    now=ca;
            else now=root;
            if(now->nu) now->ap++,ans=max(ans,now->ap);
            ca=now;
            while(ca->g!=root){
                if(ca->g->nu){
                    ca->g->ap++;
                    ans=max(ans,ca->g->ap);
                    ca=ca->g;
                }else ca->g=ca->g->fail;
            }
        }
        printf("%d",ans);
        for(int i=can.size()-1;i>=0;--i){
            nod *t=can[i];
            if(t->ap!=ans)  continue;
            while(t!=root){
                lis.push_back(t->va);
                t=t->fa;
            }
            lis.push_back('\n');
        }
        can.clear();
        for(int i=lis.size()-1;i>=0;--i)    putchar(lis[i]);
        putchar('\n');
    }
    return 0;
}