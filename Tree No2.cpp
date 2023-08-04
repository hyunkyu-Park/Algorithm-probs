//1233. [S/W 문제해결 기본] 9일차 - 사칙연산 유효성 검사

#include<iostream>
#include <string>

using namespace std;

struct Node{
	char c;
	size_t left;
	size_t right;
};

int main(int argc, char** argv)
{
	int test_case;


	for(test_case = 1; test_case <= 10; ++test_case)
	{
		int N, idx;
		size_t left, right;
		char input;
		int answer = 1;
		cin >> N;
		for (size_t i = 0; i < N; i++)
		{
			cin >> idx >> input;
			if(idx*2 < N){
				cin >> left >> right;
			}
			else if(idx*2==N){
				cin >> left;
			}
			else{
				if(input =='+' | input == '-' | input =='*' | input =='/'){
					answer = 0;
				}
			}

		}
		printf("#%d %d\n", test_case, answer);
		

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}