#include <bits/stdc++.h>

const int mod = 1e9 + 7;
typedef long long LL;

int qpow(int x, int y, const int &mod = ::mod)
{
	int ret = 1;
	while (y)
	{
		if (y & 1) ret = 1ll * ret * x % mod;
		x = 1ll * x * x % mod;
		y >>= 1;
	}
	return ret;
}

// a * m + b * n = gcd(m, n)
template <typename Tp>
void extgcd(Tp m, Tp n, Tp &a, Tp &b)
{
	if (n == 0)
	{
		a = 1;
		b = 0;
		return;
	}
	Tp aa, bb;
	extgcd(n, m % n, aa, bb);
	a = bb;
	b = aa - bb * (m / n);
}

LL multMod(LL x, LL y, LL mod)
{
	LL tmp = x * y - (LL)((long double)1.0 * x / mod * y + 1e-8) * mod;
	while (tmp < 0) tmp += mod;
	while (tmp >= mod) tmp -= mod;
	return tmp;
}

/*
 x = a1 (mod m1) and x = a2 (mod m2)
 calculate x mod [m1, m2]
*/
LL mergeCRT(LL a1, LL m1, LL a2, LL m2)
{
	LL g = std::__gcd(m1, m2), tmp, ans, b1, b2, M;
	if(a1 % g != a2 % g) return -1;
	
	tmp = a1 % g;
	m1 /= g; a1 /= g;
	m2 /= g; a2 /= g;
	M = m1 * m2;
	
	extgcd(m1, m2, b2, b1);
	b1 = multMod(b1, m2, M);
	b2 = multMod(b2, m1, M);
	ans = multMod(a1, b1, M) + multMod(a2, b2, M);
	if(ans >= M) ans -= M;
	ans = ans * g + tmp;
	return ans;
}

namespace factor
{
	LL power(LL x, LL y, LL mod)
	{
		LL ret = 1;
		x %= mod;
		do
		{
			if (y & 1) ret = multMod(ret, x, mod);
			x = multMod(x, x, mod);
		} while (y >>= 1);
		return ret;
	}
	bool MillerRabin(LL n, int a)
	{
		LL d = n - 1;
		int s = 0;
		while (~d & 1)
		{
			s++;
			d >>= 1;
		}
		LL p = power(a, d, n);
		if (p == 1)
			return true;
		for (int i = 0; i < s; i++)
		{
			if (p == n - 1)
				return true;
			p = multMod(p, p, n);
		}
		return false;
	}
	const int pr[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	bool isprime(LL n)
	{
		for (int i = 0; i < 10 && pr[i] < n; i++)
			if (!MillerRabin(n, pr[i]))
				return false;
		return true;
	}
	void rho(LL n, std::vector<LL> &ret)
	{
		if (n == 1)
			return;
		if (isprime(n))
		{
			ret.push_back(n);
			return;
		}
		if (n == 4)
		{
			ret.push_back(2);
			ret.push_back(2);
			return;
		}
		while (true)
		{
			LL x = 2, y = 2, d = 1;
			int k = rand() + 1;
			while (d == 1)
			{
				x = (multMod(x, x, n) + k) % n;
				y = (multMod(y, y, n) + k) % n;
				y = (multMod(y, y, n) + k) % n;
				d = std::__gcd(n, std::abs(x - y));
			}
			if (d != n)
			{
				rho(d, ret);
				rho(n / d, ret);
				break;
			}
		}
	}
} // namespace factor

const int pivot = 2;
struct extField // a + b * sqrt(pivot)
{
	int a, b;
	extField(int k1 = 0, int k2 = 0) { a = k1; b = k2; }
	extField operator +(const extField &rhs) const
	{
		extField ret(a + rhs.a, b + rhs.b);
		if(ret.a >= mod) ret.a -= mod;
		if(ret.b >= mod) ret.b -= mod;
		return ret;
	}
	extField operator -(const extField &rhs) const
	{
		extField ret(a - rhs.a, b - rhs.b);
		if(ret.a < 0) ret.a += mod;
		if(ret.b < 0) ret.b += mod;
		return ret;
	}
	extField operator *(const extField &rhs) const
	{
		return extField((1ll * a * rhs.a + 1ll * b * rhs.b % mod * pivot) % mod,
						(1ll * a * rhs.b + 1ll * b * rhs.a) % mod);
	}
};

/*
 solve equation x^2 - n = 0 (mod p), where p is an odd prime
 return one of the two roots or -1 if there is no solution
*/
int Cipolla(int n, int P)
{
	if(n == 0) return 0;
	if(qpow(n, (P - 1) / 2, P) != 1) return -1;
	int a = 1, piv;
	while(qpow(piv = (1ll * a * a - n + P) % P, (P - 1) / 2, P) == 1) a++;
	
	int p = 1, q = 0, pp = a, qq = 1, tp, tq, y = (P + 1) / 2;
	while(y)
	{
		if(y & 1)
		{
			tp = (1ll * p * pp + 1ll * q * qq % P * piv) % P;
			tq = (1ll * p * qq + 1ll * q * pp) % P;
			p = tp;
			q = tq;
		}
		if(y > 1)
		{
			tp = (1ll * pp * pp + 1ll * qq * qq % P * piv) % P;
			tq = 2ll * pp * qq % P;
			pp = tp;
			qq = tq;
		}
		y >>= 1;
	}
	return p;
}

int main()
{
	printf("%lld\n", mergeCRT(5, 234, 20, 123));
	return 0;
}