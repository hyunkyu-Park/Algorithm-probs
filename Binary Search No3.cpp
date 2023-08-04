//[SWEA] 11446번 : 사탕 가방

#include <iostream>
#include <vector>

using namespace std;
vector<long long> candies;

long long binarySearch(long long m, long long max)
{
	long long start = 1, end = max;
	long long answer = 0;

	while (end >= start)
	{
		long long mid = start + (end - start) / 2;

		// 각 사탕 개수를 현재 가방 개수로 나누면, 해당 가방 개수일 때 사용해야하는 각 사탕 개수를 알 수 있음.
		long long curCount = 0;
		for (int i = 0; i < candies.size(); i++)
			curCount += candies[i] / mid;
		
		if (curCount < m)		// 가방 개수 너무 많으면 한 가방 내 사탕 개수 못 채움 -> mid 이상 개수는 불가능. 그 아래 탐색
			end = mid - 1;
		else                   //  가방 개수 딱 맞거나 너무 적으면 한 가방 내 사탕 개수 채움 -> 현재 가방 개수를 answer로 설정하고 그 위 값도 탐색
		{
			answer = mid;
			start = mid + 1;
		}
	}
	return answer;
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
	cin.tie(); cout.tie();

	int test_case;
	int T;
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{

		long long n, m;
		cin >> n >> m;
		long long max = 0;
		for (int j = 0; j < n; j++)
		{
			long long num;
			cin >> num;
			candies.push_back(num);

			if (max < num)
				max = num;
		}

		cout << '#' <<test_case << ' ' << binarySearch(m, max) << endl;
		candies.clear();

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}