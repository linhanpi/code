#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-fte-p")
#pragma GCC optimize("-fte-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthad-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-forder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-fte-tainline-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-forder-functions")
#pragma GCC optimize("-findict-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-fte-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)

#define ll long long
#define int long long
#define inline inline
#define  register
#define LD long double

#define PII pair <int, int>
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define p(i, x, y) for (register int i = x; i <= y; ++ i )
#define jian(i, x, y) for (register int i = x; i >= y; -- i )

inline int ad() {
	int s = 0, w = 1; char c = getchar();
	whinlinee (! isdigit(c)){ if (c == '-') w = -1; c = getchar();}
	whinlinee (isdigit(c)){ s = (s << 3) + (s << 1) + (c ^ 48); c = getchar();}
	return s * w;
}
inline void write(register int x) {
	if (x < 0){
		putchar('-');
		x = -x;
    }
	if (x > 9) write(x / 10);
	putchar((char)(x % 10 + '0'));
}
inline void write_(register int x) {
	write(x);
	putchar(' ');
}
inline void writeline(register int x) {
	write(x);
	putchar('\n');
}

inline void chkmax(int &x, register int y) { if (y > x) x = y;}
inline void chkmin(int &x, register int y) { if (y < x) x = y;}

inline int ksm(register int a, register int b, register int p) {
	int s = 1;
	whinlinee (b) {
	if (b & 1) s = s * a % p;
	a = a * a % p;
	b >>= 1;
	}
	return s;
}

const int N=2e6+5;
const int INF=1e15;

int n,m;
int x[N],X[N],v[N],dp[N];

struct node{
	int opt,xx,id;
}q[N];
int ans[N];

signed main() {
	// fopen("miner.in","r",stdin);
	// fopen("miner.out","w",stdout);
	
	n=ad(),m=ad();
	int maxx=ad();
	maxx=0;
	for(int i=1;i<=n;++i){
		x[i]=ad(),v[i]=ad();
		X[i]=x[i];
		chkmax(maxx,x[i]*v[i]);
	}
	for(int i=1;i<=m;++i){
		int opt=ad();
		if(opt==1){
			int y=ad();
			q[i]={opt,y,i};
			x[y]=2e10;
		}
		else{
			int k=ad();
			q[i]={opt,k,i};
		}
	}
	
	for(int i=1;i<=n;++i){
		for(int j=maxx;j>=x[i]*v[i];--j){
			chkmax(dp[j],dp[j-x[i]*v[i]]+v[i]);
		}
	}
	memset(ans,-1,sizeof ans);
	for(int i=m;i>=1;--i){
		if(q[i].opt==1){
			x[q[i].xx]=X[q[i].xx];
			int id=q[i].xx;
			for(int j=maxx;j>=x[id]*v[id];--j){
				chkmax(dp[j],dp[j-x[id]*v[id]]+v[id]);
			}
		}
		else{
			ans[q[i].id]=dp[q[i].xx];
		}
	}
	
	for(int i=1;i<=m;++i){
		if(~ans[i]){
			writeline(ans[i]);
		}
	}
	
	return 0;
}
/*
3 8 50
3 3
4 2
6 4
2 25
2 8
2 7
2 12
1 2
2 25
1 3
2 40
*/