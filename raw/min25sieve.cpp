// This amazing code is by Eric Sunli Chen.
#include<bits/stdc++.h>
using namespace std;
template<typename T> bool get_int(T &x)
{
	char t=getchar();
	bool neg=false;
	x=0;
	for(; (t>'9'||t<'0')&&t!='-'&&t!=EOF; t=getchar());
	if(t=='-')neg=true,t=getchar();if(t==EOF)return false;
	for(; t<='9'&&t>='0'; t=getchar())x=x*10+t-'0';
	if(neg)x=-x;return true;
}
template<typename T> void print_int(T x)
{
	if(x<0)putchar('-'),x=-x;
	short a[20]= {},sz=0;
	while(x>0)a[sz++]=x%10,x/=10;
	if(sz==0)putchar('0');
	for(int i=sz-1; i>=0; i--)putchar('0'+a[i]);
}
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define get1(a) get_int(a)
#define get2(a,b) (get1(a)&&get1(b))
#define get3(a,b,c) (get1(a)&&get2(b,c))
#define printendl(a) print_int(a),puts("")
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int,int> pii;
const int inf=0x3f3f3f3f;
const LL Linf=1ll<<61;
const double pi=acos(-1.0);

const int maxn=320111;
const int mod=998244353;

#define array abracadabra
namespace min25
{
	int sq;LL n;
	struct array
	{
		LL pre[maxn],nxt[maxn];
		void clear()
		{
			memset(pre,0,sizeof(pre));
			memset(nxt,0,sizeof(nxt));
		}
		array(){clear();}
		
		LL&operator [](const LL&x)
		{
			if(x<=sq)return pre[x];
			else return nxt[n/x];
		}
	};
	array h,h0,h1,g;
	bool pr[maxn];
	void prework(LL nn)
	{
		n=nn;sq=sqrt(n);
		for(int i=2;i<=sq;i++)pr[i]=1;
		for(int i=2;i<=sq;i++)if(pr[i])for(int j=i+i;j<maxn;j+=i)pr[j]=0;
		
		vector<LL> vs;
		for(int i=1;(LL)i*i<=n;i++)
		{
			vs.pb(i);
			vs.pb(n/i);
		}
		sort(vs.begin(),vs.end());vs.erase(unique(vs.begin(),vs.end()),vs.end());
		int sz=vs.size();
		for(int i=0;i<sz;i++)
			h0[vs[i]]=vs[i];
		for(int i=2;i<=sq;i++)if(pr[i])
		{
			for(int j=sz-1;j>=0;j--)
			{
				if(vs[j]<(LL)i*i)break;
				h0[vs[j]]=h0[vs[j]]-h0[vs[j]/i]+h0[i-1];
			}
		}
		for(int i=0;i<sz;i++)g[vs[i]]=h[vs[i]]=(h0[vs[i]]-1)*4;
		for(int i=sq;i>0;i--)if(pr[i])
		{
			for(int j=sz-1;j>=0;j--)
			{
				if(vs[j]<(LL)i*i)break;
				LL p=i;
				for(int e=1;;e++)
				{
					g[vs[j]]+=(3*e+1)*((e>1)+g[vs[j]/p]-h[min(vs[j]/p,i+0ll)]);
					if(1.0*p*i>n)break;
					p*=i;
					if(p>vs[j])break;
				}
			}
		}
		printf("%lld\n",g[n]+1);
	}
};

LL n;
int main()
{
	get1(n);
	min25::prework(n);
	return 0;
}
