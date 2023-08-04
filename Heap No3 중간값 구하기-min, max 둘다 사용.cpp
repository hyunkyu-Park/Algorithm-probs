#include<iostream>
#include <queue>
using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;

	//freopen("input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int ans=0,N,mid;
		priority_queue<int, vector<int>, greater<int>> min_pq;
		priority_queue<int> max_pq;
		cin >> N >> mid;
		while (N--) {
			int a, b;
			cin >> a >> b;
			mid > a ? max_pq.push(a) : min_pq.push(a);
			mid > b ? max_pq.push(b) : min_pq.push(b);
			while (max_pq.size() > min_pq.size()) {
				min_pq.push(mid);
				mid = max_pq.top();
				max_pq.pop();
			}
			while (max_pq.size() < min_pq.size()) {
				max_pq.push(mid);
				mid = min_pq.top();
				min_pq.pop();
			}
			ans += mid ;
			ans = ans%20171109;
		}

		cout <<"#"<<test_case<< " "<< ans<< "\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}