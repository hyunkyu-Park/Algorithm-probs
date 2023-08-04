//참고 https://bowbowbow.tistory.com/6
//kmp 알고리즘

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> getPi(string p) {
	
	int m = p.size();
	vector<int> pi (m,0);
	int j = 0;
	for (int i = 1; i < m; i++) {
		while (j > 0 && p[i] != p[j])
			j = pi[j - 1];
		if (p[i] == p[j])
			pi[i] = ++j;
	}
	return pi;
}

int kmp(string s, string p) {
	vector<int> pi = getPi(p);
	int n = s.size(), m = p.size(), j = 0, ans = 0;
	for (int i = 0; i < n; i++) {
		while (j > 0 && s[i] != p[j])
			j = pi[j - 1];
		
		if (s[i] == p[j]) {
			if (j == m - 1) {
				ans++;
				j = pi[j];
			}
			else
				j++;
		}
	}

	return ans;
}


int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;
	cin.ignore();
	for (test_case = 1; test_case <= T; ++test_case)
	{
		string s, p;
		getline(cin,s);
		getline(cin, p);
		cout << "#" << test_case << " " << kmp(s, p)<<"\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}