//[S/W 문제해결 기본] 9일차 - 중위순회

#include<iostream>
#include<vector>

using namespace std;

struct Node{
	char c;
	size_t left = 0;
	size_t right =0;
};

void inorder_tra(size_t idx, vector<Node> &vec){
	if(vec[idx].left != 0){
		inorder_tra(vec[idx].left, vec);
	}
	cout << vec[idx].c;
	if(vec[idx].right != 0){
		inorder_tra(vec[idx].right, vec);
	}
}

int main()
{
	int test_case;

	for(test_case = 1; test_case <= 10; ++test_case)
	{
		size_t N, num, left, right;
		char input;
		cin >> N;
		vector<Node> my_vec(N+1);
		for(size_t i=1; i<=N; ++i){
			cin >> num;
			cin >> input;
			if(num*2<N){
				cin >> left >> right;
				my_vec[i].left = left;
				my_vec[i].right = right;
			}
			else if(num*2<=N){
				cin >> left;
				my_vec[i].left = left;
			}
			my_vec[i].c = input;
		}
		printf("#%d ", test_case);
		inorder_tra(1, my_vec);
		cout << "\n";
		

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
