//1868. 파핑파핑 지뢰찾기


#include<iostream>
#include<cstring>
#include<deque>

using namespace std;

int N, mines, clicks;
int map[301][301]; //맵 저장
bool visited[301][301]; //방문 표시용
//시계방향 12 1 3 5 6 7 9 11
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

bool is_valid(int x, int y){
    if(x>=0 && y>=0 && x<N && y<N){
        return true;
    }
    return false;
}

//주변 8칸에 지뢰가 있는지 확인
bool is_mine(int x, int y){
    for(int i=0; i<8; ++i){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(is_valid(nx, ny)){
            if(map[nx][ny] == -1){
                return true;
            }
        }
    }
    return false;
}

void play(){
    deque<pair<int, int>> queue;
    for(int i=0; i<N; ++i){ //행 체크
        for(int j=0; j<N; ++j){ //열 체크
            if(!visited[i][j] && map[i][j] != -1 && !is_mine(i, j)){ //방문한적 없고, 지뢰가 아니고, 주변 8칸에 지뢰가 없는 좌표 즉, 0
                clicks++;
                queue.push_back({i, j});

                while(!queue.empty()){
                    int x = queue.front().first;
                    int y = queue.front().second;
                    visited[x][y] = 1;
                    queue.pop_front();

                    for(int k=0; k<8; k++){
                        int nx = x+dx[k];
                        int ny = y+dy[k];

                        //우리가 0이되는 좌표를 찾아서 큐를 돌리는데, 근처 8방향 좌표중에 또다른 0이 있다면 큐에 추가해버린다
                        //그래서 클릭수를 중복해서 늘리지 않음
                        if(is_valid(nx, ny) && !visited[nx][ny] && map[nx][ny]==0){
                            visited[nx][ny] = 1; //0주변 좌표중에 범위 안에 있고, 방문한적 없고, 지뢰가 아닌 좌표 방문표시
                            if(!is_mine(nx, ny)){ // 주위에 8칸에 지뢰가 없는 곳, 즉 또 다른 0
                                queue.push_back({nx, ny});
                            }
                        }
                    }
                }
            }
        }
    }
}


int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{
        
        clicks = 0; //총 지뢰 개수 초기화
        memset(map, 0, sizeof(map)); //맵 초기화
        memset(visited, false, sizeof(visited)); //0값들의 좌표를 저장하는 check 초기화
        char temp;
        cin >> N;
        for(int i=0; i<N; ++i){
            for(int j=0; j<N; ++j){
                cin >>temp; //만약 입력 값이 지뢰라면
                if(temp =='*'){
                    map[i][j] = -1; // -1로 저장
                    mines++;
                    visited[i][j] = true;
                }
            }
        }
        play();
        for(int i=0; i<N; ++i){
            for(int j=0; j<N; ++j){
                if(map[i][j] != -1 && !visited[i][j]){ //지뢰도 아니고 방문한적도 없다면
                    clicks++;
                }
            }
        }
        
       

        printf("#%d %d\n", test_case, clicks);
        



	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}