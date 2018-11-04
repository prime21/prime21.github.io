#include <bits/stdc++.h>

using namespace std;

#define REP(I,A,B) for (int I=(A),I##_END_=(B);I<=I##_END_;I++)
#define FOR(I,A,B) for (int I=(A),I##_END_=(B);I<I##_END_;I++)
#define REPD(I,A,B) for (int I=(A),I##_END_=(B);I>=I##_END_;I--)

const int MAXN =202020; 

struct segment_tree{
	int oc[MAXN<<2];
	void add(int p,int l,int r,int ll,int rr,int vl){
		if (l==ll && r==rr)
		{
			oc[p]+=vl;
			return ;
		}
		int mid=(l+r)/2;
		if (rr<=mid)
			add(p+p,l,mid,ll,rr,vl);
		else if (mid<ll)
			add(p+p+1,mid+1,r,ll,rr,vl);
		else
			add(p+p,l,mid,ll,mid,vl),
			add(p+p+1,mid+1,r,mid+1,rr,vl);

	}
	int find(int p,int l,int r,int x){
		if (l==r)
			return oc[p];
		int mid=(l+r)/2;
		if (x<=mid)
			return oc[p]+find(p+p,l,mid,x);
		else
			return oc[p]+find(p+p+1,mid+1,r,x);
	}
}SGT[2];

int dep[MAXN];
int L[MAXN];
int R[MAXN];
int n,m;
int a[MAXN];
int df_time=0;

vector<int> to[MAXN];

void init(){
	scanf("%d%d",&n,&m);
	REP(i,1,n) scanf("%d",a+i);
	int x,y;
	FOR(i,1,n)
	{
		scanf("%d%d",&x,&y);
		to[y].push_back(x);
		to[x].push_back(y);
	}
}

void dfs(int p,int fa=0){
	L[p]=++df_time;
	for (auto &q:to[p])
	if (q!=fa)
	{
		dep[q]=dep[p]+1;
		dfs(q,p);
	}
	R[p]=df_time;
}

void work(){
	int op,x,vl;
	REP(i,1,m)
	{
		scanf("%d%d",&op,&x);
		if (op==1)
		{
			scanf("%d",&vl);
			SGT[ dep[x]&1 ].add(1,1,n,L[x],R[x],vl);
			SGT[ (dep[x]&1)^1 ].add(1,1,n,L[x],R[x],-vl);
		}
		else
			printf("%d\n",a[x]+SGT[ dep[x]&1 ].find(1,1,n,L[x]));
	}
}

int main(){
	init();
	dep[1]=1;
	dfs(1);
	work();
	return 0;
}
