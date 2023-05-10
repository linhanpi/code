#include<bits/stdc++.h>
// #define int long long
#define double long double
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
const int M=105;
const int mod=998244353;
const int inf=1e9+1;
const int base=2e9+7;
const double down=0.996;
#define ra() (rand()*2-RAND_MAX)
int n;
struct node{
    int x,y,w;
}no[N];
double ansx,ansy,answ;
double en(double x,double y){
    double res=0;
    for(int i=1;i<=n;i++){
        double dx=x-no[i].x;
        double dy=y-no[i].y;
        res+=sqrt(dx*dx+dy*dy)*no[i].w;
    }
    return res;
}
void th(){
    double t=3000;
    while(t>1e-15){
        double ex=ansx+(rand()*2-RAND_MAX)*t;
        double ey=ansy+(rand()*2-RAND_MAX)*t;
        double ew=en(ex,ey);
        double cha=ew-answ;
        if(cha<0){
            ansx=ex,ansy=ey,answ=ew;
        }
        else if(exp(-cha/t)*RAND_MAX>rand()){
            ansx=ex,ansy=ey;
        }
        t*=down;
    }
    return ;
}
void solve(){
    th();
    th();
    th();
    th();
    return ;
}
signed main(){
	n=read();
    for(int i=1;i<=n;i++){
        no[i].x=read(),no[i].y=read(),no[i].w=read();
        ansx+=no[i].x,ansy+=no[i].y;
    }
    ansx/=n,ansy/=n;
    answ=en(ansx,ansy);
    solve();
    cout<<fixed<<setprecision(3)<<ansx<<" "<<ansy<<endl;
    return 0;
}