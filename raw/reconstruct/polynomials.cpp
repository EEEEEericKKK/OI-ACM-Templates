#include <bits/stdc++.h>

namespace Poly
{

constexpr int mod = 998244353;
constexpr int root = 3;
constexpr int poly_bits = 19;
constexpr int poly_max = 1 << poly_bits;
int qpow(int x, int y, const int&mod = Poly::mod)
{
	int ret = 1;
	while(y)
	{
		if(y&1) ret = 1ll*ret*x%mod;
		x = 1ll*x*x%mod;
		y >>= 1;
	}
	return ret;
}

void dft(int* a, int n, bool inv = 0)
{
	static int w[2][poly_max]; static bool fb = 0;
	if(!fb)
	{
		fb = 1;
		int wn0 = qpow(root, (mod-1) >> poly_bits), wn1 = qpow(wn0, mod - 2);
		w[0][0] = w[1][0] = 1;
		for(int i=1; i<poly_max; i++)
		{
			w[0][i] = 1ll * w[0][i-1] * wn0 % mod;
			w[1][i] = 1ll * w[1][i-1] * wn1 % mod;
		}
	}
	const int *W = w[inv];
	const unsigned long long md2 = static_cast<unsigned long long>(mod) * mod;
	for(int i=0, j=0; i<n; i++)
	{
		if(i<j) std::swap(a[i], a[j]);
		for(int t = n>>1; (j ^= t) < t; t >>= 1);
	}
	static unsigned long long ca[poly_max];
	for(int i=0; i<n; i++) ca[i] = a[i];
	for(int l = 1, d = poly_bits - 1; l<n; l <<= 1, d--)
	{
		int l2 = l << 1;
		static int cw[poly_max];
		for(int j=0; j<l; j++) cw[j] = W[j<<d];
		for(int i=0, j; i<n; i+=l2)
		{
			unsigned long long *x1 = ca+i, *x2 = ca+i+l, tmp;
			for(j=0; j+8 <= l; j+=8)
			{
				tmp=(*x2%mod)*cw[j];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
				tmp=(*x2%mod)*cw[j+1];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
				tmp=(*x2%mod)*cw[j+2];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
				tmp=(*x2%mod)*cw[j+3];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
				tmp=(*x2%mod)*cw[j+4];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
				tmp=(*x2%mod)*cw[j+5];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
				tmp=(*x2%mod)*cw[j+6];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
				tmp=(*x2%mod)*cw[j+7];	*x2=*x1-tmp+md2; *x1+=tmp; x1++; x2++;
			}
			for(; j<l; j++)
			{
				tmp=(*x2%mod)*cw[j];
				*x2=*x1-tmp+md2;
				*x1+=tmp;
				x1++; x2++;
			}
		}
		if(l == 65536) for(int i=0; i<n; i++) ca[i] %= mod;
	}
	for(int i=0; i<n; i++) a[i] = ca[i] % mod;
	if(inv)
	{
		int inv = qpow(n, mod-2);
		for(int i=0; i<n; i++) a[i] = 1ll * a[i] * inv % mod;
	}
}

void Mult(int *a, int n, int *b, int m, int *c, int k = -1)
{
	static int ta[poly_max], tb[poly_max];
	if(k == -1) k = n + m - 1;
	if(n > k) n = k;
	if(m > k) m = k;
	if(n <= 50 && m <= 50)
	{
		memset(ta, 0, k<<2);
		for(int i=0; i<n; i++) for(int j=0; j<m; j++) ta[i+j] = (ta[i+j] + 1ll * a[i] * b[j]) % mod;
		memcpy(c, ta, k<<2);
		return;
	}
	int l = 1;
	while(l < n + m - 1) l <<= 1;
	memcpy(ta, a, n<<2); memset(ta + n, 0, (l-n)<<2);
	memcpy(tb, b, m<<2); memset(tb + m, 0, (l-m)<<2);
	dft(ta, l); dft(tb, l);
	for(int i=0; i<l; i++) ta[i] = 1ll * ta[i] * tb[i] % mod;
	dft(ta, l, 1);
	memcpy(c, ta, k<<2);
}

void Inv_do(int *a, int n, int *b, int m)
{
	if(m == 1)
	{
		if(a[0] == 1) b[0] = 1;
		else b[0] = qpow(a[0], mod - 2);
		return;
	}
	if(n > m) n = m;
	int nl = (m+1)/2, l = 1;
	while(l < n + nl*2 - 2) l <<= 1;
	Inv_do(a, n, b, nl);
	static int ta[poly_max];
	memcpy(ta, a, n<<2); memset(ta + n, 0, (l-n)<<2);
	memset(b+nl, 0, (l-nl)<<2);
	dft(ta, l); dft(b, l);
	for(int i=0; i<l; i++) b[i] = (mod+2 - 1ll * ta[i] * b[i] % mod) * b[i] % mod;
	dft(b, l, 1);
}
void Inv(int *a, int n, int *b, int m)
{
	assert(a[0] > 0);
	static int ta[poly_max];
	Inv_do(a, n, ta, m);
	memcpy(b, ta, m<<2);
}

void Derive(int *a, int *b, int n)
{
	for(int i=1; i<n; i++) b[i-1] = 1ll * a[i] * i % mod;
	b[n-1] = 0;
}
void Integral(int *a, int *b, int n)
{
	static int inv[poly_max]; static bool fb = 0;
	if(!fb)
	{
		fb = 1;
		inv[1] = 1;
		for(int i=2; i < poly_max; i++) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
	}
	for(int i = n-2; i>=0; i--) b[i+1] = 1ll * a[i] * inv[i+1] % mod;
	b[0] = 0;
}

void Ln(int*a, int n, int*b, int m)
{
	assert(a[0] == 1);
	static int ta[poly_max], tb[poly_max];
	Inv(a, n, tb, m);
	if(n < m)
	{
		Derive(a, ta, n);
		memset(ta+n, 0, (m-n)<<2);
	}
	else Derive(a, ta, m);
	Mult(ta, m-1, tb, m-1, tb, m-1);
	Integral(tb, b, m);
}
void Exp_do(int *a, int n, int *b, int m)
{
	if(m == 1)
	{
		b[0] = 1;
		return;
	}
	if(n > m) n = m;
	int nl = (m+1) / 2;
	Exp_do(a, n, b, nl);
	static int ta[poly_max];
	Ln(b, nl, ta, m);
	for(int i=0; i<m; i++)
	{
		ta[i] = (i<n ? a[i] : 0) - ta[i];
		if(ta[i] < 0) ta[i] += mod;
	}
	ta[0]++; if(ta[0] == mod) ta[0] = 0;
	Mult(b, m, ta, m, b, m);
}
void Exp(int *a, int n, int *b, int m)
{
	assert(a[0] == 0);
	static int ta[poly_max];
	Exp_do(a, n, ta, m);
	memcpy(b, ta, m<<2);
}

void Pow(int *a, int n, int *b, int m, int k)
{
	int fir = 0;
	while(fir < n && a[fir] == 0) fir++;
	if(fir == n || 1ll * k * fir >= m)
	{
		memset(b, 0, m<<2);
		return;
	}
	static int ta[poly_max];
	n -= fir; m -= fir * k;
	memcpy(ta, a + fir, n<<2);
	int coef = qpow(ta[0], k), rcoef = qpow(ta[0], mod - 2);
	for(int i=0; i<n; i++) ta[i] = 1ll * ta[i] * rcoef % mod;
	Ln(ta, n, ta, m);
	for(int i=0; i<m; i++) ta[i] = 1ll * ta[i] * k % mod;
	Exp(ta, m, ta, m);
	memset(b, 0, (fir*k)<<2);
	for(int i=0; i<m; i++) b[i+fir*k] = 1ll * ta[i] * coef % mod;
}

}; // namespace Poly

int a[200111], n, k;
int main()
{
	scanf("%d%d", &n, &k);
	for(int i=0; i<n; i++) scanf("%d", a+i);
	
	Poly::Pow(a, n, a, n, k);
	for(int i=0; i<n; i++) printf("%d%c", a[i], i == n ? '\n' : ' ');
	return 0;
}