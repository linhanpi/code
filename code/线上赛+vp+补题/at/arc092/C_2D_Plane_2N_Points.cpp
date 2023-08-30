#include<bits/stdc++.h>
#include<atcoder/maxflow>
#define R(i) for(int i=1;i<=n;i++)
#define A g.add_edge
using namespace std;
using namespace atcoder;
int a[110],b[110],c[110],d[110],n;
int main(){
	cin>>n;
    mf_graph <int> g(2*n+2);
    for(int i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    for(int i=1;i<=n;i++){
        cin>>c[i]>>d[i];
    }
    for(int i=1;i<=n;i++){
        A(0,i,1),A(n+i,2*n+1,1);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i]<c[j]&&b[i]<d[j]){
                A(i,n+j,1);
            }
        }
    }
	cout<<g.flow(0,2*n+1)<<'\n';
	return 0;
}