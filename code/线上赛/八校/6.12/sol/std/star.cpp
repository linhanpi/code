#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3005;
const double eps=1e-12,inf=1e100;
int read(){
	int f=1,g=0;
	char ch=getchar();
	for (;!isdigit(ch);ch=getchar()) if (ch=='-') f=-1;
	for (;isdigit(ch);ch=getchar()) g=g*10+ch-'0';
	return f*g;
}
int T,n,cnt[3];
struct vec{
	int x,y;
	vec(int _x=0,int _y=0){x=_x;y=_y;}
}a[3][N],c[3][N];
vec operator+(vec a,vec b){return (vec){a.x+b.x,a.y+b.y};}
vec operator-(vec a,vec b){return (vec){a.x-b.x,a.y-b.y};}
vec operator*(vec a,int k){return (vec){a.x*k,a.y*k};}
vec operator/(vec a,int k){return (vec){a.x/k,a.y/k};}
ll operator^(vec a,vec b){return (ll)a.x*b.y-(ll)a.y*b.x;}
ll operator&(vec a,vec b){return (ll)a.x*b.x+(ll)a.y*b.y;}
bool cmp(vec a,vec b){return (a.x!=b.x) ? (a.x<b.x) : (a.y<b.y);}
bool side(vec a,vec b,vec c){return ((b-a)^(c-a))>=0;}
ll len(vec a){return (ll)a.x*a.x+(ll)a.y*a.y;}
bool operator==(vec a,vec b){return (a.x==b.x)&&(a.y==b.y);}
ll area(vec a,vec b,vec c){return (b-a)^(c-a);}

int getconvex(vec *a,int n,vec *c){
	int cnt=-1;
	sort(a+1,a+n+1,cmp);
	n=unique(a+1,a+n+1)-a-1;
	for (int i=1;i<=n;i++){
		vec cur=a[i];
		while ((cnt>0)&&side(c[cnt-1],c[cnt],cur)) cnt--;
		c[++cnt]=cur;
	}
	int las=cnt;
	for (int i=n-1;i;i--){
		vec cur=a[i];
		while ((cnt>las)&&side(c[cnt-1],c[cnt],cur)) cnt--;
		c[++cnt]=cur;
	}
	if (n==1) c[++cnt]=a[1];
	return cnt;
}
void chkmax(ll &x,ll y){if (x<y) x=y;}
int main(){
	freopen("star.in","r",stdin);
	freopen("star.out","w",stdout);
	T=read();
	while (T--){
		n=read();
		cnt[0]=cnt[1]=cnt[2]=0;
		for (int i=1;i<=n;i++){
			int x=read(),y=read(),c=read();
			a[c][++cnt[c]]=vec(x,y);
		}
		for (int i=0;i<3;i++)
		cnt[i]=getconvex(a[i],cnt[i],c[i]);
		for (int i=0;i<2;i++)
		for (int j=i+1;j<3;j++)
		if (cnt[i]>cnt[j]){swap(cnt[i],cnt[j]);swap(c[i],c[j]);}
		ll ans=0;
		
		for (int cen=0;cen<cnt[0];cen++){
			int i=0,l=0,r=0;
			vec cur=c[0][cen],v=c[1][i];
			for (int j=0;j<cnt[2];j++){
				if (area(cur,v,c[2][j])>area(cur,v,c[2][l])) l=j;
				if (area(cur,c[2][j],v)>area(cur,c[2][r],v)) r=j;
			}
			chkmax(ans,area(cur,v,c[2][l]));
			chkmax(ans,area(cur,c[2][r],v));
			for (i=1;i<cnt[1];i++){
				int d=side(cur,v,c[1][i]) ? (cnt[2]-1) : 1;
				v=c[1][i];
				while (area(cur,v,c[2][(l+d)%cnt[2]])>area(cur,v,c[2][l])) l=(l+d)%cnt[2];
				while (area(cur,c[2][(r+d)%cnt[2]],v)>area(cur,c[2][r],v)) r=(r+d)%cnt[2];
				chkmax(ans,area(cur,v,c[2][l]));
				chkmax(ans,area(cur,c[2][r],v));
			}
		}
		printf("%lld.%d\n",ans/2,(ans&1)?5:0);
	}
	return 0;
}
