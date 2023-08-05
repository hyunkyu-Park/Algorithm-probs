//공부를 한 날이 3 5 6 10 11이면
//check 는   0 0 0 1 0 1 1 0 0 0 1 1이 되고
//no_study는 0 1 2 2 3 3 3 4 5 6 6 6이 된다.

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main()
{

	int test_case;
	int T;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N, P, input;
        cin >> N >>P;

        vector<bool> study_days(1e6+1);
        vector<int> no_study;

        for(int i=0; i<N; ++i){
            cin >>input;
            study_days[input] = true; //공부한 날만 true표시
        }//for loop이 끝나면 공부를 한 마지막 날짜가 input에 들어있음

        study_days.resize(input+1); //마지막 공부일 이후로는 필요 없기 때문에 사이즈 조절
        no_study.resize(input+1);

        int sum = 0;
        for(int i=1; i<input+1; ++i){
            if(!study_days[i]){
                sum +=1;
            }
            no_study[i] = sum; //공부를 안한 누적일 표시
        }

        int max_days =0;
        for(int i=0; i<=input; ++i){
            if(study_days[i]){ //만약 해당일에 공부를 했다면
                //해당일 기준 공부를 안한 누적일+p일 만큼의 upper_bound 찾기.
                // 예를들어 2일차 기준 누적으로 공부를 하지 않은 날은 1일. 1일+해킹2일, 즉 누적 공부 안한날이 3일 되는 날 찾기
                auto upper = upper_bound(no_study.begin(), no_study.end(), no_study[i]+P);

                int upper_index = upper - no_study.begin(); //upper이 가르키는 인덱스 찾기

                if(no_study[upper_index-1]-no_study[i]<P){ //upper_idx-1의 누적 공부 안한날과 기준일의 누적 공부 안한날의 차이가 P 미만이라면,
                                                           // 그 차이만큼 더 해킹할 수 있기 때문에 Max값 수정할 때 남은 일수를 더해서 비교해준다.
                    int left_p = P - (no_study[upper_index-1]-no_study[i]);
                    max_days = max(max_days, upper_index - i +left_p);
                    
                }
                else{
                    max_days = max(max_days, upper_index - i); //P번 해킹하고 나서 누적 공부 안한날이 3일일인 인덱스 - 해당일(기준일)
                }
            }
        }
        
        cout << "#" <<test_case <<" "  <<max_days << "\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

