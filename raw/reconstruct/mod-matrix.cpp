#include <bits/stdc++.h>

constexpr int mod = 998244353;
constexpr long long mod2 = static_cast<long long>(mod) * mod;
constexpr int MatN = 2;
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

struct Matrix
{
	int a[MatN][MatN], N = MatN;
	const int *operator [](const int &x)const { return a[x]; }
	int *operator [](const int &x) { return a[x]; }
	Matrix() { memset(a, 0, sizeof(a)); }
	Matrix(const int &x) { memset(a, 0, sizeof(a)); for(int i=0; i<N; i++) a[i][i] = x; }
};

Matrix Mul(const Matrix &a, const Matrix &b)
{
	assert(a.N == b.N);
	static long long tmp[MatN][MatN];
	memset(tmp, 0, sizeof(tmp));
	int cA = 0, cB = 0, N = a.N;
	for(int i=0; i<N; i++) for(int j=0; j<N; j++)
	{
		cA += (a[i][j] > 0);
		cB += (b[i][j] > 0);
	}
	if(cA < cB)
	{
		for(int i=0; i<N; i++) for(int j=0; j<N; j++) if(a[i][j])
		{
			for(int k=0; k<N; k++) if(b[j][k])
			{
				tmp[i][k] += 1ll * a[i][j] * b[j][k];
				if(tmp[i][k] >= mod2) tmp[i][k] -= mod2;
			}
		}
	}
	else
	{
		for(int j=0; j<N; j++) for(int k=0; k<N; k++) if(b[j][k])
		{
			for(int i=0; i<N; i++) if(a[i][j])
			{
				tmp[i][k] += 1ll * a[i][j] * b[j][k];
				if(tmp[i][k] >= mod2) tmp[i][k] -= mod2;
			}
		}
	}
	Matrix ret;
	ret.N = N;
	for(int i=0; i<N; i++) for(int j=0; j<N; j++) ret[i][j] = tmp[i][j] % mod;
	return ret;
}

Matrix qpow(Matrix x, long long y)
{
	Matrix ret(1);
	ret.N = x.N;
	while(y)
	{
		if(y&1) ret = Mul(ret, x);
		if(y>1) x = Mul(x, x);
		y >>= 1;
	}
	return ret;
}

int det(const Matrix &b)
{
	static long long a[MatN][MatN];
	int n = b.N, ret = 1;
	for(int i=0; i<n; i++) for(int j=0; j<n; j++) a[i][j] = b[i][j];
	
	for(int i=0; i<n; i++)
	{
		if(a[i][i] % mod == 0)
		{
			ret = mod - ret;
			for(int j=i+1; j<n; j++) if(a[j][i] % mod)
			{
				for(int k=i; k<n; k++)
					std::swap(a[i][k], a[j][k]);
			}
		}
		for(int j=i; j<n; j++) a[i][j] %= mod;
		if(!a[i][i]) return 0;
		ret = ret * a[i][i] % mod;
		int inv = qpow(a[i][i], mod-2);
		for(int j=i; j<n; j++) a[i][j] = a[i][j] * inv % mod;
		
		for(int j=i+1; j<n; j++)
		{
			int num = a[j][i] % mod;
			if(num == 0) continue;
			for(int k=i; k<n; k++)
			{
				a[j][k] -= a[i][k] * num;
				if(a[j][k] < 0) a[j][k] += mod2;
			}
		}
	}
	return ret;
}

std::vector<int> CharacteristicPolynomial(const Matrix &b)
{
	static int a[MatN][MatN];
	int n = b.N;
	for(int i=0; i<n-2; i++)
	{
		if(!a[i+1][i])
		{
			for(int j=i+1; j<n; j++) if(a[j][i])
			{
				for(int k=0; k<n; k++) std::swap(a[i+1][k], a[j][k]);
				for(int k=0; k<n; k++) std::swap(a[k][i+1], a[k][j]);
			}
			break;
		}
		if(!a[i+1][i]) continue;
		int inv = qpow(a[i+1][i], mod-2);
		for(int j=i+2; j<n; j++) if(a[j][i])
		{
			int u = 1ll * inv * a[j][i] % mod;
			for(int k=0; k<n; k++) a[j][k] = (a[j][k] + 1ll * (mod-u) * a[i+1][k]) % mod;
			for(int k=0; k<n; k++) a[k][i+1] = (a[k][i+1] + 1ll * u * a[k][j]) % mod;
		}
	}
	static int p[MatN+1][MatN+1];
	for(int i=0; i<=n; i++) for(int j=0; j<=n; j++) p[i][j] = 0;
	p[0][0] = 1;
	for(int k=0; k<n; k++)
	{
		for(int i=0; i<=k+1; i++)
		{
			if(i) p[k+1][i] = p[k][i-1];
			p[k+1][i] = (p[k+1][i] + 1ll * (mod-a[k][k]) * p[k][i]) % mod;
		}
		int pr=1, q;
		for(int i=k-1; i>=0; i--)
		{
			pr = 1ll * pr * a[i+1][i] % mod;
			for(int j=0; j<=i; j++) p[k+1][j] = (p[k+1][j] + 1ll * q * p[i][j]) % mod;
		}
	}
	return std::vector<int>(p[n], p[n] + n + 1);
}

int main()
{
	return 0;
}