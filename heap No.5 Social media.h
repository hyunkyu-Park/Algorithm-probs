#include <queue>
#include <map>
#include<vector>
#include<cstring>

using namespace std;

struct Info{
    int pID;
    int timestamp;
    int like;
    int uID;

    bool operator<(const Info& other) const {
        if (like != other.like) {
            return like < other.like; // like가 큰 순서대로 정렬
        }
        return timestamp < other.timestamp; // like가 같으면 timestamp가 큰 순서대로 정렬
    }
    
};



Info post[100001]; //pID별로
bool connected[1001][1001]; //각 Id별 follow하는 Id 저장
priority_queue<Info> max_pq; //time차이가 1000미만으로 나면 여기 저장
queue<int> time_max_queue; //time차이가 1000초과라면 여기 저장
int num_post;
int user_num;


void init(int N)
{
    num_post=0;
    user_num =N;
    memset(connected, 0, sizeof(connected));
    for(int i=1; i<=N; ++i){
        connected[i][i] =1;
    }

}

void follow(int uID1, int uID2, int timestamp)
{
    connected[uID1][uID2] = 1;
}

void makePost(int uID, int pID, int timestamp)
{
    post[pID] = {pID, timestamp, 0, uID};
    num_post++;
}

void like(int pID, int timestamp)
{
    post[pID].like++;
}

void getFeed(int uID, int timestamp, int pIDList[]){

    max_pq = priority_queue<Info>();
    time_max_queue = queue<int>();
    bool time_gap = false; //시간 차이가 1000초과로 나는가?
    int total=0; //누적으로 저장한 값이 총 몇개인가

    for(int i=num_post; i>0; --i){
        if(time_gap ==true && total>9){ //time차이가 1000이상 나기 시작했는데(더 이상max_pq에 들어갈 값이 없음) 값을 10개 이상 뽑았다면
            break;
        }

        if(time_gap == false){ //지금 보는 곳이 1000초 차이 미만
            if(connected[uID][post[i].uID]){//uID가 게시글의 아이디를 팔로우 하고 있다면
                if(timestamp - post[i].timestamp >1000){    //time차이가 1000 초과라면 time max pq에 저장
                    time_max_queue.push(post[i].pID);
                    time_gap = true;
                    total++;
                }
                else{
                    max_pq.push(post[i]);
                    total++;
                }
            }
        }

        else{//지금 보는곳이 1000초 차이 이상
            if(connected[uID][post[i].uID]){//uID가 게시글의 아이디를 팔로우 하고 있다면
                time_max_queue.push(post[i].pID);
                total++;
            }
        }
    }

    int num=0; //지금까지 pIDList에 집어넣은 개수, 인덱스 역할

    while(num<10 && !max_pq.empty()){ //max_pq가 비거나 pIDList를 다 채울때까지
        pIDList[num++] = max_pq.top().pID;
        max_pq.pop();
    }

    while(num<10 && !time_max_queue.empty()){// pIDList를 다 채울때까지
        pIDList[num++] = time_max_queue.front();
        time_max_queue.pop();
    }
}

