// This amazing code is by Eric Sunli Chen.
#include <bits/stdc++.h>

const int maxn=50;
const int bsz=3;
const int bnum=1000;
const int pw10[bsz]={1,10,100};
struct bint
{
	int a[maxn/bsz+10],sz;
	void clear(){memset(a,0,sizeof(a));sz=0;}
	bint(){clear();}
	
	void push(){int c=0;for(int i=0;i<sz;i++){a[i]+=c;c=a[i]/bnum;a[i]%=bnum;if(a[i]<0){a[i]+=bnum;c--;}}while(c){a[sz++]=c%bnum;c/=bnum;}}
	void resize(){while(sz>0&&a[sz-1]==0)sz--;}
	bint(int x){clear();a[sz++]=x;push();}
	bint operator =(int x){return *this=bint(x);}
	template<typename T>bint parse(T s,int l,int r)
	{
		clear();sz=(r-l+bsz)/bsz;
		for(int i=0;i<sz;i++)for(int j=std::max(l,r-bsz*i-bsz+1);j<=r-bsz*i;j++)a[i]=a[i]*10+s[j]-'0';
		resize();return *this;
	}
	bint parse(char*s){return parse(s,0,strlen(s)-1);}
	bint parse(std::string s){return parse(s,0,(int)s.size()-1);}
	void out(char ch='\n')const
	{
		char tmp[]="%0_d";tmp[2]=bsz+'0';
		if(!sz)putchar('0');else{printf("%d",a[sz-1]);for(int i=sz-2;i>=0;i--)printf(tmp,a[i]);}
		putchar(ch);
	}
	
	bool operator ==(const bint&b)const{if(sz!=b.sz)return false;for(int i=sz-1;i>=0;i--)if(a[i]!=b.a[i])return false;}
	bool operator !=(const bint&b)const{return (*this==b)^1;}
	bool operator <(const bint&b)const{if(sz!=b.sz)return sz<b.sz;for(int i=sz-1;i>=0;i--)if(a[i]!=b.a[i])return a[i]<b.a[i];return false;}
	bool operator >(const bint&b)const{return b<*this;}
	bool operator <=(const bint&b)const{return *this<b||*this==b;}
	bool operator >=(const bint&b)const{return b<=*this;}
	
	bint operator +(const bint&b)const
	{
		bint ret;ret.sz=std::max(sz,b.sz);
		for(int i=0;i<ret.sz;i++)
		{
			if(i<sz)ret.a[i]+=a[i];
			if(i<b.sz)ret.a[i]+=b.a[i];
		}
		ret.push();return ret;
	}
	bint operator +(const int&b)const
	{
		bint ret=*this;
		if(!ret.sz&&b)ret.sz=1;
		ret.a[0]+=b;ret.push();
		return ret;
	}
	bint operator +=(const bint&b){return *this=*this+b;}
	bint operator +=(const int&b){return *this=*this+b;}
	
	bint operator -(const bint&b)const
	{
		bint ret=*this;
		for(int i=0;i<b.sz;i++)ret.a[i]-=b.a[i];
		ret.push();ret.resize();return ret;
	}
	bint operator -=(const bint&b){return *this=*this-b;}
	
	bint operator *(const bint&b)const
	{
		bint ret;ret.sz=sz+b.sz;
		for(int i=0;i<sz;i++)for(int j=0;j<b.sz;j++)ret.a[i+j]+=a[i]*b.a[j];
		ret.push();ret.resize();return ret;
	}
	bint operator *(const int&b)const
	{
		bint ret=*this;for(int i=0;i<sz;i++)ret.a[i]*=b;
		ret.push();return ret;
	}
	bint operator *=(const bint&b){return *this=*this*b;}
	bint operator *=(const int&b){return *this=*this*b;}
	
	bint operator /(const bint&b)const
	{
		bint t[bsz],ret,cur;t[0]=b;for(int i=1;i<bsz;i++)t[i]=t[i-1]*10;
		for(int i=sz-1;i>=0;i--)
		{
			cur=cur*bnum+a[i];ret*=bnum;
			for(int j=bsz-1;j>=0;j--)
			{
				while(cur>=t[j])
				{
					cur=cur-t[j];
					ret+=pw10[j];
				}
			}
		}
		return ret;
	}
	bint operator /(const int&b)const
	{
		bint ret;ret.sz=sz;long long cur=0;
		for(int i=sz-1;i>=0;i--)
		{
			ret*=bnum;cur=cur*bnum+a[i];
			ret+=cur/b;cur%=b;
		}
		ret.resize();
		return ret;
	}
	bint operator /=(const bint&b){return *this=*this/b;}
	bint operator /=(const int&b){return *this=*this/b;}
	
	bint operator %(const bint&b)const
	{
		bint t[bsz],cur;t[0]=b;for(int i=1;i<bsz;i++)t[i]=t[i-1]*10;
		for(int i=sz-1;i>=0;i--)
		{
			cur=cur*bnum+a[i];
			for(int j=bsz-1;j>=0;j--)
			{
				while(cur>=t[j])
					cur=cur-t[j];
			}
		}
		return cur;
	}
	int operator %(const int&b)const
	{
		long long cur=0;
		for(int i=sz-1;i>=0;i--)cur=(cur*bnum+a[i])%b;
		return cur;
	}
	bint operator %=(const bint&b){return *this=*this%b;}
	bint operator %=(const int&b){return *this=bint(*this%b);}
};

int main()
{
	return 0;
}
