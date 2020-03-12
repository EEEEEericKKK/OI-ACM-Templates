#include <bits/stdc++.h>

constexpr int mod = 1e9+7;
typedef std::vector<int> vi;
int qpow(int x, int y)
{
	int ret = 1;
	while(y)
	{
		if(y&1) ret = 1ll * ret * x % mod;
		x = 1ll * x * x % mod;
		y >>= 1;
	}
	return ret;
}

vi operator +(const vi &a, const vi &b)
{
	vi ret;
	if(a.size() < b.size())
	{
		ret = b;
		for(int i=0; i<a.size(); i++)
		{
			ret[i] += a[i];
			if(ret[i] >= mod) ret[i] -= mod;
		}
	}
	else
	{
		ret = a;
		for(int i=0; i<b.size(); i++)
		{
			ret[i] += b[i];
			if(ret[i] >= mod) ret[i] -= mod;
		}
	}
	return ret;
}
vi operator *(int t, const vi &a)
{
	vi ret = a;
	for(int i=0; i<a.size(); i++) ret[i] = 1ll * ret[i] * t % mod;
	return ret;
}
vi operator *(const vi &a, int t)
{
	vi ret = a;
	for(int i=0; i<a.size(); i++) ret[i] = 1ll * ret[i] * t % mod;
	return ret;
}
vi operator -(const vi &a, const vi &b)
{
	vi ret = a;
	for(int i=0; i<a.size(); i++)
	{
		ret[i] -= b[i];
		if(ret[i] < 0) ret[i] += mod;
	}
	for(int i=a.size(); i<b.size(); i++)
	{
		if(b[i]) ret.push_back(mod - b[i]);
		else ret.push_back(0);
	}
	return ret;
}
vi operator *(const vi &a, const vi &b)
{
	const unsigned long long md2 = static_cast<unsigned long long>(mod) * mod;
	static unsigned long long res[200111];
	memset(res, 0, sizeof(res[0]) * (a.size() + b.size() - 1));
	for(int i=0; i<a.size(); i++) for(int j=0; j<b.size(); j++)
	{
		res[i+j] += 1ll * a[i] * b[j];
		if(res[i+j] >= md2) res[i+j] -= md2;
	}
	vi ret(a.size() + b.size() - 1);
	for(int i=0; i<a.size() + b.size() - 1; i++) ret[i] = res[i] % mod;
	return ret;
}
vi operator %(vi a, vi b)
{
	if(a.size() < b.size()) return a;
	assert(b.size() > 1);
	b = b * qpow(b.back(), mod-2);
	std::reverse(b.begin(), b.end());
	for(int i=a.size()-1; i>=b.size()-1; i--)
	{
		if(!a[i]) continue;
		int tmp = a.back();
		for(int j=b.size()-1; j>=0; j--)
			a[i-j] = (a[i-j] + 1ll * tmp * (mod - b[j])) % mod;
	}
	while(!a.back()) a.pop_back();
	return a;
}
vi operator /(vi a, vi b)
{
	if(a.size() < b.size()) return vi();
	assert(b.size() > 1);
	b = b * qpow(b.back(), mod-2);
	std::reverse(b.begin(), b.end());
	vi ret;
	for(int i=a.size()-1; i>=b.size()-1; i--)
	{
		ret.push_back(a[i]);
		if(!a[i]) continue;
		for(int j=b.size()-1; j>=0; j--)
			a[i-j] = (a[i-j] + 1ll * a.back() * (mod - b[j])) % mod;
	}
	std::reverse(ret.begin(), ret.end());
	return ret;
}

template<typename Tp>
vi qpow(vi x, Tp y, const vi &mod)
{
	vi ret(1, 1);
	while(y)
	{
		if(y) ret = ret * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ret;
}

int main()
{
	return 0;
}