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
int dp0u[NOV];
int dp0s[NOV];
int dp1f[NOV];
int dp1r[NOV];
int dp1b[NOV];

int min(int a, int b, int c)
{
	return min(a, min(b, c));
}

int min(int a, int b, int c, int d)
{
	return min(a, min(b, c, d));
}

void dispNum(int x) {
	if(x >= INF)
		cout<<"INF";
	else if(x == -1)
		cout<<"NULL";
	else
		cout<<x;
}

void dispState(int u)
{
	cout<<"After finishing function call for "<<u<<":"<<endl;
	cout<<"Vertex\t0U\t0S\t1F\t1R\t1B"<<endl;
	for(int i=1; i<=n; i++) {
		cout<<i<<"\t";
		dispNum(dp0u[i]);
		cout<<"\t";
		dispNum(dp0s[i]);
		cout<<"\t";
		dispNum(dp1f[i]);
		cout<<"\t";
		dispNum(dp1r[i]);
		cout<<"\t";
		dispNum(dp1b[i]);
		cout<<endl;
	}
	cout<<endl;
}

void super_domination_dp(int u, int par)
{
	cout<<"Calling function for "<<u<<endl<<endl;
	if(tree[u].size()==0 || (tree[u].size()==1 && tree[u][0]==par) )
	{
		dp0u[u] = 0;
		dp0s[u] = INF;
		dp1f[u] = 1;
		dp1r[u] = INF;
		dp1b[u] = INF;
		dispState(u);
		return;
	}
	
	for(int c:tree[u])
	{
		if(c!=par)
			super_domination_dp(c, u);
	}
	
	dp0u[u] = 0;
	for(int c:tree[u])
	{
		if(c!=par)
			dp0u[u] += min(dp0s[c], dp1b[c]);
	}
	
	dp0s[u] = INF;
	for(int c:tree[u])
	{
		if(c!=par)
		{
			int tempdp = 0;
			tempdp = dp1f[c];
			for(int x:tree[u])
			{
				if(x!=par && x!=c)
					tempdp += min(dp0s[x], dp1f[x], dp1b[x]);
			}
			dp0s[u] = min(dp0s[u], tempdp);
		}
	}
	
	dp1f[u] = 1;
	for(int c:tree[u])
	{
		if(c!=par)
			dp1f[u] += min(dp1f[c], dp1r[c], dp1b[c]);
	}
	
	dp1r[u] = INF;
	for(int c:tree[u])
	{
		if(c!=par)
		{
			int tempdp = 0;
			tempdp = dp0u[c];
			for(int x:tree[u])
			{
				if(x!=par && x!=c)
					tempdp += min(dp1f[x], dp1r[x], dp1b[x]);
			}
			dp1r[u] = min(dp1r[u], tempdp);
		}
	}
	dp1r[u]++;
	
	dp1b[u] = INF;
	for(int c:tree[u])
	{
		if(c!=par)
		{
			int tempdp = 0;
			tempdp = dp0s[c];
			for(int x:tree[u])
			{
				if(x!=par && x!=c)
					tempdp += min(dp0s[x], dp1f[x], dp1b[x], dp1r[x]);
			}
			dp1b[u] = min(dp1b[u], tempdp);
		}
	}
	dp1b[u]++;
	
	dispState(u);
}

int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		tree[u].pb(v);
		tree[v].pb(u);
	}
	
	for(int i=1;i<=n;i++) {
		dp0u[i] = -1;
		dp0s[i] = -1;
		dp1f[i] = -1;
		dp1r[i] = -1;
		dp1b[i] = -1;
	}
	
	auto start = high_resolution_clock::now(); 
	super_domination_dp(1, -1);
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<microseconds>(stop - start); 
	
	cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
	
	int ans = dp0s[1];
	ans = min(ans, dp1f[1]);
	ans = min(ans, dp1r[1]);
	ans = min(ans, dp1b[1]);
	
	cout<<"Super domination number = "<<ans<<endl;
	return 0;
}
