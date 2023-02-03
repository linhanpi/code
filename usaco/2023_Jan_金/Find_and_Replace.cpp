#include<bits/stdc++.h>
#define int long long
//#define double long double
//#define pii pair <int,int>
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
const int N=2e5+5;
const int M=(1<<12);
const int mo=7000007;
const int inf=1e9+7;
const int base=131;
const int mod3=998244353;
const int mod2=998244352;
const int phi2=3<<27;
inline int qmi(int x,int y,int mod){
    int ans=1;
    while(y){
        if(y&1)ans=ans*x%mod;
        x=x*x%mod;
        y>>=1;
    }
    return ans;
}
inline int dc1(int x) {return x*(x+1)/2;}
inline int dc2(int x) {return x*(x+1)*(x+x+1)/6;}
char a[N];
int len[N];
char ansl,ansr;
int tot;
vector <char> ans;
string b[N];
int chang[N][26];
signed main(){
    int l=read(),r=read(),m=read();
    for(int i=1;i<=m;i++){
        cin>>a[i]>>b[i];
        len[i]=b[i].size();
    }
    ans.push_back('a');
    for(int i=1;i<=m;i++){
        if(len[i]==1){
            for(int j=0;j<(int)ans.size();j++){
                if(ans[j]==a[i]){
                    ans[j]=b[i][0];
                }
            }
            continue;
        }
        for(int j=0;j<(int)ans.size();j){
            if(ans[j]==a[i]){
                ans.erase(ans.begin()+j);
                for(int k=0;k<len[i];k++,j++){
                    ans.insert(ans.begin()+j,b[i][k]);
                }
            }
            else j++;
        }
    }
    for(int i=l-1;i<=r-1;i++){
        cout<<ans[i];
    }
    return 0;
}
/*
3 8 4
a ab
a bc
c de
b bbb
*/