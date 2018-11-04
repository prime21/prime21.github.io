#include <bits/stdc++.h>
using namespace std;

#define REP(I,A,B) for (int I=(A),I##_END_=(B);I<=I##_END_;I++)
#define FOR(I,A,B) for (int I=(A),I##_END_=(B);I<I##_END_;I++)
#define REPD(I,A,B) for (int I=(A),I##_END_=(B);I>=I##_END_;I--)

const int MAXN = 202020;

struct state{
	int l,r,vl;
	state(){}
	state(int l,int r,int vl){ this->l = l; this->r = r; this  -> vl = vl;}
};

int n,m;
vector<state> v[7070];

int l[MAXN];
int r[MAXN];

void solve(int lvl,int now){
	set<int> color;
	int L=now,R=now;
	REP(i,lvl,n)
	{
		for (auto &cur: v[i])
		if(cur.l<=R && cur.r >=L)
			color.insert(cur.vl);
		if (l[L]) L=l[L]; else L=r[L];
		R=r[R];
	}
	printf("%d\n",color.size());
}

void init(){
	scanf("%d%d",&n,&m);
}
void work(){
	int kd;
	int lvl,l,r,x;
	REP(i,1,m)
	{
		scanf("%d",&kd);
		if (kd==1)
		{
			scanf("%d",&lvl);
			scanf("%d%d%d",&l,&r,&x);
			v[lvl].push_back(state(l,r,x));
		}
		else
		{
			scanf("%d%d",&lvl,&x);
			solve(lvl,x);
		}
	}
}

void prepare(){
	int cnt=0;
	for (int i=1;i<MAXN;i++)
	if (i&(i-1))
		r[i]=++cnt;
	else
		l[i]=++cnt,
		r[i]=++cnt;
}

int main(){
	prepare();
	init();
	work();
	return 0;
}
