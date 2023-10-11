// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;
#define int long long int


bool f(vector<string>&s,char c){
	for(int i=0;i<3;i++){
		int cnt = 0;
		for(int j=0;j<3;j++){
			cnt += (s[i][j]==c);
		}
		if(cnt==3) return true;
	}
	for(int j=0;j<3;j++){
		int cnt = 0;
		for(int i=0;i<3;i++){
			cnt += (s[i][j]==c);
		}
		if(cnt==3) return true;
	}
	if(s[0][0] == s[1][1] && s[1][1] == s[2][2] && s[2][2] == c) return true;
	if(s[0][2] == s[1][1] && s[1][1] == s[2][0] && s[2][0] == c) return true;
	return false;
}
int32_t main() {
	int t;
	cin>>t;
	while(t--){
		vector<string>s(3);
		for(int i=0;i<3;i++){
			cin>>s[i];
		}
		if(f(s,'+')){
			cout<<"+\n";
		}else if(f(s,'X')){
			cout<<"X\n";
		}else if(f(s,'O')){
			cout<<"O\n";
		}else{
			cout<<"DRAW\n";
		}

	}
	return 0;
}
