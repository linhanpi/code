/*
 * @Author: watering_penguin 
 * @Date: 2023-03-02 15:41:42 
 * @Last Modified by: watering_penguin
 * @Last Modified time: 2023-03-11 14:33:10
 */
#include<bits/stdc++.h>
// #define int long long//信仰
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
const int N=2e3+5;
const int M=8e3+5;
const int mo=7000007;
const int inf=INT_MAX;
const int base=131;
const int mod=1e4+7;
const double eps=1e-6;
const double alpha=0.75;
const pii lpii={0,0};
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
struct SAM{
	int t[26],f,len;
	#define t(o,q,p,i) sam[o][q][p].t[i]
	#define f(o,q,p) sam[o][q][p].f
	#define len(o,q,p) sam[o][q][p].len
}sam[2][2][M];
int last[2],tot[2];
char s[N];
void insertsam(int q,int c){
	int p=last[q],np=++tot[q];last[q]=np;
	len(1,q,p)=len(1,q,p)+1;
	for(;p&&!t(1,q,p,c);p=f(1,q,p))t(1,q,p,c)=np;
	if(1,q,!p)f(1,q,np)=1;
	else{
		int v=t(1,q,p,c);
		if(1,q,len(1,q,v)==len(1,q,p)+1)f(1,q,np)=v;
		else{
			int nv=++tot[q];
			sam[1][q][nv]=sam[1][q][v];
			len(1,q,nv)=len(1,q,p)+1;
			for(;p&&t(1,q,p,c)==v;p=f(1,q,p))t(1,q,p,c)=nv;
			f(1,q,np)=f(1,q,v)=nv;
		}
	}
	return ;
}
int n;
void zxlzdj(int q){
	for(int i=n;i;i--){
		sam[0][q][i-1]=sam[0][q][i];
		t(0,q,i-1,s[i]-'a')=i;
	}
	return ;
}
bool vis[N<<1][N<<1];
struct node{
	int a,b,c;
};
void bfs(int f1,int f2) {
	memset(vis,0,sizeof(vis));
	queue<node> q;
	q.push({f1,f2,0});
	vis[f1][f2]=1;
	while(!q.empty()){
		node now=q.front();
		q.pop();
		for(int i=0;i<26;i++){
			if(t(f1,0,now.a,i)) {
				if(t(f2,1,now.b,i)) {
					int a=t(f1,0,now.a,i),b=t(f2,1,now.b,i);
					if(!vis[a][b]){
						vis[a][b]=1;
						q.push({a,b,now.c+1});
					}
				}
				else{
					cout<<now.c+1<<endl;
					return ;
				}
			}
		}
	}
	puts("-1");
	return ;
}
signed main(){
	last[0]=last[1]=tot[0]=tot[1]=1;
	scanf("%s",s+1);
	n=strlen(s+1);
	zxlzdj(0);
	for(int i=1;i<=n;i++){
		insertsam(0,s[i]-'a');
	}
	scanf("%s",s+1);
	n=strlen(s+1);
	zxlzdj(1);
	for(int i=1;i<=n;i++){
		insertsam(1,s[i]-'a');
	}
	bfs(1,1);
	bfs(1,0);
	bfs(0,1);
	bfs(0,0);
	return 0;
}
