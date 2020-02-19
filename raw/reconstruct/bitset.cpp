#include <bits/stdc++.h>

const int maxn=1600;
struct Bitset
{
	unsigned long long a[maxn];
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
		unsigned long long last=0;
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
		unsigned long long last=0;
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
	std::vector<int> ones()const
	{
		std::vector<int> ret;
		for(int i=0;i<maxn;i++)
		{
			unsigned long long tmp=a[i];
			while(tmp)
			{
				int t=__builtin_ctz(tmp);
				ret.push_back(t|(i<<6));
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
