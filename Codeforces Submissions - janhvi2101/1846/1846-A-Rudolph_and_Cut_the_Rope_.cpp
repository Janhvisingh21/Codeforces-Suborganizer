// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
#define int long long int
int32_t main() {
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		int ans = 0;
		vector<int>v;
		for(int i=0;i<n;i++){
			int x,y;
			cin>>x>>y;
			ans += (x>y);
		}
		cout<<ans<<"\n";

	}
	return 0;
}
