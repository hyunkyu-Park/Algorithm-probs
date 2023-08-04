//염라대왕의 이름정렬

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
int T, N,i,len;
vector<string> names;
string input;

bool my_compare(string s1,string s2)
{
	if (s1.length() == s2.length())
	{
		return s1 < s2;
	}
	else
	{
		return s1.length() < s2.length();
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	cin >> T;
	for (int testcase = 1; testcase <= T; ++testcase)
	{
		int N;
		names.clear();
		cin >> N;
		for (i = 0; i < N; ++i)
		{
			cin >> input;
			names.push_back(input);
		}
		sort(names.begin(), names.end(), my_compare);
		names.erase(unique(names.begin(), names.end()), names.end());
		cout << "#" << testcase<<"\n";
		for (i = 0; i < names.size(); ++i)
		{
			cout << names[i] << "\n";
		}
	}
}