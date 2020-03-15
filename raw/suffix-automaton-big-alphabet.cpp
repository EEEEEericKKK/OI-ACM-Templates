#include<bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define pb push_back
#define mp make_pair

typedef unsigned uint;
typedef long long LL;
typedef unsigned long long uLL;
typedef pair<uint,uint> pii;

const uint maxn=5000111;
const uint maxv=maxn*2;
const uint maxe=maxn*3;
const uint hash_size=1<<25;

namespace hs
{
	uint head[hash_size],val[hash_size],id[hash_size];
	uint i,v,h;
	inline uint& go(const uint&x,const uint&c)
	{
		h=(x<<5)|c;i=v=h&hash_size-1;
		
		while(val[i])
		{
			if(val[i]==h)break;
			i=i+((v&1023)<<1)+1&hash_size-1;
		}
		
		if(!val[i])val[i]=h;
		return id[i];
	}
}

LL sum,ans;
uint fa[maxv],val[maxv],have[maxv],tot,p;

void append(uint c)
{
	uint np=++tot;val[np]=val[p]+1;
	while(p)
	{
		uint&tmp=hs::go(p,c);
		if(tmp)break;
		tmp=np;have[p]|=1u<<c;
		p=fa[p];
	}
	if(!p)fa[np]=1;
	else
	{
		uint q=hs::go(p,c);
		if(val[p]+1==val[q])fa[np]=q;
		else
		{
			uint nq=++tot,tmp;val[nq]=val[p]+1;
			have[nq]=tmp=have[q];
			
			while(tmp)
			{
				uint nc=__builtin_ctz(tmp);
				hs::go(nq,nc)=hs::go(q,nc);
				tmp&=tmp-1;
			}
			fa[nq]=fa[q];
			fa[q]=nq;
			fa[np]=nq;
			while(p)
			{
				uint&tmp=hs::go(p,c);
				if(tmp!=q)break;
				tmp=nq;
				p=fa[p];
			}
		}
	}
	p=np;
	sum+=val[p]-val[fa[p]];
}

char ch;
int main()
{
	p=++tot;
	while((ch=getchar())!='\n')
	{
		append(ch-'a');
		ans^=sum;
	}
	printf("%lld\n",ans);
	return 0;
}