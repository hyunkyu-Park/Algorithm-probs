//[Professional] 고속도로 건설 2 위에는 내 풀이 밑에 주석은 더 빠른 풀이(min PQ 안쓰고 vector써서 sort해서 앞에서부터 썼음)

#include<iostream>
#include<queue>
#include<vector>


using namespace std;

int connection[50001];


struct path{
    int from;
    int to;
    int cost;

    bool operator<(const path &other) const{
        return cost >other.cost;
    }
};



// //find와 path compression 하는 함수 281 노트497 참고 
// int find(int index){
//     int pathStart = index;
//     //find the uptimate rep
//     while(connection[index] != index){
//         index = connection[index];
//     }

//     //x가 이제 최종 rep과 같아짐
//     //path compression
//     while(connection[pathStart] != index){
//         int tmp = connection[pathStart];
//         connection[pathStart] = tmp;
//         pathStart = tmp;
//     }
//     return index;
// }

//위에 find보다 얘가 빠름
int find(int x) {
    if (connection[x] == x) return x;
    return connection[x] = find(connection[x]);
}

void set_union(int x, int y){
    connection[find(y)] = find(x);
}


int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N, M, from, to, cost;
        cin >> N >>M; 

        int edges=0;

        for(int i=1; i<=N; ++i){
            connection[i] = i;
        }
        priority_queue<path> paths; //min PQ;
        for(int i=0; i<M; ++i){
            cin >> from >> to >> cost;
            paths.push({from, to, cost});
        }

        int ans = 0;
        while(edges != N-1){ //N개의 점을 연결하려면 N-1개의 선이 필요하다
            int x = paths.top().from;
            int y = paths.top().to;
            if(find(x) != find(y)){ //만약 두 점이 연결되있지 않다면, 즉 사이클이 없다면
                ans+=paths.top().cost; //cost를 더하고
                set_union(x, y); //두 점을 연결
                edges++; //하나의 edge 추가
            }
            paths.pop(); //min cost를 갖는 path 빼기
        }
        
        printf("#%d %d\n", test_case, ans);
        


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
























// #include <iostream>
// #include <vector>
// #include <algorithm>

// using namespace std;

// struct Road {
//     int start;
//     int end;
//     int cost;

//     bool operator<(const Road& other) const {
//         return cost < other.cost;
//     }
// };

// const int MAXN = 50001;
// int parent[MAXN];

// int find(int x) {
//     if (parent[x] == x) return x;
//     return parent[x] = find(parent[x]);
// }

// void set_union(int x, int y) {
//     parent[find(y)] = find(x);
// }

// int main() {
//     int T;
//     cin >> T;

//     for (int tc = 1; tc <= T; ++tc) {
//         int N, M;
//         cin >> N >> M;

//         vector<Road> roads;
//         for (int i = 0; i < M; ++i) {
//             int s, e, c;
//             cin >> s >> e >> c;
//             roads.push_back({s, e, c});
//         }

//         sort(roads.begin(), roads.end());

//         for (int i = 1; i <= N; ++i) {
//             parent[i] = i;
//         }

//         int minCost = 0;
//         int edgeCount = 0;

//         for (int i = 0; i < M; ++i) {
//             int start = roads[i].start;
//             int end = roads[i].end;
//             int cost = roads[i].cost;

//             if (find(start) != find(end)) {
//                 set_union(start, end);
//                 minCost += cost;
//                 edgeCount++;

//                 if (edgeCount == N - 1) break; // 모든 도시를 잇는 간선을 선택하면 종료
//             }
//         }

//         cout << "#" << tc << " " << minCost << endl;
//     }

//     return 0;
// }
