// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
#define int long long int

int32_t main() {
	int t;
	cin>>t;
	while(t--){
		int n,m,h;
		cin>>n>>m>>h;
		vector<vector<int>>v(n,vector<int>(m));
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				cin>>v[i][j];
			}
			sort(v[i].begin(),v[i].end());
			for(int j=1;j<m;j++){
				v[i][j] += v[i][j-1];
				// cout<<v[i][j]<<" ";
			}
			// cout<<endl;
		}
		vector<vector<int>>a(n);
		for(int i=0;i<n;i++){
			int cur = 0;
			int cnt = 0;
			int pre = 0;
			vector<int>here(3);
			int alag = 0;
			for(int j=0;j<m;j++){
				// cout<<v[i][j]<<" ";
				cur += v[i][j];
				alag += v[i][j]-pre;
				if(alag <= h) cnt++; 
				else{
					cur -= v[i][j];
					break;
				}
				pre = v[i][j];
			}
			// cout<<cnt<<" "<<cur<<"\n";
			here[0] = -cnt;
			here[1] = cur;
			here[2] = i;
			a[i] = here;
		}
		sort(a.begin(),a.end());
		for(int i=0;i<n;i++){
			if(a[i][2] == 0){
				cout<<i+1<<"\n";
				break;
			}
		}
	}
	return 0;
}
