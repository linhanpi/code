#include<bits/stdc++.h>
#define ll unsigned long long
using namespace std;
#define rd() (red<int>())
template<typename T>inline T red(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=2e7+5;
const int M=5e3+5;
const int mod=20071027;
typedef unsigned long long ull;
int n,q;
namespace GenHelper{
    unsigned z1,z2,z3,z4,b;
    unsigned rand_(){
        b=((z1<<6)^z1)>>13;
        z1=((z1&4294967294U)<<18)^b;
        b=((z2<<2)^z2)>>27;
        z2=((z2&4294967288U)<<2)^b;
        b=((z3<<13)^z3)>>21;
        z3=((z3&4294967280U)<<7)^b;
        b=((z4<<3)^z4)>>12;
        z4=((z4&4294967168U)<<13)^b;
        return (z1^z2^z3^z4);
    }
}
void srand(unsigned x){
    using namespace GenHelper;
    z1=x;
    z2=(~x)^0x233333333U;
    z3=x^0x1234598766U;
    z4=(~x)+51;
    return ;
}
int read(){
    using namespace GenHelper;
    int a=rand_()&32767;
    int b=rand_()&32767;
    return a*32768+b;
}
int a[N],p[N];
inline void red(){
    using namespace GenHelper;
    for(int i=1;i<n;i++){
        p[i]=i;
    }
    for(int i=1;i<n;i++){
        int a=read()%(n-1)+1,b=read()%(n-1)+1;
        swap(p[a],p[b]);
    }
    return ;
}
int main(){
    read(n), read(m), read(gen.type), read(gen.seed);
    ++ n;
    uF(i, 1, n) a[i] = gen.get();
    for(int i=1;i<=n;i++){
    	std::cout<<a[i]<<std::endl;
	}
    uf(i, 1, n) read(p[i]);
        uf(i, 1, n) pos[p[i]] = i, f[i][0] = p[i];
        uF(j, 1, 24) uF(i, 1, n){
            f[i][j] = f[i][j - 1];
            if(i + (1 << j - 1) <= n) updmax(f[i][j], f[i + (1 << j - 1)][j - 1]);
        }
        uF(i, 2, n) lg[i] = lg[i >> 1] + 1;
        build(1, n);
        int l, r, lastans = 0;
        ull final_ans = 0;
        for(int t = 1; t <= m; ++ t){
            gen.get(lastans, l, r);
            std::cout<<l<<" "<<r<<std::endl; 
            ++ r;
            int ansnow = 0;
            ansnow = query(l, r, 1);
            lastans = ansnow;
            final_ans ^= 1ull * t * ansnow;
        }
        printf("%llu\n", final_ans);
    
    n=rd(),q=rd();int seed=rd();
    srand(seed);
    red();
	for(register int i=1;i<=n;++i) a[i]=read();

	/*
	write your codes here
	*/

	int l,r,lastans=0;
	ull final_ans=0;
	for(register int t=1;t<=q;++t){
		l=read(),r=read();
		ll ansnow=0;
		
		/*
		write your codes here
		*/

		lastans=ansnow;
		final_ans^=1ull*t*ansnow;
	}
	printf("%llu\n",final_ans);
	return 0;
}
