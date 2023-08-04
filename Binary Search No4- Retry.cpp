
//9999 광고시간 정하기

//1. low가 high보다 작거나 같은동안 돈다
//2. 1과 L사이의 mid 값을 정한다.
//3. 해당 mid 값을 쓸 수 있는지 본다.
//4. 쓸 수 있으면 ans를 mid로 두고 low를 mid+1로 둔다.
//5. 아니라면 highfmf mid-1로 둔다.



///is_valid
//시작점 0부터 마지막점 0까지 돈다고 가정
//만약 지금까지의 누적 Peak time에다가  + e[last] - s[last] >= val 라면 해당 값을 사용 할 수 있다
    //만약 총 시간 + (val-피크타임), 즉 남은 val <= L(최대치) 라면 last에서 종료가능, 즉 return true;
    //아니라면 지금 시작점에서 출발했을 경우엔 성립 x
        //시작점 하나 밀어줘야함


//아니라면 
    //광고를 끝까지 밀었는데 피크 시간과 val분 이상 겹치지 않는다면false 리턴

    //누적 피크 타임 업데이트
    //이번 피크에서 다음 피크로 가는 총 시간 업데이트
    //마지막점 다음으로 밀어주기




#include<iostream>
#include<vector>

using namespace std;

int L, N;
int s[100000];
int e[100000];

bool is_valid(int val){
    int first = 0, last =0, total_time=0, peak_time =0;
    while(true){
        if(peak_time + (e[last] - s[last]) >= val){
            if(total_time + (val - peak_time) <= L){
                return true;
            }
            else{
                peak_time -= (e[first] - s[first]);
                total_time -= (s[first+1] - s[first]);
                first++;
            }
        }
        else{
            if(last == N-1){
                return false;
            }

            else{
                peak_time += e[last] -s[last];
                total_time += s[last+1] - s[last];
                last++;
            }
        }
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);
	int test_case;
	int T;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> L;
        cin >> N;

        for(int i=0; i<N; ++i){
            cin >> s[i] >>e[i];
        }

        int ans, low = 1, high = L;
        
        while(low <= high){
            int mid = low + (high-low)/2;

            if(is_valid(mid)){
                ans = mid;
                low = mid+1;
            }
            else{
                high = mid-1;
            }
        }

        cout << '#' << test_case << ' ' << ans << '\n';

        


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}