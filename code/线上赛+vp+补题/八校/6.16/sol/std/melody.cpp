#include <bits/stdc++.h>
using namespace std;
const unsigned maxn = 1 << 22, mod = 998244353;
typedef unsigned u32;
typedef unsigned long long u64;
char I[22000038],*J=I;
inline u32 read()
{
	u32 x=0;
	while(*J<48||57<*J)J++;
	while(47<*J&&*J<58)x=(x<<1)+(x<<3)+(*J++^48);
	return x;
}

inline u32 upbit(u32 x) { return x |= x >> 1, x |= x >> 2, x |= x >> 4, x |= x >> 8, x |= x >> 16, x+1; }

inline u32 mt(u32 x) { return x >= mod ? x - mod : x; }

inline u32 qpow(u32 x, u32 k) { u32 res = 1; while (k) { if (k & 1) res = (u64)res * x % mod; x = (u64)x * x % mod, k >>= 1; } return res; }

u32 w[maxn];

void __init__(u32 N)
{
    for (u32 mid = 1, o, j; mid < N; mid <<= 1)
        for (w[j = mid] = 1, o = qpow(3, (mod - 1) / (mid << 1)), j++; j < (mid << 1); j++) w[j] = (u64)w[j - 1] * o % mod;
}

void DFT(u32 *A, u32 *B, u32 n, u32 len)
{
    memset(B + len, 0, sizeof(u32) * (n - len)), memcpy(B, A, sizeof(u32) * len);
    for (u32 mid = n >> 1, R, j, k, *W, y, *a, *b; mid; mid >>= 1) for (R = mid << 1, j = 0; j < n; j += R)
        for (k = 0, W = w + mid, a = B + j, b = a + mid; k < mid; k++, W++, a++, b++)
            *b = (u64)(*a + mod - (y = *b)) * *W % mod, *a = mt(*a + y);
}

void iDFT(u32 *B, u32 n)
{
    for (u32 mid = 1, R, j, k, *W, y, *a, *b; mid < n; mid <<= 1) for (R = mid << 1, j = 0; j < n; j += R)
        for (k = 0, W = w + mid, a = B + j, b = a + mid; k < mid; k++, W++, a++, b++)
            y = (u64)*b * *W % mod, *b = mt(*a + mod - y), *a = mt(*a + y);
    reverse(B + 1, B + n);
    for (u32 iv = mod - mod / n, i = 0; i < n; i++) B[i] = u64(B[i]) * iv % mod;
}

u32 n, N, v[maxn], s[maxn], iv[maxn];

void add(u32& x, u32 y) { x = (x + y >= mod ? x + y - mod : x + y); }

const u32 B = 8;

u32 g[maxn], G[maxn], h1[maxn * 2], h2[maxn], h[maxn * 2];
void solve(u32 l, u32 r, u32 pt)
{
    if (r - l + 1 <= 64)
    {
        for (u32 i = l, j; i <= r; i++)
        {
            G[i] = mt(1 + mod - (u64)g[i] * iv[i] % mod);
            for (j = i; j <= r; j++) add(g[i + j], (u64)s[j] * G[i] % mod)/*, VS[i][j] = 1*/;
        }
        return;
    }
    u32 len = (r - l + 1) / B;
    memset(h + pt, 0, sizeof(int) * len * B << 2);
    for (u32 id = 0; id < B; id++)
    {
        DFT(s + l + len * id, h2, len << 1, len);
        for (u32 Id = 0; Id < id; Id++)
        {
            for (u32 *f = h1 + pt + (len * Id << 1),
                *F = h + pt + (len * (id + Id) << 1), i = 0; i < (len << 1); i++) add(F[i], (u64)f[i] * h2[i] % mod);
         }
        if (id)
        {
            u32 *f = h + pt + (len * id << 1);
            iDFT(f, len << 1);
            for (u32 *F = g + l * 2 + len * id, i = 0; i < (len << 1); i++) add(F[i], f[i]);
        }
        solve(l + id * len, l + (id + 1) * len - 1, pt + (len * B << 2));
        if (id ^ B) DFT(G + l + len * id, h1 + pt + (len * id << 1), len << 1, len);
    }
    for (u32 id = B; id < (B << 1) - 1; id++)
    {
        u32 *f = h + pt + (len * id << 1);
        iDFT(f, len << 1);
        for (u32 *F = g + l * 2 + len * id, i = 0; i < (len << 1); i++) add(F[i], f[i]);
    }
}

int main()
{
	freopen("melody.in","r",stdin);
	freopen("melody.out","w",stdout);
    fread(I,1,22000038,stdin);
    n = read();
    for (u32 i = 1; i <= n; i++) v[i] = read();
    for (u32 i = s[0] = 1; i <= n; i++) s[i] = (u64)s[i - 1] * v[i] % mod;
    iv[n] = qpow(s[n], mod - 2);
    for (u32 i = n - 1; i; i--) iv[i] = (u64)iv[i + 1] * v[i + 1] % mod;
    N = upbit(n);
    __init__(N);
    solve(1, N >> 1, 0);
    u32 ans = g[n];
    for (u32 i = (N >> 1) + 1; i < n; i++) add(ans, (u64)s[i] * G[n - i] % mod);
    printf("%u\n", (s[n] + mod - ans) % mod);
    return 0;
}
