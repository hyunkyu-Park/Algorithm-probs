
#include<iostream>
#include<deque>
#include<cstring>

using namespace std;



struct location{
    int x;
    int y;
};

struct Map{
    int cost;
    bool visited;
};

Map map[101][101];
int cum_cost[101][101];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

int main()
{
	int test_case;
	int T;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N;
        cin >>N;

        memset(cum_cost, 0, sizeof(cum_cost));
        for (int i = 0; i < 101; i++) {
            for (int j = 0; j < 101; j++) {
                map[i][j].cost = 0; // cost를 0으로 초기화
                map[i][j].visited = false; // visited를 false로 초기화
        }
    }
        
        
        string input;

        for(int i=0; i<N; i++){ //맵 정보 입력 받고 cum_cost 값 초기화
            cin >>input;
            for(int j=0; j<N; ++j){
                map[i][j].cost = input[j]-'0';
                cum_cost[i][j] =0;
            }
        }

        deque<location> coords;
        coords.push_back({0,0});
        map[0][0].visited = true;

        while (!coords.empty()){
            auto tmp = coords.front();
            coords.pop_front();

            for(int i=0; i<4; ++i){
                // int check =dx[i];
                // int chec1= dy[i];
                // cout <<chec1 << check;
                int new_x = tmp.x + dx[i];
                int new_y = tmp.y + dy[i];

                if(new_x>=0 && new_x<N && new_y >=0 && new_y<N){ //if new x,y are valid(in range)
                    if(!map[new_x][new_y].visited || cum_cost[tmp.x][tmp.y] +map[new_x][new_y].cost<cum_cost[new_x][new_y]){
                        cum_cost[new_x][new_y] = cum_cost[tmp.x][tmp.y] + map[new_x][new_y].cost;
                        map[new_x][new_y].visited =true;
                        coords.push_back({new_x, new_y});
                    }
                    
                }
            }
        }

        printf("#%d %d\n", test_case, cum_cost[N-1][N-1]);
        


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}