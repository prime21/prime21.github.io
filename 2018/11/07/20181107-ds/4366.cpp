#include <bits/stdc++.h>

#define REP(I,A,B) for (int I=(A),I##_END_=(B);I<=I##_END_;I++)
#define FOR(I,A,B) for (int I=(A),I##_END_=(B);I<I##_END_;I++)
#define REPD(I,A,B) for (int I=(A),I##_END_=(B);I>=I##_END_;I--)

using namespace std;


int v[MAXN];
int p[MAXN];
int o[MAXN];
int n,m;
int qry[MAXN];

int st[MAXN<<1]={0};

void init(){
	scanf("%d%d",&n,&m);

	REP(i,1,n) qry[i]=0,o[i]=i;
	REP(i,0,n+n) st[i]=0;

	REP(i,1,n) 
}

void dfs(int p){
	
}

int main(){
	int _=0;
	REP(__,1,_)
	{
		init();
		dfs(1);
	}
	return 0;
}
