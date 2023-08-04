//No. 10 [S/W 문제해결 기본] 9일차 - 사칙연산

// 시간 : 10개 테스트케이스를 합쳐서 C/C++의 경우 10초 / Java의 경우 20초
// 메모리 : 힙, 정적 메모리 합쳐서 256MB 이내, 스택 메모리 1MB 이내
// ※ SW Expert 아카데미의 문제를 무단 복제하는 것을 금지합니다.

// 사칙연산으로 구성되어 있는 식은 이진 트리로 표현할 수 있다. 아래는 식 “(9/(6-4))*3”을 이진 트리로 표현한 것이다.
// 임의의 정점에 연산자가 있으면 해당 연산자의 왼쪽 서브 트리의 결과와 오른쪽 서브 트리의 결과에 해당 연산자를 적용한다.
// 사칙연산 “+, -, *, /”와 양의 정수로만 구성된 임의의 이진 트리가 주어질 때, 이를 계산한 결과를 출력하는 프로그램을 작성하라.
// 계산 중간 과정에서의 연산은 모두 실수 연산으로 한다.

// [입력]
// 총 10개의 테스트 케이스가 주어진다.
// 각 테스트 케이스의 첫 줄에는 정점의 개수 N(1≤N≤1000)이 주어진다. 그다음 N 줄에 걸쳐 각 정점의 정보가 주어진다.
// 정점이 정수면 정점 번호와 양의 정수가 주어지고, 정점이 연산자이면 정점 번호, 연산자, 해당 정점의 왼쪽 자식, 오른쪽 자식의 정점 번호가 차례대로 주어진다.
// 정점 번호는 1부터 N까지의 정수로 구분된고 루트 정점의 번호는 항상 1이다.
// 위의 예시에서, 숫자 4가 7번 정점에 해당하면 “7 4”으로 주어지고, 연산자 ‘/’가 2번 정점에 해당하면 두 자식이 각각 숫자 9인 4번 정점과 연산자 ‘-’인 5번 정점이므로 “2 / 4 5”로 주어진다.

// [출력]
// 각 테스트케이스마다 '#t'(t는 테스트케이스 번호를 의미하며 1부터 시작한다)를 출력하고 사칙연산을 계산한 결과값을 출력한다.
// 결과값은 소수점 아래는 버리고 정수로 출력한다.


#include<iostream>
#include<string.h>
#include<queue>
using namespace std;

int N;

struct Node {
    char c;
    int num;
	int left;
	int right;
};
Node node[1001];
double result;

double count(int idx)
{	
	if (node[idx].num)
	{
		return node[idx].num;
	}
	else
	{
		if (node[idx].c == '+')
		{
			return (double)count(node[idx].left) + (double)count(node[idx].right);
		}
		else if (node[idx].c == '-')
		{
			return (double)count(node[idx].left) - (double)count(node[idx].right);
		}
		else if (node[idx].c == '*')
		{
			return (double)count(node[idx].left) * (double)count(node[idx].right);
		}
		else if (node[idx].c == '/')
		{
			return (double)count(node[idx].left) / (double)count(node[idx].right);
		}
		
	}
}

int main(int argc, char** argv)
{
	int test_case;


	for (test_case = 1; test_case <= 10; ++test_case)
	{
		cin >> N;
        //0으로 node size 만큼으로 초기화
        memset(node,0,sizeof(node));
		for (int i = 0; i < N; i++)
		{
			int idx;
			cin >> idx;

            //+ - * /가 아닐경우 숫자로 들어오는데 한자리 수가 아닐수도 있기 때문에 string으로 받아야 한다.
			string c;
			cin >> c;


			if (c == "+" || c == "-" || c == "*" || c == "/")
			{
				node[idx].c = c[0];
				int left, right;
				cin >> left >> right;
				node[idx].left = left;
				node[idx].right = right;
			}
			else
			{
				int num = 0;
				int z = 1;
				for (int j = c.size() - 1; j >= 0; j--)
				{
					num += z * (c[j] - '0');
					z *= 10;
				}
				node[idx].num = num;
			}
		}
        int ans = count(1);
		
		cout << "#" << test_case << " " << count(1) << endl;



	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}