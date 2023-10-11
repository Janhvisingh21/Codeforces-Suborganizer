// Source: https://usaco.guide/general/io
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		vector<int>a(n);
		for(int &x:a) cin>>x;
		sort(a.begin(),a.end());
		int ans = 0;
		for(int i=0;i<n/2;i++){
			ans += (a[n-i-1] - a[i]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
