#include <bits/stdc++.h>
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

            if (j > 1)
                g[i][j] = (g[i][j] + 1LL * g[i - 1][j - 2] * j * (j - 1)%P * ni2%P) % P;
        }
    }
    f[n * 2 + 1][0] = 1;
    int sum = 0;
    pre(i, n * 2, 1) {
        if (u[i]) {
            rep(j, 0, sum + 1) {
                f[i][j] = f[i + 1][j];
                rep(k, 1, j)
                f[i][j] = (f[i][j] + 1LL * f[i + 1][j - k] * c[sum - (j - k)][k - 1] % P * g[k - 1][k - 1] % P * k) % P;
            }
            sum++;
        } else {
            int res = n * 2 - i - sum;
            rep(j, 0, sum)f[i][j] = 1LL * f[i + 1][j] * (j - res) % P;
        }
    }
    // rep(i, 1, n)f[1][n] = 500000004LL * f[1][n] % P;
    printf("%d\n", f[1][n]);
    return 0;
}
