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

const int maxn=1600;
struct Bitset
{
	uLL a[maxn];
	void reset(){memset(a,0,sizeof(a));}
	Bitset(){reset();}
	void flip(int x){a[x>>6]^=1ull<<(x&63);}
	void set(int x){a[x>>6]|=1ull<<(x&63);}
	void reset(int x){a[x>>6]&=~(1ull<<(x&63));}
	int test(int x){return (a[x>>6]>>(x&63))&1;}
	Bitset operator ~()const
	{
		Bitset ret;
		for(int i=0;i<maxn;i++)ret.a[i]=~a[i];
		return ret;
	}
	Bitset operator &(const Bitset &b)const
	{
		Bitset ret;
		for(int i=0;i<maxn;i++)ret.a[i]=a[i]&b.a[i];
		return ret;
	}
	Bitset operator |(const Bitset &b)const
	{
		Bitset ret;
		for(int i=0;i<maxn;i++)ret.a[i]=a[i]|b.a[i];
		return ret;
	}
	Bitset operator ^(const Bitset &b)const
	{
		Bitset ret;
		for(int i=0;i<maxn;i++)ret.a[i]=a[i]^b.a[i];
		return ret;
	}
	Bitset operator <<(const int t)const
	{
		Bitset ret;
		uLL last=0;
		int high=t>>6,low=t&63;
		for(int i=0;i+high<maxn;i++)
		{
			ret.a[i+high]=last|(a[i]<<low);
			if(low)last=a[i]>>(64-low);
		}
		return ret;
	}
	Bitset operator >>(const int t)const
	{
		Bitset ret;
		uLL last=0;
		int high=t>>6,low=t&63;
		for(int i=maxn-1;i>=high;i--)
		{
			ret.a[i-high]=last|(a[i]>>low);
			if(low)last=a[i]<<(64-low);
		}
		return ret;
	}
	int popcount()const
	{
		int ret=0;
		for(int i=0;i<maxn;i++)ret+=__builtin_popcount(a[i]);
		return ret;
	}
	vector<int> ones()const
	{
		vector<int> ret;
		for(int i=0;i<maxn;i++)
		{
			uLL tmp=a[i];
			while(tmp)
			{
				int t=__builtin_ctz(tmp);
				ret.pb(t|(i<<6));
				tmp^=1ull<<t;
			}
		}
		return ret;
	}
};
int main()
{
	return 0;
}
