// No. 5 수열 편집


#include<iostream>
#include<list>

using namespace std;

int main()
{
	int test_case;
	int T;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		list<int> li;
		int N, M, L, num, x, y;
		char c;
		//수열의 길이 N, 추가 횟수 M, 출력할 인덱스 번호 L
		cin >> N >> M >> L;
		auto iter = li.begin();

		for(int i=0; i<N; ++i){
			cin >> num;
			li.push_back(num);
		}
		for(int i=0; i<M; ++i){
			cin >> c;
			if(c=='I'){
				iter = li.begin();
				cin >> x >> y;
				for(int j=0; j<x; ++j){
					iter++;
				}
				li.insert(iter, y);
			}
			else if(c=='D'){
				iter = li.begin();
				cin >> x;
				for(int j=0; j<x; ++j){
					iter++;
				}
				li.erase(iter); 

			}
			else if(c=='C'){
				iter = li.begin();
				cin >>x >> y;
				for(int j=0; j<x; ++j){
					iter++;
				}
				*iter = y;
			}
		}
		iter = li.begin();
		if(L > li.size()){
			*iter = -1;
		}
		else{
			for(int i=0; i<L; ++i){
				iter++;
			}
		}
		

		printf("#%d ", test_case);
		printf("%d \n", *iter);

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}