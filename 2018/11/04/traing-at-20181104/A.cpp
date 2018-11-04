#include <bits/stdc++.h>

#define REP(I,A,B) for (int I=(A),I##_END_=(B);I<=I##_END_;I++)
#define FOR(I,A,B) for (int I=(A),I##_END_=(B);I<I##_END_;I++)

using namespace std;

int n;
int a[101010];
int d[101010];

void work2(){
	set<int> ans;
	if ((a[1]+a[2])%2==0)
		ans.insert((a[1]+a[2])/2);
	ans.insert(a[1]-d[1]);
	ans.insert(a[2]+d[1]);
	printf("%d\n",ans.size());
	for (auto &now: ans)
		printf("%d ",now);
}
void work3(){
	set<int> ans;
	if (d[1]==d[2])
		ans.insert(a[1]-d[1]),
		ans.insert(a[3]+d[1]);

	if (d[1]/2 == d[2] && d[1]%2==0)
		ans.insert( (a[1]+a[2])/2 );
	
	if (d[1] == d[2]/2 && d[2]%2==0)
		ans.insert( (a[3]+a[2])/2 );
	
	printf("%d\n",ans.size());
	for (auto &now: ans)
		printf("%d ",now);

}
void work_n(){
	set<int> ans;
	map<int,int> M;
	int x,y;

	FOR(i,1,n) M[d[i]]++;

	if (M.size()==1)
	{
		ans.insert(a[1]-d[1]);
		ans.insert(a[n]+d[1]);
	}
	else if (M.size()==2)
	{
		x=0;
		FOR(i,1,n) 
			if(M[d[i]]==1) x=i;
			else y=i;

		if (d[x]/2==d[y] && d[x]%2==0) 
			ans.insert( (a[x]+a[x+1])/2 );

	}

	printf("%d\n",ans.size());
	for (auto &now: ans)
		printf("%d ",now);

}

int main(){
	scanf("%d",&n);
	REP(i,1,n) scanf("%d",a+i);
	sort(a+1,a+1+n);
	REP(i,2,n) d[i-1]=a[i]-a[i-1];

	if (n==1)
		printf("-1\n");
	else if (n==2)
		work2();
	else if (n==3)
		work3();
	else
		work_n();
	return 0;
}
