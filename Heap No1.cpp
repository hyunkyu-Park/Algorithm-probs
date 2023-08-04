//2930. 힙

#include <queue>
#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int test_case;
	int T;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		priority_queue<int> max_pq;
		int N;
		cin >> N;
		
		cout <<"#" << test_case;
		for(int i=0; i<N; ++i){
			int order;
			cin >>order;
			switch (order){
			case 1:
				int num;
				cin >>num;
				max_pq.push(num);
				break;

			case 2:
				if(!max_pq.empty()){
					cout <<" " << max_pq.top();
					max_pq.pop();
				}
				else{
					cout <<" -1";
				}
				break;
			}
		}
		cout <<"\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}