// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
#define int long long int

int32_t main() {
	int t;
	cin>>t;
	while(t--){
		int n,d,h;
		cin>>n>>d>>h;
		double ans = n*d*h;
		ans /= 2.0;
		vector<int>a(n);
		for(int &x:a){
			cin>>x;
		}
		sort(a.begin(),a.end());
		int cur = 0;
		for(int x:a){
			if(x>cur){
				cur = x + h;
			}else{
				int height = cur - x;
				double base = d*height;
				base /= double(h);
				double temp_area = height*base;
				temp_area /= 2.0;
				ans -= temp_area;
				cur = x + h;
			}
		}
		cout<<fixed<<setprecision(12)<<ans<<"\n";
	}
	return 0;
}
