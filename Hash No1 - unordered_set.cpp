
#include<iostream>
#include <unordered_set>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin>>T;


	for(test_case = 1; test_case <= T; ++test_case)
	{
		unordered_set<string> set1;
		int N, M, count=0;
		cin >>N >>M;
		string input;

		for(int i=0; i<N; ++i){
			cin >>input;
			set1.insert(input);
		}

		for(int i=0; i<M; ++i){
			cin >>input;
			auto iter = set1.find(input);

			if (iter != set1.end()) {
        		count++;
			}
		}

		printf("#%d %d\n", test_case, count);

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}