#include <bits/stdc++.h>

using VI = std::vector<int>;
using ll = long long;
const int base = 1000000000;
const int bsz = 9;

struct BigInt
{
	VI a; int sign;
	BigInt() { sign = 1; }
	BigInt(ll v)
	{
		sign = 1; if(v < 0) v = -v, sign = -1;
		a.clear();
		while(v)
		{
			a.push_back(v % base);
			v /= base;
		}
	}
	BigInt operator = (const int &v) { return *this = BigInt(static_cast<ll>(v)); }
	BigInt operator = (const ll &v) { return *this = BigInt(v); }
	BigInt operator = (const BigInt &v) { a = v.a; sign = v.sign; return *this; }
	
	BigInt operator -() const
	{
		BigInt ret = *this;
		ret.sign = -ret.sign;
		return ret;
	}
	
	BigInt operator + (const BigInt &rhs) const
	{
		if(sign != rhs.sign) return (*this) - (-rhs);
	}
	
	BigInt operator - (const BigInt &rhs) const
	{
		if(sign != rhs.sign) return (*this) + (-rhs);
	}
};