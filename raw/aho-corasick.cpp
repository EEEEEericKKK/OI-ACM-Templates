#include <bits/stdc++.h>

const int N = 100111;
const int Sigma = 26;

int go[N][Sigma], fail[N], tot, rt;
bool match[N];
void clear()
{
	tot = rt = 1;
	memset(go[1], 0, sizeof(go[1]));
}
int append(int x, int c)
{
	if (!go[x][c])
	{
		go[x][c] = ++tot;
		memset(go[tot], 0, sizeof(go[tot]));
	}
	return go[x][c];
}
void construct(int sigma)
{
	static int q[maxn], fr, rr, fail[maxn];
	fr = rr = 0;
	q[rr++] = rt;
	for (; fr < rr; fr++)
	{
		int x = q[fr];
		for (int i = 0; i < sigma; i++)
			if (go[x][i])
			{
				int &f = fail[go[x][i]];
				if (x == rt)
					f = x;
				else
				{
					f = fail[x];
					while (f != rt && !go[f][i])
						f = fail[f];
					if (go[f][i])
						f = go[f][i];
				}
				q[rr++] = go[x][i];
			}
	}
	for (int i = 0; i < sigma; i++)
		if (!go[rt][i])
			go[rt][i] = rt;
	for (int _ = 1; _ < rr; _++)
	{
		int x = q[_];
		if (match[fail[x]])
			match[x] = 1;
		for (int i = 0; i < sigma; i++)
			if (!go[x][i])
				go[x][i] = go[fail[x]][i];
	}
}

int main()
{
	return 0;
}