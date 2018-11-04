#include <bits/stdc++.h>

#define REP(I,A,B) for (int I=(A),I##_END_=(B);I<=I##_END_;I++)
#define FOR(I,A,B) for (int I=(A),I##_END_=(B);I<I##_END_;I++)
#define REPD(I,A,B) for (int I=(A),I##_END_=(B);I>=I##_END_;I--)
#define sqr(X) ((X)*(X))

inline void upd(double &x,const double &y) {
	if (x<y) x=y;
}

using namespace std;

const int MAXS = (1<<20)+5;
const int MAXN = 22;
const double pi = acos(-1);
const double eps=1e-8;

struct node{
	int x,y;
	double a;
}v[MAXN];

int l,r,n;
int all;
double dp[MAXS];

double make(double cur,int id){
	double dis = sqrt( sqr(v[id].x-cur) + sqr(v[id].y) );
	double beta = atan2( v[id].y, v[id].x-cur );
	double gama = pi - v[id].a - beta;
	if (gama<eps){
		printf("%.10lf\n",(r-l)*1.);
		exit(0);
	}
	double len = dis * sin(v[id].a) / sin(gama);

	if (cur+len>=r-eps)
	{
		printf("%.10lf",(r-l)*1.);
		exit(0);
	}
	return cur+len;
}

void init(){
	scanf("%d%d%d",&n,&l,&r);
	int ange;
	all=(1<<n)-1;
	FOR(i,0,n)
	{
		scanf("%d%d%d",&v[i].x,&v[i].y,&ange);
		v[i].a= ange*1./180*pi;
	}
}

void work(){
	REP(s,0,all) dp[s]=l;

	REP(s,0,all)
	FOR(i,0,n)
	if ( (( s>>i ) &1)  ==0)
		upd( dp[s|(1<<i)], make(dp[s],i) );
	printf("%.10lf\n",dp[all]-l);
}

int main(){
	init();
	work();
	return 0;
}
