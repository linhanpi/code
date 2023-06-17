#include<bits/stdc++.h>
#define ull unsigned long long
#define ll long long
using namespace std;
#define rd() (red<int>())
template<typename T>inline T red(){T x=0;bool f=false;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=true;c=getchar();}while(c>='0'&&c<='9')x=(x<<3)+(x<<1)+(c^48),c=getchar();return f?-x:x;}
template<typename T>inline void write(T x){if(x<0){putchar('-');x=-x;}if(x/10)write(x/10);putchar((x%10)^48);return;}
const int N=8e6+5;
const int M=3200+5;
const int mod=20071027;
int n,q,ci;
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
    return a*32768+b+1;
}
int a[N],p[N];
inline void red(){
    using namespace GenHelper;
    for(int i=1;i<n;i++){
        p[i]=i;
    }
    for(int i=1;i<ci;i++){
        int a=read()%(n-1)+1,b=read()%(n-1)+1;
        swap(p[a],p[b]);
    }
    return ;
}

int main(){
    n=rd(),q=rd(),ci=rd();int seed=rd(),type=rd();
    srand(seed);
    red();
	for(register int i=1;i<=n;++i) a[i]=read()%mod;
    
    /*
    write your codes here
    */

	int l,r,lastans=0;
	ull final_ans=0;
	for(register int t=1;t<=q;++t){
		l=read()%(n-1)+1,r=read()%(n-1)+1;
        if(l>r)swap(l,r);
		ll ansnow=0;
		
        /*
        write your codes here
        */

        if(type==0)printf("%llu\n",ansnow);
		lastans=ansnow;
		final_ans^=1ull*t*ansnow;
	}
	if(type==1)printf("%llu\n",final_ans);
	return 0;
}