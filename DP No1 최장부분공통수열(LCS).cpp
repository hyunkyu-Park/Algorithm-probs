
// 참고 사이트
// https://velog.io/@emplam27/%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-%EA%B7%B8%EB%A6%BC%EC%9C%BC%EB%A1%9C-%EC%95%8C%EC%95%84%EB%B3%B4%EB%8A%94-LCS-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98-Longest-Common-Substring%EC%99%80-Longest-Common-Subsequence

//최장 공통 부분 수열 dp

#include<iostream>

using namespace std;

int arr[1001][1001];

int main()
{
	int test_case;
	int T;
	
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        string s1, s2;
        cin >> s1 >> s2;

        for(size_t i=0; i<=s1.length(); ++i){
            for(size_t j=0; j<=s2.length(); ++j){
                if(i==0 ||j==0){
                    arr[i][j] =0;
                }
                else if(s1[i-1] == s2[j-1]){ //만약 두 문자가 같다면 좌측 대각선 위에 정보+1
                    arr[i][j] = arr[i-1][j-1] +1;
                }
                else{//만약 두 문자가 다르다면 위랑 왼쪽 비교해서 가장 큰 수 저장
                    arr[i][j] = max(arr[i-1][j], arr[i][j-1]);
                }
            }
        } 
        int max_num =arr[s1.length()][s2.length()]; //가장 마지막에 들어가는 수가 max

        printf("#%d %d\n", test_case, max_num);
		

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}