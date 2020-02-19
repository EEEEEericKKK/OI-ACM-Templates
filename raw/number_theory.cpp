// This amazing code is by Eric Sunli Chen.
#include <bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<int,int> pii;
const int inf=0x3f3f3f3f;

const int mod=1e9+7;

int power(int x,int y,const int&mod=::mod)
{
	int ret=1;
	while(y)
	{
		if(y&1)ret=1ll*ret*x%mod;
		x=1ll*x*x%mod;
		y>>=1;
	}
	return ret;
}
void ext_gcd(int m,int n,int&a,int&b)
{
	if(n==0)
	{
		a=1;b=0;
		return;
	}
	int aa,bb;
	ext_gcd(n,m%n,aa,bb);
	a=bb;b=aa-bb*(m/n);
}

LL mult(LL x,LL y,LL mod)
{
	LL tmp=x*y-LL((long double)1.0*x/mod*y+1e-8)*mod;
	while(tmp<0)tmp+=mod;
	while(tmp>=mod)tmp-=mod;
	return tmp;/**/
}
namespace factor
{
	LL power(LL x,LL y,LL mod)
	{
		LL ret=1;x%=mod;
		do
		{
			if(y&1)ret=mult(ret,x,mod);
			x=mult(x,x,mod);
		}while(y>>=1);
		return ret;
	}
	bool MillerRabin(LL n,int a)
	{
		LL d=n-1;int s=0;
		while(~d&1)
		{
			s++;
			d>>=1;
		}
		LL p=power(a,d,n);
		if(p==1)return true;
		for(int i=0;i<s;i++)
		{
			if(p==n-1)return true;
			p=mult(p,p,n);
		}
		return false;
	}
	bool isprime(LL n)
	{
		for(int i=2;i<30&&i<n;i++)if(!MillerRabin(n,i))return false;
		return true;
	}
	void rho(LL n,vector<LL>&ret)
	{
		if(n==1)return;
		if(isprime(n))
		{
			ret.pb(n);
			return;
		}
		if(n==4)
		{
			ret.pb(2);
			ret.pb(2);
			return;
		}
		while(true)
		{
			LL x=2,y=2,d=1;int k=rand()+1;
			while(d==1)
			{
				x=(mult(x,x,n)+k)%n;
				y=(mult(y,y,n)+k)%n;
				y=(mult(y,y,n)+k)%n;
				d=__gcd(n,abs(x-y));
			}
			if(d!=n)
			{
				rho(d,ret);rho(n/d,ret);
				break;
			}
		}
	}
}
namespace Cipolla
{
	int qpow(int x,int y,int mod)
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
	int calc(int x,int mod)
	{
		if(x==0)return 0;
		if(qpow(x,(mod-1)/2,mod)!=1)return -1;
		int a=1,piv;while(qpow(piv=((LL)a*a-x+mod)%mod,(mod-1)/2,mod)==1)a++;
		int p=1,q=0,pp=a,qq=1,tp,tq,y=(mod+1)/2;
		while(y)
		{
			if(y&1)
			{
				tp=((LL)pp*p+(LL)qq*q%mod*piv)%mod;
				tq=((LL)pp*q+(LL)qq*p)%mod;
				p=tp;q=tq;
			}
			tp=((LL)pp*pp+(LL)qq*qq%mod*piv)%mod;
			tq=(LL)pp*qq*2%mod;
			pp=tp;
			qq=tq;
			y>>=1;
		}
		assert(1ll*p*p%mod==x);
		return p;
	}
}

