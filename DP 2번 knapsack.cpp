//참고
//https://gsmesie692.tistory.com/113

//3282. 0/1 Knapsack

#include<iostream>

using namespace std;

int arr[101][1001];
size_t sizes[101];
size_t vals[1001];

int main()
{
	int test_case;
	int T;
	
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{
        size_t N, M;
        cin >> N >> M;
        int v[101][1001];
        int w[101];
        int c[101];

        for(int i = 1; i <= N; i++)
            cin >> sizes[i] >> vals[i];
        
        for(int i = 1; i <= N; i++)
        {
            for(int j = 1; j <= M; j++)
            {
                if(sizes[i] > j)
                    arr[i][j] = arr[i - 1][j];
                else
                    arr[i][j] = vals[i] + arr[i - 1][j - sizes[i]] > arr[i - 1][j] ? vals[i] + arr[i - 1][j - sizes[i]] : arr[i - 1][j];
            }
        }
 
    
        cout << "#" << test_case << " " << arr[N][M] << "\n";
		
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}