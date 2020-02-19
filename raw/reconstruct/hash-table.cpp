#include <bits/stdc++.h>

constexpr int hash_mod=233333;
constexpr int hash_maxn=2333333;

typedef int val_t;
typedef long long q_t;

struct hash_table
{
	int head[hash_mod], nxt[hash_maxn], tot;
	val_t a[hash_maxn];
	q_t val[hash_maxn];
	void clear(){memset(head,0,sizeof(head));tot=0;}
	hash_table(){clear();}
	val_t &operator[](const q_t&x)
	{
		int tx=x%hash_mod;
		for(int i=head[tx];i;i=nxt[i])if(val[i]==x)return a[i];
		nxt[++tot]=head[tx];head[tx]=tot;val[tot]=x;a[tot]=0;
		return a[tot];
	}
	val_t find(const q_t&x)const
	{
		int tx=x%hash_mod;
		for(int i=head[tx];i;i=nxt[i])if(val[i]==x)return a[i];
		return 0;
	}
};

int main()
{
	return 0;
}