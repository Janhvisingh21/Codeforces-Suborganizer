// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
#define int long long int

int32_t main() {
	int t;
	cin>>t;
	int num = 0;
	vector<string>dp(1e6+10,"NO");
	for(int k=2;k<=1e6;k++){
		int node = k+1;
		int cur = k;
		while(cur*k <= 1e6 && node<=1e6 && node>0){
			// cout<<node<<"\n";
			node += (cur*k);
			cur*=k;
			if(node<=1e6) dp[node] = "YES"; 
		}
	}
	while(t--){
		int n;
		cin>>n;
		cout<<dp[n]<<"\n";
	}
	return 0;
}
