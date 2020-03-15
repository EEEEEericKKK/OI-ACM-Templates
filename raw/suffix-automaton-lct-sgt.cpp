// This amazing code is by Eric Sunli Chen.
#include<bits/stdc++.h>
using namespace std;
template<typename T> bool get_int(T &x)
{
	char t=getchar();
	bool neg=false;
	x=0;
	for(; (t>'9'||t<'0')&&t!='-'&&t!=EOF; t=getchar());
	if(t=='-')neg=true,t=getchar();if(t==EOF)return false;
	for(; t<='9'&&t>='0'; t=getchar())x=x*10+t-'0';
	if(neg)x=-x;return true;
}
template<typename T> void print_int(T x)
{
	if(x<0)putchar('-'),x=-x;
	short a[20]= {},sz=0;
	while(x>0)a[sz++]=x%10,x/=10;
	if(sz==0)putchar('0');
	for(int i=sz-1; i>=0; i--)putchar('0'+a[i]);
}
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define get1(a) get_int(a)
#define get2(a,b) (get1(a)&&get1(b))
#define get3(a,b,c) (get1(a)&&get2(b,c))
#define printendl(a) print_int(a),puts("")
typedef unsigned long long LL;
typedef pair<int,int> pii;
const int inf=0x3f3f3f3f;
const LL Linf=1ll<<61;
const double pi=acos(-1.0);

const int maxn=200111;

namespace SAM
{
	int go[maxn][26],tot,val[maxn],fa[maxn],rt;
	
	int newnode(int x){tot++;val[tot]=x;return tot;}
	int append(int p,int c)
	{
		int np=newnode(val[p]+1);
		while(p&&!go[p][c])
		{
			go[p][c]=np;
			p=fa[p];
		}
		if(!p)fa[np]=1;
		else
		{
			int q=go[p][c];
			if(val[q]==val[p]+1)fa[np]=q;
			else
			{
				int nq=newnode(val[p]+1);
				
				memcpy(go[nq],go[q],sizeof(go[q]));
				fa[nq]=fa[q];
				fa[q]=fa[np]=nq;
				
				while(p&&go[p][c]==q)
				{
					go[p][c]=nq;
					p=fa[p];
				}
			}
		}
		return np;
	}
	void prework()
	{
		rt=newnode(0);
	}
};

#define ls (t<<1)
#define rs ((t<<1)|1)
namespace SGT
{
	struct node
	{
		int l,r;
		LL delta,s1,s2;
		node(){delta=s1=s2=0;}
		void add(int v)
		{
			delta+=v;
			s1+=(LL)(r-l+1)*v;
			s2+=(LL)(r-l+1)*(l+r)/2*v;
		}
	};
	node seg[300111];
	
	void build(int l,int r,int t)
	{
		seg[t].l=l;seg[t].r=r;
		if(l==r)return;
		int mid=(l+r)>>1;
		build(l,mid,ls);
		build(mid+1,r,rs);
	}
	void push(int t)
	{
		if(seg[t].delta)
		{
			seg[ls].add(seg[t].delta);
			seg[rs].add(seg[t].delta);
			seg[t].delta=0;
		}
	}
	void pull(int t)
	{
		seg[t].s1=seg[ls].s1+seg[rs].s1;
		seg[t].s2=seg[ls].s2+seg[rs].s2;
	}
	void add(int l,int r,int v,int t)
	{
		if(l>r)return;
		//if(t==1)printf("add %d %d v= %d\n",l,r,v);
		if(l<=seg[t].l&&r>=seg[t].r)
		{
			seg[t].add(v);
			return;
		}
		push(t);
		int mid=(seg[t].l+seg[t].r)>>1;
		if(l<=mid)add(l,r,v,ls);
		if(r>mid)add(l,r,v,rs);
		pull(t);
	}
	LL query1(int l,int r,int t)
	{
		if(l<=seg[t].l&&r>=seg[t].r)return seg[t].s1;
		push(t);
		int mid=(seg[t].l+seg[t].r)>>1;LL ret=0;
		if(l<=mid)ret+=query1(l,r,ls);
		if(r>mid)ret+=query1(l,r,rs);
		return ret;
	}
	LL query2(int l,int r,int t)
	{
		if(l<=seg[t].l&&r>=seg[t].r)return seg[t].s2;
		push(t);
		int mid=(seg[t].l+seg[t].r)>>1;LL ret=0;
		if(l<=mid)ret+=query2(l,r,ls);
		if(r>mid)ret+=query2(l,r,rs);
		return ret;
	}
};

struct node
{
	int ch[2],fa,v;
	node(){ch[0]=ch[1]=fa=v=0;}
};
node a[maxn];
int gettp(int o){return a[a[o].fa].ch[0]==o?0:a[a[o].fa].ch[1]==o?1:-1;}
void rotate(int o,int d)
{
	int k1=a[o].ch[d],k2=a[k1].ch[d^1];
	if(gettp(o)!=-1)a[a[o].fa].ch[gettp(o)]=k1;
	a[o].ch[d]=k2;a[k1].ch[d^1]=o;
	a[k1].fa=a[o].fa;a[o].fa=k1;a[k2].fa=o;
}
void splay(int o)
{
	int tmp=o;while(gettp(tmp)!=-1)tmp=a[tmp].fa;
	a[o].v=a[tmp].v;
	while(gettp(o)!=-1)
	{
		int f1=a[o].fa,f2=a[f1].fa,t1=gettp(o),t2=gettp(f1);
		if(t2==-1||f2==0)rotate(f1,t1);
		else if(t1==t2){rotate(f2,t2);rotate(f1,t1);}
		else{rotate(f1,t1);rotate(f2,t2);}
	}
}

void access(int o,int nv)
{
	int k=0;
	while(o)
	{
		splay(o);int lastv=a[o].v,rt=a[o].fa;
		
		if(lastv)SGT::add(lastv-SAM::val[o]+1,lastv-SAM::val[rt],-1,1);
		if(nv)SGT::add(nv-SAM::val[o]+1,nv-SAM::val[rt],1,1);
		
		if(a[o].ch[1])a[a[o].ch[1]].v=lastv;
		a[o].ch[1]=k;k=o;o=a[o].fa;
	}
	a[k].v=nv;
}

char s[maxn];
int pos[maxn],len[maxn],n;

int main()
{
	scanf("%s",s+1);n=strlen(s+1);
	
	SAM::prework();
	pos[0]=SAM::rt;
	
	LL sum=0;
	for(int i=1;i<=n;i++)
	{
		pos[i]=SAM::append(pos[i-1],s[i]-'a');
		len[i]=SAM::val[pos[i]]-SAM::val[SAM::fa[pos[i]]];
		sum+=len[i];
	}
	
	for(int i=2;i<=SAM::tot;i++)a[i].fa=SAM::fa[i];
	
	SGT::build(1,n,1);
	
	LL ans=0;
	for(int i=1;i<=n;i++)
	{
		access(pos[i],i);
		if(len[i]>1)ans+=SGT::query2(1,len[i]-1,1);
		ans+=SGT::query1(len[i],i,1)*len[i];
	}
	ans-=sum;
	if(sum&1)ans=sum*((sum-1)/2)-ans;
	else ans=(sum/2)*(sum-1)-ans;
	printf("%I64u\n",ans);
	
	return 0;
}
