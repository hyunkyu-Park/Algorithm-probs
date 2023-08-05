//No. 41 3차원 농부
//이분탐색으로 풀려고 했으나 26개 위로 계속 오답나서 수정

//test case
//1 - test case
// 5 5  - N M
// 3 8  - c1 c2
// 1 2 3 7 9 
// 4 6 8 10 11

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int testCase = 1; testCase <= T; ++testCase) {
        int N, M;
        cin >> N >> M;
        
        int c1, c2;
        cin >> c1 >> c2;
        
        int x_gap = abs(c1-c2);
        vector<int> cows(N);
        vector<int> horses(M);
        
        for (int i = 0; i < N; ++i) {
            cin >> cows[i];
        }
        
        for (int i = 0; i < M; ++i) {
            cin >> horses[i];
        }
        
        sort(cows.begin(), cows.end());
        sort(horses.begin(), horses.end());
        
        long long minDistance = 1e9; // 초기값으로 충분히 큰 수 설정
        int count = 0;
        
        for (int i = 0, j = 0; i < N; ++i) { //cow의 작은 값부터 확인한다. 
            while (j < M && horses[j] <= cows[i]) {//j는 horse의 인덱스를 의미. 우리가 보고 있는 cow보다 horse가 작다면 해당 horse 거리 계산하고 다음 말로 넘어간다.
                //왜나하면 한 말에대해서 자기보다 z가 작은 소 중에 제일 큰값과 자기보다 z가 큰 소중에 제일 작은 소만 확인하면 되기 때문
                //이해가 안된다면 위의 테케 확인
                long long distance = abs(cows[i] - horses[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    count = 1;
                } else if (distance == minDistance) {
                    count++;
                }
                j++;
            }
            
            if (j < M) {
                long long distance = abs(cows[i] - horses[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    count = 1;
                } else if (distance == minDistance) {
                    count++;
                }
            }
        }

        minDistance += x_gap;
        
        cout << "#" << testCase << " " << minDistance << " " << count << "\n";
    }
    
    return 0;
}
