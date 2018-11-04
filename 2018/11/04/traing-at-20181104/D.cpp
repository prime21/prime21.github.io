#include <bits/stdc++.h>

#define REP(I,A,B) for (int I=(A),I##_END_=(B);I<=I##_END_;I++)
#define FOR(I,A,B) for (int I=(A),I##_END_=(B);I<I##_END_;I++)
#define REPD(I,A,B) for (int I=(A),I##_END_=(B);I>=I##_END_;I--)

using namespace std;

const int MAXN = 71;

char mm[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN];

struct sta{
	int x,y,z;
	sta(){}
	sta(int x,int y,int z): x(x),y(y),z(z) {}
	void sort(){
		if (this->x > this->y)
			swap(this->x,this->y);
		if (this->x > this->z)
			swap(this->x,this->z);
		if (this->y > this->z)
			swap(this->y,this->z);
	}
};
sta fa[MAXN][MAXN][MAXN];
sta start;

queue<sta> Q;

int n;
int sx,sy,sz;

void init(){
	scanf("%d",&n);
	scanf("%d%d%d",&sx,&sy,&sz);
	REP(i,1,n)
		scanf("%s",mm[i]+1);
}

inline void upd(const sta&now,const sta&nxt,int vl){
	if (dp[nxt.x][nxt.y][nxt.z]==-1)
	{
		fa[nxt.x][nxt.y][nxt.z]=now;
		dp[nxt.x][nxt.y][nxt.z]=vl;
		Q.push(nxt);
	}
}

int move(int xx,int yy,int za,int zb){
	return mm[xx][yy] == mm[za][zb];
}

void print(sta now){
	if (now.x == start.x && now.y ==start.y && now.z==start.z)
		return ;
	sta pre;
	print(pre=fa[now.x][now.y][now.z]);

	if (pre.x!=now.x && pre.x!=now.y && pre.x!=now.z)
		printf("%d ",pre.x);
	if (pre.y!=now.x && pre.y!=now.y && pre.y!=now.z)
		printf("%d ",pre.y);
	if (pre.z!=now.x && pre.z!=now.y && pre.z!=now.z)
		printf("%d ",pre.z);


	if (now.x!=pre.x && now.x!=pre.y && now.x!=pre.z)
		printf("%d\n",now.x);
	if (now.y!=pre.x && now.y!=pre.y && now.y!=pre.z)
		printf("%d\n",now.y);
	if (now.z!=pre.x && now.z!=pre.y && now.z!=pre.z)
		printf("%d\n",now.z);

}

void work(){
	sta now = sta(sx,sy,sz);
	sta nxt;
	int VL;
	now.sort();
	start=now;
	memset(dp,-1,sizeof dp);
	dp[now.x][now.y][now.z]=0;
	Q.push(now);

	while (!Q.empty())
	{
		now =Q.front();
		VL=dp[now.x][now.y][now.z]+1;
		Q.pop();
		REP(i,1,n)
		if (i!=now.x && i!=now.y && i!=now.z)
		{
			if (move(now.x,now.y, now.z,i))
			{
				nxt=now;
				nxt.z=i;
				nxt.sort();
				upd(now,nxt,VL);
			}
			if (move(now.z,now.y, now.x,i))
			{
				nxt=now;
				nxt.x=i;
				nxt.sort();
				upd(now,nxt,VL);
			}
			if (move(now.x,now.z, now.y,i))
			{
				nxt=now;
				nxt.y=i;
				nxt.sort();
				upd(now,nxt,VL);
			}
		}
	}

	printf("%d\n",dp[1][2][3]);
	if (dp[1][2][3]!=-1)
		print(sta(1,2,3));
}

int main(){
	init();
	work();
	return 0;
}
