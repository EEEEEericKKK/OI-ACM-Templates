#include <bits/stdc++.h>

namespace FFT
{

constexpr int poly_bits= 17;
constexpr int poly_max = 1<<poly_bits;
constexpr double pi = std::acos(-1.0);
struct cpx
{
	double x,y;
	cpx(double _x=0,double _y=0){x=_x;y=_y;}
	cpx operator+(const cpx &t){return cpx(x+t.x,y+t.y);}
	cpx operator-(const cpx &t){return cpx(x-t.x,y-t.y);}
	cpx operator*(const cpx &t){return cpx(x*t.x-y*t.y,x*t.y+y*t.x);}
	cpx operator*(const double &t){return cpx(x*t,y*t);}
	cpx conj()const{return cpx(x,-y);}
	cpx inv()const{return cpx(x/(x*x+y*y),-y/(x*x+y*y));}
};

inline void dft(cpx *a, int n, bool inv = 0)
{
	static cpx w[poly_max+1],cw[poly_max+1];
	static bool fb = true;
	if(fb)
	{
		fb = false;
		for(int i=0;i<=poly_max;i++)w[i]=cpx(std::cos(2*pi/poly_max*i),std::sin(2*pi/poly_max*i));
	}
	
	for(int i=0,j=0;i<n;i++)
	{
		if(i<j)std::swap(a[i],a[j]);
		for(int t=n>>1;(j^=t)<t;t>>=1);
	}
	for(int l=1,d=poly_bits-1;l<n;l<<=1,d--)
	{
		int l2=l<<1;
		static cpx cw[poly_max];
		for(int j=0;j<l;j++)cw[j]=w[inv?poly_max-(j<<d):(j<<d)];
		for(int i=0;i<n;i+=l2)for(int j=0;j<l;j++)
		{
			cpx tmp=a[i|l|j]*cw[j];
			a[i|l|j]=a[i|j]-tmp;
			a[i|j]=a[i|j]+tmp;
		}
	}
	if(inv)for(int i=0;i<n;i++)a[i]=a[i]*(1.0/n);
}

}; // namespace FFT

int main()
{
	return 0;
}