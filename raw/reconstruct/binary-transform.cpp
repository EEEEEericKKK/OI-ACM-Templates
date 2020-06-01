#include <bits/stdc++.h>

#define getcode(i,j) (((i)>>(j))&1)
namespace bin_conv
{

constexpr int mod = 1e9+7;
int qpow(int x,int y)
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

inline void add(int&x,int y){x+=y;if(x>=mod)x-=mod;}

//Fast Mobius transform : used in and-convolution / or-convolution
void FMT(int *a, int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<(1<<n);j++)if(getcode(j,i))
		{
			a[j] += a[j^(1<<i)];
			if(a[j] >= mod) a[j] -= mod;
		}
	}
}
void iFMT(int *a, int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<(1<<n);j++)if(getcode(j,i))
		{
			a[j] -= a[j^(1<<i)];
			if(a[j] < 0) a[j] += mod;
		}
	}
}

//Fast Walsh transform : used in xor-convolution
void FWT(int *a, int n)
{
	int l = (1<<n);
	for(int k=1; k<n; k<<=1)
	{
		for(int i=0; i<n; i+=(k<<1))for(int j=0; j<k; j++)
		{
			register int u=a[i+j], v=a[i+j+k];
			a[i+j]=u+v;if(a[i+j]>=mod)a[i+j]-=mod;
			a[i+j+k]=u-v;if(a[i+j+k]<0)a[i+j+k]+=mod;
		}
	}
}
void iFWT(int *a,int n)
{
	FWT(a,n);
	int inv = qpow((mod+1)/2,n);
	for(int i=0; i<(1<<n); i++) a[i] = 1ll*a[i]*inv % mod;
}

}; // namespace bin_conv
#undef getcode