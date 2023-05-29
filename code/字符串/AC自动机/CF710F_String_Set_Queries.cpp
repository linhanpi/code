#include<bits/stdc++.h>
#define int long long//信仰
#define pii pair <int,int>
#define lowbit(x) (-x&x)
#define lson (p<<1)
#define rson (p<<1|1)
using namespace std;
#define read() (red<int>())
template<typename T>inline T red() {
    T x=0;
    bool f=false;
    char c=getchar();
    while(c<'0'||c>'9') {
        if(c=='-')f=true;
        c=getchar();
    }
    while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();
   return f?-x:x;
}
template<typename T>inline void write(T x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x/10) write(x/10);
    putchar((x%10)^48);
    return;
}
const int N=1e6+5;
const int inf=INT_MAX;
mt19937 rnd(time(0));
#define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
#define ran_real(l,r) uniform_real_distribution<double>(l,r)(rnd)
#define ra (inf-rnd())
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){
    int ans=1;
    x%=mod;
    while(y){
        if(y&1)ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
inline int fang(int x) {return x*x;}
struct zdj{
    int t[26],ne[26],f,sum,ed;
    #define t(p,c) acam[p].t[c]
    #define ne(p,c) acam[p].ne[c]
    #define f(p) acam[p].f
    #define sum(p) acam[p].sum
    #define ed(p) acam[p].ed
}acam[N];
int tot;
void insert(string s,int k,int rt){
    int p=rt;
    for(int i=0;i<s.size();i++){
        int ne=s[i]-'a';
        if(!t(p,ne))t(p,ne)=++tot;
        p=t(p,ne);
    }
    ed(p)+=k;
    return ;
}
void bd(int rt){
    queue <int> q;
    f(rt)=rt;
    for(int i=0;i<26;i++){
        if(t(rt,i)){
            ne(rt,i)=t(rt,i);
            f(ne(rt,i))=rt;
            q.push(ne(rt,i));
        }
        else ne(rt,i)=rt;
    }
    while(!q.empty()){
        int now=q.front();
        q.pop();
        sum(now)=sum(f(now))+ed(now);
        for(int i=0;i<26;i++){
            if(t(now,i)){
                ne(now,i)=t(now,i);
                f(ne(now,i))=ne(f(now),i);
                q.push(ne(now,i));
            }
            else ne(now,i)=ne(f(now),i);
        }
    }
    return ;
}
int hb(int p,int q){
    if(!p||!q)return p+q;
    ed(p)+=ed(q);
    for(int i=0;i<26;i++)t(p,i)=hb(t(p,i),t(q,i));
    return p;
}
int root[N],si[N],cnt;
void gai(string s,int k){
    root[++cnt]=++tot;
    si[cnt]=1;
    insert(s,k,root[cnt]);
    while(si[cnt]==si[cnt-1]){
        cnt--;
        si[cnt]+=si[cnt+1];
        root[cnt]=hb(root[cnt],root[cnt+1]);
    }
    bd(root[cnt]);
    return ;
}
int cha(string s,int rt){
    int p=rt,res=0;
    for(int i=0;i<s.size();i++){
        int c=s[i]-'a';
        p=ne(p,c);
        res+=sum(p);
    }
    return res;
}
signed main(){
    int q=read();
    while(q--){
        int op=read();
        string s;cin>>s;
        if(op==1)gai(s,1);
        if(op==2)gai(s,-1);
        if(op==3){
            int res=0;
            for(int i=1;i<=cnt;i++)res+=cha(s,root[i]);
            cout<<res<<endl;
            fflush(stdout);
        }
    }
    return 0;
}