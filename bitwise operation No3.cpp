//https://g-idler.tistory.com/96
// SWEA_3316_동아리실_관리하기
using namespace std;
#include <iostream>
#include <string>
#include <cstring>
#define MAX 10000

long long dp[MAX][16]; // A, B, C, D 경우의 수 2^4 - 1 = 15

int main()
{
	int T;
	cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		string club;
		cin >> club;
		
        memset(dp, 0, sizeof(dp));
		long long case_cnt = 0;
		
		for (int day = 0; day < club.size(); day++) {
			int admin = 1 << (club[day] - 'A');
			
			for (int i = 1; i < 16; i++) {
				if (day == 0) { // 1일차
					// i번째 경우에 관리자와 A가 포함되면
					if ((i & admin) != 0 && (i & 1) != 0) {
						dp[day][i] = 1;
					}
				}
				else { // 2일차 ~
					// 전날까지의 경우의 수가 0이 아니면
					if (dp[day - 1][i] != 0) {
						for (int j = 1; j < 16; j++) {
							// 전날 나온 사람이 오늘도 나오고 (i & j != 0)
							// 오늘 나온 사람이 관리자인 경우 count (j & admin != 0)
							if ((i & j) != 0 && (j & admin) != 0) {
								dp[day][j] += dp[day - 1][i];
								dp[day][j] %= 1000000007;
							}
						}
					}
				}
			}
		}
		for (int i = 1; i < 16; i++) {
			case_cnt += dp[club.size() - 1][i];
			case_cnt %= 1000000007;
		}
		printf("#%d %llu\n", tc, case_cnt);
	}
}