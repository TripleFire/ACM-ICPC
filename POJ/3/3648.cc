/*
* 2-SAT 输出解问题
* 一对(h,w)不能在一边，给出的通奸关系也不能在一边
* 输出解时，(i)为h,(i+n)为w
*/

//Result:wizmann	3648	Accepted	288K	16MS	C++	3133B	2012-10-16 13:59:03
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x

#define NODE 1010
#define EDGE 300100

struct _link
{
	int val,next;
	_link(){}
	_link(int ival,int inext)
	{
		val=ival;
		next=inext;
	}
};

struct linklist
{
	int head[NODE],ind;
	_link edge[EDGE];

	inline void init()
	{
		memset(head,-1,sizeof(head));
		ind=0;
	}
	inline void addEdge(int a,int b)
	{
		edge[ind]=_link(b,head[a]);
		head[a]=ind++;
	}
};


int n,m;

char instack[NODE];
stack<int> st;
int dfn[NODE],scc[NODE],num[NODE],low[NODE];
int sccnr,nr;
linklist g,sccg;


void init()
{
	memset(instack,0,sizeof(instack));
	memset(scc,0,sizeof(scc));
	memset(num,0,sizeof(num));
	memset(low,0,sizeof(low));
	memset(dfn,0,sizeof(dfn));
	st=stack<int>();
	nr=1;sccnr=0;
	g.init();
}

void tarjan(int pos)
{
	low[pos]=dfn[pos]=nr++;
	st.push(pos);
	instack[pos]=1;

	for(int i=g.head[pos];i!=-1;i=g.edge[i].next)
	{
		int j=g.edge[i].val;
		if(!dfn[j])
		{
			tarjan(j);
			low[pos]=min(low[pos],low[j]);
		}
		else if(instack[j])
		{
			low[pos]=min(low[pos],dfn[j]);
		}
	}

	if(dfn[pos]==low[pos])
	{
		sccnr++;
		while(1)
		{
			int t=st.top();
			instack[t]=0;
			st.pop();
			scc[t]=sccnr;
			num[sccnr]++;
			if(t==pos) break;
		}
	}
}

bool slove()
{
	for(int i=0;i<n*2;i++)
	{
		if(!dfn[i]) tarjan(i);
	}
	for(int i=0;i<n;i++)
	{
		if(scc[i]==scc[i+n]) return false;
	}
	return true;
}

void printAns()
{
	int fami[NODE]={0};
	int in[NODE]={0};
	int mark[NODE]={0};
	sccg.init();

	for(int i=0;i<n;i++)
	{
		fami[scc[i]]=scc[i+n];
		fami[scc[i+n]]=scc[i];
	}
	for(int i=0;i<2*n;i++)
	{
		for(int j=g.head[i];j!=-1;j=g.edge[j].next)
		{
			if(scc[i]!=scc[g.edge[j].val])
			{
				sccg.addEdge(scc[i],scc[g.edge[j].val]);
				in[scc[g.edge[j].val]]++;
			}
		}
	}
	queue<int> q;

	for(int i=1;i<=sccnr;i++)
	{
		if(!in[i]) q.push(i);
	}
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		if(!mark[now])
		{
			mark[now]=1;
			mark[fami[now]]=-1;
		}
		for(int i=sccg.head[now];i!=-1;i=sccg.edge[i].next)
		{
			int next=sccg.edge[i].val;
			if(--in[next]==0) q.push(next);
		}
	}

	for(int i=1;i<n;i++)
	{
		if(i>1) printf(" ");
		if(mark[scc[i]]==-1) printf("%dw",i);
		else printf("%dh",i);
	}
	puts("");
}

int main()
{
	int a,b;
	char aa,bb;
	while(input(n>>m) && n+m)
	{
		init();
		g.addEdge(n,0);//The husband must in the group
		while(m--)
		{
			scanf("%d%c %d%c",&a,&aa,&b,&bb);
			if(aa=='h' && bb=='h')
			{
				g.addEdge(a,b+n);
				g.addEdge(b,a+n);
			}
			else if(aa=='w' && bb=='w')
			{
				g.addEdge(a+n,b);
				g.addEdge(b+n,a);
			}
			else if(aa=='h' && bb=='w')
			{
				g.addEdge(a,b);
				g.addEdge(b+n,a+n);
			}
			else if(aa=='w' && bb=='h')
			{
				g.addEdge(b,a);
				g.addEdge(a+n,b+n);
			}
		}

		if(!slove()) puts("bad luck");
		else printAns();
	}
	return 0;
}
