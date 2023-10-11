// Source: https://usaco.guide/general/io
#include <bits/stdc++.h>
using namespace std;
#define int long long
void dfs(int node,int par,vector<vector<int>>&g,vector<int>&subtree){
	for(int child:g[node]){
		if(child==par) continue;
		dfs(child,node,g,subtree);
		subtree[node] += subtree[child];
	}
	if(subtree[node] == 0) subtree[node] = 1;
	return;
}
int32_t main() {
    int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		vector<int>subtree(n+1,0);
		vector<vector<int>>g(n+1);
		for(int i=1;i<n;i++){
			int u,v;
			cin>>u>>v;
			g[v].push_back(u);
			g[u].push_back(v);
		}
		dfs(1,0,g,subtree);
		int q;
		cin>>q;
		while(q--){
			int u,v;
			cin>>u>>v;
			cout<<subtree[u]*subtree[v]<<endl;
		}
	}
	return 0;
}
