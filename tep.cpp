#include <bits/stdc++.h>
<<<<<<< HEAD
using namespace std;

//#pragma GCC optimize(2)

#define ll long long
#define int long long
#define LD long double

#define PII pair <int, int>
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define rep(i, x, y) for (register int i = x; i <= y; ++ i )
#define per(i, x, y) for (register int i = x; i >= y; -- i )

inline int read() {
    int s = 0, w = 1; char c = getchar();
    while (! isdigit(c)){ if (c == '-') w = -1; c = getchar();}
    while (isdigit(c)){ s = (s << 3) + (s << 1) + (c ^ 48); c = getchar();}
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
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

inline int gcd(register int a, register int b) {
	if (a < b) swap(a, b);
	if (! b) return a;
	return gcd(b, a % b);
}

inline int exgcd(register int a, register int b, int &x, int &y) {
	if (! b) {
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

#define inv1 invByKsm
#define inv2 invByExgcd

inline int invByKsm(register int x, register int p) {
	return ksm(x, p - 2, p);
}
inline int invByExgcd(register int x, register int p) {
	exgcd(x, p, x, *new int);
	return (x%p+p)%p;
}

const int N=1e5+5;
const int INF=1e16;

int n,q,L;
vector<int> g[N];
int fa[N],w[N][5];

int f[N][5];
int TMP[N];
void dfs(int x){
	if(f[x][1]>-1e12) return;
	int sum=0;
	for(auto y:g[x]){
		dfs(y);
		int tmp=-INF;
		rep(k,1,L){
			chkmax(tmp,f[y][k]);
		}
		TMP[y]=tmp;
		sum+=tmp;
	}
	f[x][1]=sum+w[x][1];
	rep(k,2,L){
		for(auto y:g[x]){
			chkmax(f[x][k],f[y][k-1]+sum-TMP[y]+w[x][k]);
		} 
	}
}

signed main() {
//	freopen("decompose.in","r",stdin);
//	freopen("decompose.out","w",stdout);
	
	n=read(),q=read(),L=read();
	rep(i,2,n){
		int x=read();
		g[x].pb(i);
		fa[i]=x;
	}
	rep(i,1,n) rep(j,1,L) w[i][j]=read();
	
	memset(f,-0x3f,sizeof f);
	
	while(q--){
		int x=read();
		rep(i,1,L) w[x][i]=read();
		for(int now=x;now;now=fa[now]) memset(f[now],-0x3f,sizeof f[now]);
		dfs(1);
		int ans=-INF;
		rep(i,1,L) chkmax(ans,f[1][i]);
		writeline(ans);
	}
	
	return 0;
}
=======
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 605
#define P 1000000007
#define ni2 500000004LL
using namespace std;
int f[N << 1][N], g[N][N], n, u[N << 1], c[N][N];
int main() {
    scanf("%d", &n);
    rep(i, 1, n) {
        int x;
        scanf("%d", &x);
        u[x] = 1;
    }
    rep(i, 0, n) {
        c[i][0] = g[i][0] = 1;
        rep(j, 1, i)c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % P;
        rep(j, 1, i) {
            g[i][j] = (g[i - 1][j] + j * g[i - 1][j - 1]) % P;

## 题目描述

聪聪和睿睿最近迷上了一款叫做分裂的游戏。

该游戏的规则是： 共有 $n$ 个瓶子， 标号为 $0, 1, \ldots, n-1$，第 $i$ 个瓶子中装有 $p_i$ 颗巧克力豆，两个人轮流取豆子，每一轮每人选择 $3$ 个瓶子，标号为 $i,j,k$, 并要保证 $i \lt j, j \leq k$，且第 $i$ 个瓶子中至少要有 $1$ 颗巧克力豆，随后这个人从第 $i$ 个瓶子中拿走一颗豆子并在 $j,k$ 中各放入一粒豆子（$j$ 可能等于 $k$） 。如果轮到某人而他无法按规则取豆子，那么他将输掉比赛。胜利者可以拿走所有的巧克力豆！

两人最后决定由聪聪先取豆子，为了能够得到最终的巧克力豆，聪聪自然希望赢得比赛。他思考了一下，发现在有的情况下，先拿的人一定有办法取胜，但是他不知道对于其他情况是否有必胜策略，更不知道第一步该如何取。他决定偷偷请教聪明的你，希望你能告诉他，在给定每个瓶子中的最初豆子数后是否能让自己得到所有巧克力豆，他还希望你告诉他第一步该如何取，并且为了必胜，第一步有多少种取法？

## 输入格式

输入文件第一行是一个整数 $t$，表示测试数据的组数。

每组测试数据的第一行是瓶子的个数 $n$，接下来的一行有 $n$ 个由空格隔开的非负整数，表示每个瓶子中的豆子数。

## 输出格式

对于每组测试数据，输出包括两行，第一行为用一个空格两两隔开的三个整数，表示要想赢得游戏，第一步应该选取的 $3$ 个瓶子的编号 $i,j,k$，如果有多组符合要求的解，那么输出字典序最小的一组。如果无论如何都无法赢得游戏，那么输出用一个空格两两隔开的三个 $-1$。

第二行表示要想确保赢得比赛，第一步有多少种不同的取法。

## 样例 #1

### 样例输入 #1

```
2
4
1 0 1 5000
3
0 0 1
```

### 样例输出 #1

```
0 2 3
1
-1 -1 -1
0
```

## 提示

$1 \leq t \leq 10$，$2 \leq n \leq 21$，$0 \leq p_i \leq 10^4$，
>>>>>>> 62cad7168c2e9834eeef807380bc61cb232fa22c
