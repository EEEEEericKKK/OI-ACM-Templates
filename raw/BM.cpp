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

const int mod=998244353;
int qpow(int x,int y)
{
	int ret=1;
	while(y)
	{
		if(y&1)ret=(LL)ret*x%mod;
		x=(LL)x*x%mod;
		y>>=1;
	}
	return ret;
}

namespace Berlekamp_Massey
{
	int n;
	vector<int> calc(const vector<int>&x)
	{
		n=(int)x.size();
		
		vector<int> cur,fix;
		int pos,lastd;
		
		for(int i=0;i<n;i++)
		{
			int delta=(mod-x[i])%mod;
			for(int j=0;j<(int)cur.size();j++)
				delta=(delta+(LL)cur[j]*x[i-j-1])%mod;
			if(delta==0)continue;
			
			if(cur.size()==0)
			{
				cur.resize(i+1);
				pos=i;
				lastd=delta;
				continue;
			}
			
			int coef=(LL)delta*qpow(lastd,mod-2)%mod;
			vector<int> nxt(i-pos-1,0);nxt.pb(coef);
			for(int i=0;i<(int)fix.size();i++)nxt.pb((LL)fix[i]*(mod-coef)%mod);
			if(nxt.size()<cur.size())nxt.resize(cur.size());
			for(int i=0;i<(int)cur.size();i++)
			{
				nxt[i]+=cur[i];
				if(nxt[i]>=mod)nxt[i]-=mod;
			}
			
			pos=i;
			fix=cur;cur=nxt;
			lastd=delta;
			
			// printf("cur ");for(int j=0;j<(int)cur.size();j++)printf("%d ",cur[j]);puts("");
			// printf("fix ");for(int j=0;j<(int)fix.size();j++)printf("%d ",fix[j]);puts("");
		}
		return cur;
	}
};

int n;
int main()
{
	get1(n);vector<int> vv,ans;
	for(int i=0;i<n;i++)
	{
		int x;get1(x);
		vv.pb(x);
	}
	ans=Berlekamp_Massey::calc(vv);
	for(int i=0;i<(int)ans.size();i++)printf("%d%c",ans[i]<mod/2?ans[i]:ans[i]-mod,i==(int)ans.size()-1?'\n':' ');
	return 0;
}
