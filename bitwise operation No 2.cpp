// No. 2 이진수 표현

// 시간 : 10000개 테스트케이스를 합쳐서 C/C++의 경우 1초 / Java의 경우 2초
// 메모리 : 힙, 정적 메모리 합쳐서 256MB 이내, 스택 메모리 1MB 이내

 
// 정수 N, M 이 주어질 때, M의 이진수 표현의 마지막 N 비트가 모두 1로 켜져 있는지 아닌지를 판별하여 출력하라. 

// [입력]

// 첫 번째 줄에 테스트 케이스의 수 TC가 주어진다.
// 이후 TC개의 테스트 케이스가 새 줄로 구분되어 주어진다.
// 각 테스트 케이스는 다음과 같이 구성되었다.
// 첫 번째 줄에 정수 N, M이 주어진다. (1 ≤ N ≤ 30 , 0 ≤ M ≤ 108)

// [출력]
// 각 테스트 케이스마다 한 줄씩
// 마지막 N개의 비트가 모두 켜져 있다면 ON
// 아니면 OFF 를 출력하라.

// 입력
// 5
// 4 0
// 4 30
// 4 47
// 5 31
// 5 62

// 출력
// #1 OFF
// #2 OFF
// #3 ON
// #4 ON
// #5 OFF

#include<iostream>

using namespace std;

bool checking(int N, int M){
        int mask =  (1<< N) - 1;
        int check_bits = mask & M;
        return mask == check_bits;
}

int main()
{
	int test_case;
	int T;
	cin>>T; 
        
        

	for(test_case = 1; test_case <= T; ++test_case)
	{
                int N, M;
                cin >> N >> M;
                if(checking(N, M)){
                        cout << "#" << test_case << " ON\n";  
                }         
                else{
                        cout << "#" << test_case << " OFF\n";  
                }  


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}