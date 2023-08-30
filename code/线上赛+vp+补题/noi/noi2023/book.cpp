#include<bits/stdc++.h>
#define int long long//信仰
#define ld long double
#define uint unsigned long long
// #define uint unsigned int
// #define rint register int
// #define int long long
// #define double long double
#define pii pair <int,int>
#define lowbit(x) (-x&x)
#define lson (p<<1)
#define rson (p<<1|1)
using namespace std;
#define read() (red<int>())
template<typename T>inline T red(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=100+5;
const int M=1e2+5;
const int bzt=18;
const int inf=INT_MAX;
const int base=131;
const int mod=1e9+7;
const ld eps=1e-6;
const ld alpha=0.75;
const pii lpii={0,0};
const ld MAX_TIME=0.8;
const ld Down=0.996;
// mt19937 rnd(time(0));
// #define ran_int(l,r) uniform_int_distribution<int>(l,r)(rnd)
// #define ran_real(l,r) uniform_real_distribution<ld>(l,r)(rnd)
int mgcd(int x,int y){return x==0?y:mgcd(y%x,x);}
int mlcm(int x,int y){return x/mgcd(x,y)*y;}
inline int qmi(int x,int y,int mod){int ans=1;x%=mod;while(y){if(y&1)ans=ans*x%mod;x=x*x%mod;y>>=1;}return ans;}
inline int fang(int x){return x*x;}
inline int mjia(int x,int y){return (x+y)%mod;}
inline int mjian(int x,int y){return (x-y+mod)%mod;}
inline int mcheng(int x,int y){return (x*y)%mod;}
inline int mchu(int x,int y){return x*qmi(y,mod-2,mod)%mod;}
inline bool dengyu(ld x,ld y){return abs(x-y)<=eps;}
inline bool dayu(ld x,ld y){return x>eps+y;}
inline bool xiaoyu(ld x,ld y){return y>eps+x;}

int n, w[N];
map<vector<int>, pii> f[N];
void mian() {
  cin >> n;
  for(int i = 0; i < n; i++) cin >> w[i];
  sort(w, w + n);
  reverse(w, w + n);
  int ans = 1e18;
  for(auto it : f[n]) {
    int v = it.second.first;
    for(int i = 0; i < n; i++) v +=w[i] * it.first[i];
    ans = min(ans, v);
  }
  cout << ans << "\n";
}

bool Med;
int main() {
  f[1][{0}] = {0, 1};
  int encounter = 0, sum = 0;
  for(int i = 1; i < N; i++) {
    for(auto it : f[i]) {
      auto v = it.second;
      for(int j = v.second, t = i + j; j <= i && t < N; j++, t++) {
        int nv = v.first * 2 + t - 2;
        if(nv >= 5e11) continue;
        encounter++;
        vector<int> x = it.first, y;
        for(int p = 0; p < i; p++) {
          y.push_back(x[p]);
          if(p < j) y.push_back(x[p] + 1);
        }
        sort(y.begin(), y.end());
        auto it = f[t].find(y);
        if(it == f[t].end()) f[t][y] = {nv, j};
        else {
          it->second.first = min(it->second.first, nv);
          it->second.second = min(it->second.second, j);
        }
      }
    }
  }
  int T = 1;
  cin >> T;
  while(T--) mian();
  return 0;
}