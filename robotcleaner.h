extern void scanFromRobot(int ceilingState[3][3]);
extern int moveRobot(int mCommand);
 
int tc;
int N;
 
//up(0), left(1), down(2), right(3)
int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,-1,0,1 };
int visited[60][60];
int currDir; 
 
void dfs(int y, int x) {
    visited[y][x] = tc;
 
    int ret[3][3];
    scanFromRobot(ret);
 
    int initDir = currDir;
    for (int i = 0; i < 4; i++) {
        int nextDir = (i + initDir) % 4;
        int Y = y + dy[nextDir];
        int X = x + dx[nextDir];
        if (visited[Y][X] == tc)continue;
        if (ret[1 + dy[i]][1 + dx[i]] == 1)continue;
         
        moveRobot((nextDir-currDir+4)%4);
        currDir = nextDir;
        dfs(Y, X);
 
        //reverse
        moveRobot((nextDir - currDir + 6) % 4);
        currDir = (nextDir + 2) % 4;
    }
}
 
void init(int N, int subTaskCount)
{
    ::N = N;
}
 
void cleanHouse(int mLimitMoveCount)
{
    tc++;
    currDir = 0;
    dfs(N, N);
}