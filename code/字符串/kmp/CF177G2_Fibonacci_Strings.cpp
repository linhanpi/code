#include<bits/stdc++.h>
#define int long long//信仰
// #define uint unsigned int
// #define rint register int
// #define ll long long
// #define double long double
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
const int M=1e2+5;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+7;
const double eps=1e-6;
const double alpha=0.75;
const pii lpii={0,0};
const double MAX_TIME=0.8;
const double Down=0.996;
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
struct node{
    int a[2][2];
    node(){
        memset(a,0,sizeof(a));
    }
}A,B;
node operator *(const node &x,const node &y){
    node c;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                c.a[i][j]=(c.a[i][j]+x.a[i][k]*y.a[k][j]%mod)%mod;
            }
        }
    }
    return c;
}
char s[N];
int ne[N],f[N];
string fs[N];
int len,ci;
inline int gs(string t){
    int res=0;
    for(int i=0,j=0;i<t.size();i++){
        while(j&&s[j+1]!=t[i])j=ne[j];
        j+=(s[j+1]==t[i]);
        if(j==len)++res;
    }
    return res;
}
inline void qsm(int y){
    while(y){
        if(y&1)A=A*B;
        B=B*B;
        y>>=1;
    }
    return ;
}
signed main(){
	int n=read(),m=read();
    while(m--){
        scanf("%s",s+1);
        len=strlen(s+1);
        for(int i=2,j=0;i<=len;i++){
            while(j&&s[j+1]!=s[i])j=ne[j];
            j+=(s[j+1]==s[i]);
            ne[i]=j;
        }
        f[1]=f[2]=1;
        fs[1]="a",fs[2]="b";
        for(int i=3;;i++){
            if(f[i-2]>len){
                fs[i]=fs[i-1]+fs[i-2];
                ci=i-1;
                break;
            }
            f[i]=f[i-1]+f[i-2];
            fs[i]=fs[i-1]+fs[i-2];
        }
        string a,b,c;
        for(int i=0;i<len-1;i++)a+=fs[ci-1][i];
        for(int i=fs[ci-1].size()-(len-1);i<fs[ci-1].size();i++)b+=fs[ci-1][i];
        for(int i=fs[ci].size()-(len-1);i<fs[ci].size();i++)c+=fs[ci][i];
        int vb=gs(b+a),vc=gs(c+a);
        if(n-ci<=1){
            cout<<gs(fs[n])<<endl;
            continue;
        }
        A.a[0][0]=0,A.a[0][1]=1;
        memset(B.a,0,sizeof(B.a));
        B.a[0][1]=B.a[1][0]=B.a[1][1]=1;
        int y=n-ci;
        qsm(y);
        int Bs=A.a[0][0]-(y%2==1);

        A.a[0][0]=0,A.a[0][1]=1;
        memset(B.a,0,sizeof(B.a));
        B.a[0][1]=B.a[1][0]=B.a[1][1]=1;
        qsm(y-1);
        int Cs=A.a[0][0]-((y-1)%2==1);

        A.a[0][0]=gs(fs[ci]),A.a[0][1]=gs(fs[ci+1]);
        memset(B.a,0,sizeof(B.a));
        B.a[0][1]=B.a[1][0]=B.a[1][1]=1;
        qsm(y);
        int As=A.a[0][0];
        // cout<<As<<endl;
        cout<<(As+Bs*vb%mod+Cs*vc%mod)%mod<<endl;
    }
	return 0;
}
