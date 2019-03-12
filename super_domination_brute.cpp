#include <bits/stdc++.h>
#define pb push_back
#include <chrono> 
using namespace std;
using namespace std::chrono;

#define NOV 30

vector<int> tree[NOV];
int wnbrs[NOV], bnbrs[NOV];
int done[NOV];
int n;
int dmval;
vector<int> val(NOV);
vector<vector<int> >DS;

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

int main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		tree[u].pb(v);
		tree[v].pb(u);
	}
	dmval = INT_MAX;
	auto start = high_resolution_clock::now(); 
	super_domination(1);
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<microseconds>(stop - start); 
	cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
	cout<<"Minimum super DOminating Sets\n";

	for(auto v:DS){
		cout<<":::"<<endl;
		for(int i=1;i<=n;i++){
			cout<<v[i]<<" ";
		}
		cout<<endl<<endl;
	}
	cout<<dmval<<endl;
	return 0;
}