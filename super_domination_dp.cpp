#include <bits/stdc++.h>
#define pb push_back
#include <chrono> 
using namespace std;
using namespace std::chrono;

#define NOV 30
#define INF 1000005

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
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		tree[u].pb(v);
		tree[v].pb(u);
	}
	
	auto start = high_resolution_clock::now(); 
	super_domination_dp(1, -1);
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<microseconds>(stop - start); 
	
	cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
	
	int ans = dp01[1];
	ans = min(ans, dp10[1]);
	ans = min(ans, dp1r[1]);
	ans = min(ans, dp1u[1]);
	
	cout<<"Super domination number = "<<ans<<endl;
	return 0;
}
