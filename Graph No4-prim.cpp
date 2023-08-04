//[S/W 문제해결 응용] 4일차 - 하나로
#include<iostream>
#include<vector>
#include<cmath>
#include<cstring>
#include<limits>

using namespace std;


struct prim{
    bool visited; //방문 여부 확인
    long long dist = numeric_limits<long long>::max(); //최단거리 저장용
    int prev_coor = -1; //몇번째 좌표와 연결되어 있는지 표시
};

struct coor{
    int x;
    int y;
};


int N;
long long total;

long long naive_distance(coor c1, coor c2){
    return pow(c2.x - c1.x, 2) + pow(c2.y - c1.y, 2);
}

void mst(vector<prim> prims, vector<coor> coords){
    prims[0].visited = true;
    prims[0].dist = 0;
    int index = 0;
    
    for(int i=0; i<N; ++i){
        long long shortest_dist = numeric_limits<long long>::max();
        //방문 안한 노드중에 가장 작은 dist값을 갖고 있는 인덱스 찾기
        for(int j=0; j < N; ++j){
                if(!prims[j].visited){
                    if(prims[j].dist < shortest_dist){
                        index = j;
                        shortest_dist = prims[j].dist;
                    }
                }
        }// for loop j

        
        prims[index].visited = true; //해당 인덱스 방문으로 표시(이제 얘가 기준점이 됨)
        total += prims[index].dist; //해당 인덱스는 방문했으므로 총 거리에 추가

        //방문 안한 점들과 기준점 사이의 거리 계산후 더 짧다면 갱신
        for(int j=0; j<N; ++j){
            if(prims[j].visited == false){
                long long temp_dist = naive_distance(coords[index], coords[j]);
                if (temp_dist<prims[j].dist){ //만약 기존 거리보다 새 거리가 짧다면
                    prims[j].dist = temp_dist; //거리 갱신
                    prims[j].prev_coor = index; //어디서 왔는지, prev 정보 갱신
                }
            }
        }

    }
}



int main()
{
	int test_case;
	int T;
	
	cin>>T;
	
    vector<prim> prims;
    vector<coor> coords;

	for(test_case = 1; test_case <= T; ++test_case)
	{
        
        
        total = 0;

        int input;
        cin >> N;
        int check1 = N;
        
        prims.clear();
        coords.clear();
        prims.resize(N+1);
        coords.resize(N+1);

        //coords에 각 좌표 저장
        for(int i=0; i<N; ++i){
            cin >>input;
            coords[i].x = input;
        }
        for(int i=0; i<N; ++i){
            cin >>input;
            coords[i].y = input;
        }
        mst(prims, coords);


        double E;
        cin >>E;
        
        long long ans = round(total * E);
        // cout << "total:" <<total <<"\n";
        // cout << "E: " <<  E << "\n";
        // cout << "answer: " <<  ans << "\n";
        
        cout << "#" << test_case << " " << ans << "\n";


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}