// Source: https://usaco.guide/general/io
#include <bits/stdc++.h>
using namespace std;
#define int long long
int32_t main() {
    int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		vector<int>a(n);
		int ans = 0LL;
		vector<int>v;
		for(int &x:a){
			cin>>x;
			ans+=(abs(x));
			if(x) v.push_back(x);
		}
		int cur = 0;
		int pre = 0;
		for(int x:v){
			if(x<0 && pre>=0) cur++;
			pre = x;
		}
		cout<<ans<<" "<<cur<<endl;
	}
	return 0;
}
