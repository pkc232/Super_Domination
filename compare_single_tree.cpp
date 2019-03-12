#include <bits/stdc++.h>
#define pb push_back
#include <chrono> 
using namespace std;
using namespace std::chrono;

#define NOV 30
#define INF 1000005


int wnbrs[NOV], bnbrs[NOV];
int done[NOV];
int dmval;
vector<int> val(NOV);
vector<vector<int> >DS;

vector<int> tree[NOV];
int n;

// DP States
int dp00[NOV];
int dp01[NOV];
int dp10[NOV];
int dp1r[NOV];
int dp1u[NOV];

int min(int a, int b, int c)
{
	return min(a, min(b, c));
}

int min(int a, int b, int c, int d)
{
	return min(a, min(b, c, d));
}

int is_super_dominated(){
	memset(done, 0 ,sizeof(done));
	memset(wnbrs, 0, sizeof(wnbrs));
	for(int i=1;i<=n;i++){
		if(val[i] == 1)
		{
			done[i] = 1;
			for(int v:tree[i])
			{
				if(val[v] == 0)
					wnbrs[i]++;
			}
		}
	}

	for(int i=1;i<=n;i++){
		if(val[i] == 0)
		{
			for(int v:tree[i])
			{
				if(val[v] == 1){
					if(wnbrs[v] == 1){
						done[i]=1;
						break;
					}
				}
			}
		}
	}

	int cnt = 0;
	for(int i=1;i<=n;i++)
		cnt += done[i];

	return (cnt == n);
}

int domination_val(){
	int cnt = 0;
	for(int i=1;i<=n;i++)
		cnt += val[i];
	return cnt;
}

void super_domination(int u){
	if(u == n+1)
	{
		if(is_super_dominated())
		{
			int x = domination_val();
			if(x<dmval)
			{
				dmval = x;
				DS.clear();
				DS.pb(val);
			}
			else if(x==dmval)
				DS.pb(val);

		}
		return;
	}

	val[u] = 0;
	super_domination(u+1);
	val[u] = 1;
	super_domination(u+1);
}

void super_domination_dp(int u, int par)
{
	if(tree[u].size()==0 || (tree[u].size()==1 && tree[u][0]==par) )
	{
		dp00[u] = 0;
		dp01[u] = INF;
		dp10[u] = 1;
		dp1r[u] = INF;
		dp1u[u] = INF;
		return;
	}
	
	for(int c:tree[u])
	{
		if(c!=par)
			super_domination_dp(c, u);
	}
	
	dp00[u] = 0;
	for(int c:tree[u])
	{
		if(c!=par)
			dp00[u] += min(dp01[c], dp1u[c]);
	}
	
	dp01[u] = INF;
	for(int c:tree[u])
	{
		if(c!=par)
		{
			int tempdp = 0;
			tempdp = dp10[c];
			for(int x:tree[u])
			{
				if(x!=par && x!=c)
					tempdp += min(dp01[x], dp10[x], dp1u[x]);
			}
			dp01[u] = min(dp01[u], tempdp);
		}
	}
	
	dp10[u] = 1;
	for(int c:tree[u])
	{
		if(c!=par)
			dp10[u] += min(dp10[c], dp1r[c], dp1u[c]);
	}
	
	dp1r[u] = INF;
	for(int c:tree[u])
	{
		if(c!=par)
		{
			int tempdp = 0;
			tempdp = dp00[c];
			for(int x:tree[u])
			{
				if(x!=par && x!=c)
					tempdp += min(dp10[x], dp1r[x], dp1u[x]);
			}
			dp1r[u] = min(dp1r[u], tempdp);
		}
	}
	dp1r[u]++;
	
	dp1u[u] = INF;
	for(int c:tree[u])
	{
		if(c!=par)
		{
			int tempdp = 0;
			tempdp = dp01[c];
			for(int x:tree[u])
			{
				if(x!=par && x!=c)
					tempdp += min(dp01[x], dp10[x], dp1u[x], dp1r[x]);
			}
			dp1u[u] = min(dp1u[u], tempdp);
		}
	}
	dp1u[u]++;
}

int main(){
	while(cin>>n)
	{
		for(int i=1;i<=n;i++)
			tree[i].clear();
		for(int i=1;i<n;i++){
			int u,v;
			cin>>u>>v;
			tree[u].pb(v);
			tree[v].pb(u);
		}
		
		super_domination_dp(1, -1);
		dmval = INF;
		super_domination(1);
		
		int dpans = dp01[1];
		dpans = min(dpans, dp10[1]);
		dpans = min(dpans, dp1r[1]);
		dpans = min(dpans, dp1u[1]);
		
		cout<<"Brute force ans = "<<dmval<<endl;
		cout<<"DP ans = "<<dpans<<endl;
		
		cout<<"\n\n\n";
		
		if(dpans==dmval)
			cout<<"Match\n";
		else
		{
			cout<<"Not match\n";
			exit(1);
		}
	}
	
	return 0;
}
