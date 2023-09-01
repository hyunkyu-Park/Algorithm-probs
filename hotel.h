#include <vector>
#include <algorithm>
#define MAX_N 5001
#define MAX_P 51
#define INF 999999999
#define HEAP_SIZE 10001

using namespace std;

struct Priority_Queue {
    short heap_size;
    pair<int, int> heap[HEAP_SIZE];

    void clear() {
        heap_size = 0;
    }
    void push(pair<int, int> x) {
        heap[heap_size] = x;
        int current = heap_size++;
        while (current > 0 && heap[(current - 1) / 2] > heap[current]) {
            pair<int, int> tmp = heap[(current - 1) / 2];
            heap[(current - 1) / 2] = heap[current];
            heap[current] = tmp;
            current = (current - 1) / 2;
        }
    }
    void pop() {
        heap[0] = heap[--heap_size];
        int current = 0;
        while (current * 2 + 1 < heap_size) {
            int child;
            if (current * 2 + 2 == heap_size) {
                child = current * 2 + 1;
            } else {
                child = heap[current * 2 + 2] > heap[current * 2 + 1] ? current * 2 + 1 : current * 2 + 2;
            }
            if (heap[child] > heap[current]) break;
    
            pair<int, int> tmp = heap[current];
            heap[current] = heap[child];
            heap[child] = tmp;
            current = child;
        }
    }
    bool empty() {
        return heap_size == 0;
    }
    pair<int, int> top() {
        return heap[0];
    }
} pq;

int n;
int brand[MAX_N];
short p[MAX_P], p_cnt[MAX_P];
vector<pair<int,int> > roads[MAX_N];

int dist[MAX_N];
bool visited[MAX_N];

short find(int x) {
    if (p[x] == x) return x;
    return p[x] = find(p[x]);
}

void init(int N, int mBrands[])
{
    n =N;
    for (short i = 0; i < MAX_P; i++) {
        p[i] = i;
        p_cnt[i] = 0;
    }
    for (short i = 0; i < n; i++) {
        brand[i] = mBrands[i];
        p_cnt[brand[i]] += 1;
        roads[i].clear();
    }
}


void connect(int mHotelA, int mHotelB, int mDistance) {
    roads[mHotelA].push_back({ mHotelB, mDistance });
    roads[mHotelB].push_back({ mHotelA, mDistance });
}

int merge(int mHotelA, int mHotelB) {
    short brandA = find(brand[mHotelA]), brandB = find(brand[mHotelB]);
    if (brandA != brandB) {
        p[brandB] = brandA;
        p_cnt[brandA] += p_cnt[brandB];
    }
    return p_cnt[brandA];
}

int move(int mStart, int mBrandA, int mBrandB) {
    int distA = INF, distB = INF;

    pq.clear();
    for (short i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = false;
    }
    
    dist[mStart] = 0;
    pq.push({ 0, mStart });
    while (!pq.empty()) {
        int x = pq.top().second;
        pq.pop();

        if (visited[x]) continue;
        visited[x] = true;
        if (x != mStart && find(brand[x]) == mBrandA && distA > dist[x]) {
            if (mBrandA == mBrandB) distB = distA;
            distA = dist[x];
        }
        else if (x != mStart && find(brand[x]) == mBrandB && distB > dist[x]) {
            distB = dist[x];
        }
        if (distA != INF && distB != INF) break;

        for (auto road : roads[x]) {
            if (dist[road.first] > dist[x] + road.second) {
                dist[road.first] = dist[x] + road.second;
                pq.push({ dist[road.first], road.first });
            }
        }
    }

    return distA + distB;
}