#include <bits/stdc++.h>

namespace MOD_Matrix
{

constexpr int N = 10;
constexpr int mod = 1e9+7;
int Size = N;

int qpow(int x, int y)
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

struct matrix
{
	int a[N][N];
	void reset(){memset(a, 0, sizeof(a));}
	void reset(int x)
	{
		reset();
		for(int i=0; i<Size; i++) a[i][i] = x;
	}
	matrix(){reset();}
	matrix(int x){reset(x);}
	int det()const
	{
		static int tab[N][N];
		std::memcpy(tab, a, sizeof(a));
		int ret = 1;
		for(int i=0; i<Size; i++)
		{
			if(!tab[i][i])
			{
				ret = mod - ret;
				for(int j=i+1; j<Size; j++) if(tab[j][i])
				{
					for(int k=i; k<Size; k++) std::swap(tab[i][k], tab[j][k]);
					break;
				}
			}
			if(!tab[i][i]) return 0;
			ret = 1ll*ret*a[i][i]%mod;
			int inv = qpow(a[i][i], mod-2);
			for(int j=0; j<Size; j++) a[i][j] = 1ll*a[i][j]*inv%mod;
			for(int j=i+1; j<Size; j++) if(a[j][i])
			{
				int tmp = mod - a[j][i];
				for(int k=0; k<Size; k++)
					a[j][k] = (a[j][k]+1ll*a[i][k]*tmp)%mod;
			}
		}
		return ret;
	}
};

matrix operator *(const matrix&a, const matrix&b)
{
	matrix ret;
	for(int i=0;i<Size;i++)for(int k=0;k<Size;k++)if(a.a[i][k])
		for(int j=0;j<Size;j++)ret.a[i][j]=(ret.a[i][j]+1ll*a.a[i][k]*b.a[k][j])%mod;
	return ret;
}

matrix qpow(matrix x, int y)
{
	matrix ret(1);
	while(y)
	{
		if(y&1) ret = ret*x;
		x = x*x;
		y >>= 1;
	}
	return ret;
}

} // namespace MOD_Matrix

int main()
{
	return 0;
}