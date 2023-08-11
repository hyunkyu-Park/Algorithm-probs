#include<climits>

using namespace std;

int n;

//for minTravelTime
int graph_time[61][30100][3];
int graph_time_size[61];
int dist1[61][2];

//for minPrice;
int travel_a_to_b_price[61][61];
int price[61];

struct heap {
    int data[30001][3];
    int size = 0;

    int compare(int i, int j) {
        if (data[i][0] == data[j][0]) {
            if (data[i][1] == data[j][1]) {
                return data[i][2] < data[j][2];
            }
            return data[i][1] < data[j][1];
        }
        return data[i][0] < data[j][0];
    }

    void swap(int i, int j) {
        int tmp[3];
        tmp[0] = data[i][0];
        tmp[1] = data[i][1];
        tmp[2] = data[i][2];
        data[i][0] = data[j][0];
        data[i][1] = data[j][1];
        data[i][2] = data[j][2];
        data[j][0] = tmp[0];
        data[j][1] = tmp[1];
        data[j][2] = tmp[2];
    }

    void push(int a, int b, int c) {
        data[size][0] = a;
        data[size][1] = b;
        data[size][2] = c;
        size++;
        int tmp = size - 1;
        while (tmp > 0) {
            int parent = (tmp - 1) / 2;
            if (compare(tmp, parent)) {
                swap(tmp, parent);
                tmp = parent;
            } else {
                break;
            }
        }
    }

    void pop() {
        size--;
        data[0][0] = data[size][0];
        data[0][1] = data[size][1];
        data[0][2] = data[size][2];
        int tmp = 0;
        while (tmp * 2 + 1 < size) {
            int child = tmp * 2 + 1;
            if (child + 1 < size && compare(child + 1, child)) {
                child++;
            }
            if (compare(child, tmp)) {
                swap(child, tmp);
                tmp = child;
            } else {
                break;
            }
        }
    }

    int *top() {
        return data[0];
    }

    int empty() {
        return size == 0;
    }

    void clear() {
        size = 0;
    }
} my_pq;

void init(int N) {
    n = N;
    for (int i = 0; i < N; i++){
        graph_time_size[i] = 0;
    } 

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            travel_a_to_b_price[i][j] = INT_MAX;
        }
    }     
}

void add(int mStartAirport, int mEndAirport, int mStartTime, int mTravelTime, int mPrice) {
    int size = graph_time_size[mStartAirport];
    graph_time[mStartAirport][size][0] = mEndAirport;
    graph_time[mStartAirport][size][1] = mStartTime;
    graph_time[mStartAirport][size][2] = mTravelTime;
    graph_time_size[mStartAirport]++;

    if (travel_a_to_b_price[mStartAirport][mEndAirport] > mPrice) {
        travel_a_to_b_price[mStartAirport][mEndAirport] = mPrice;
    }
}

int minTravelTime(int mStartAirport, int mEndAirport, int mStartTime) {
    my_pq.push(0, mStartTime, mStartAirport);
    for (int i = 0; i < n; i++) {
        dist1[i][0] = INT_MAX;
        dist1[i][1] = INT_MAX;
    }
    dist1[mStartAirport][0] = 0;
    dist1[mStartAirport][1] = mStartTime;
    while (!my_pq.empty()) {
        int tmp[3] = {my_pq.top()[0], my_pq.top()[1], my_pq.top()[2]};
        my_pq.pop();
        if (tmp[0] != dist1[tmp[2]][0] || tmp[1] != dist1[tmp[2]][1]) {
            continue;
        }
        if (tmp[2] == mEndAirport) {
            my_pq.clear();
            return tmp[0] * 24 + tmp[1] - mStartTime;
        }
        for (int i = 0; i < graph_time_size[tmp[2]]; i++) {
            auto next = graph_time[tmp[2]][i];
            int nextDate = tmp[0];
            if (tmp[1] > next[1]) {
                nextDate++;
            }

            int nextTime = next[1] + next[2];
            if (nextTime >= 24) {
                nextTime -= 24;
                nextDate++;
            }

            if (nextDate < dist1[next[0]][0] || (nextDate == dist1[next[0]][0] && nextTime < dist1[next[0]][1])) {
                dist1[next[0]][0] = nextDate;
                dist1[next[0]][1] = nextTime;
                my_pq.push(nextDate, nextTime, next[0]);
            }
        }
    }
    return -1;
}

int minPrice(int mStartAirport, int mEndAirport) {
    
    my_pq.push(0, mStartAirport, 0);
    for (int i = 0; i < n; i++) {
        price[i] = INT_MAX;
    }
    price[mStartAirport] = 0;

    while (!my_pq.empty()) {
        int tmp[2] = {my_pq.top()[0], my_pq.top()[1]}; //tmp[0]: price, tmp[1]: airport
        my_pq.pop();
        if (tmp[0] != price[tmp[1]]) {
            continue;
        }
        if (tmp[1] == mEndAirport) {
            my_pq.clear();
            return tmp[0];
        }
        for (int i = 0; i < n; i++) {
            if (travel_a_to_b_price[tmp[1]][i] == INT_MAX) {
                continue;
            }
            if (tmp[0] + travel_a_to_b_price[tmp[1]][i] < price[i]) {
                price[i] = tmp[0] + travel_a_to_b_price[tmp[1]][i];
                my_pq.push(tmp[0] + travel_a_to_b_price[tmp[1]][i], i, 0);
            }
        }
    }

    return -1;
}