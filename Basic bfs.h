//12318. 기초 BFS 연습


struct location{
    int x;
    int y;
};

int arr[10][10] ={0};

const int NESW[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};


void bfs_init(int map_size, int map[10][10]) {
    for(int i=0; i<10; ++i){
        for(int j=0; j<10; ++j){
            arr[i][j] = map[i][j];
        }
    }
}
int bfs(int x1, int y1, int x2, int y2) {
    x1 -=1;
    x2 -=1;
    y1 -=1;
    y2 -=1;


    int dist[10][10] = {0};
    location queue[100];
    int front = -1;
    int rear = -1;

    dist[y1][x1] = 1;
    queue[++rear] = {y1, x1};
    while(front != rear){
        location cur = queue[++front];

        for(int i=0; i<4; ++i){
            int new_x = cur.x + NESW[i][0];
            int new_y = cur.y + NESW[i][1];
            if(new_x >=0 && new_x <10 && new_y>=0 && new_y <10 && dist[new_x][new_y]==0
                        &&arr[new_x][new_y] != 1){
                
                dist[new_x][new_y] = dist[cur.x][cur.y] + 1;
                queue[++rear] = {new_x, new_y};
                
                if (new_x == y2 && new_y == x2) {
                    return dist[new_x][new_y]-1; // 도착점에 도달한 경우 최단 거리 반환
                }
            }
        }
    }
    return -1;

}