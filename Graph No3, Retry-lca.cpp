//영준이의 진짜 BFS   

#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

#define swap(a,b) {int tmp=a; a = b ; b= tmp;}

vector<int> adj[100001];
queue<int> q;
int parent[100001][19];
int depth[100001];
int N;
long long sum;

void make_depth(int node) {
	int prev = 1;
	for (int next : adj[1]) {
		q.push(next);
		depth[next] = 1;
	}
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		for (int next : adj[cur]) {
			q.push(next);
			depth[next] = depth[cur] + 1;

		}
	}
}

void connect() {
	for (int k = 1; k < 19; k++) {
		for (int cur = 1; cur <= N; cur++) {
			parent[cur][k] = parent[parent[cur][k - 1]][k - 1];
		}
	}
}

int LCA(int u, int v) {
	if (depth[u] < depth[v])
		swap(u, v);
	int diff = depth[u] - depth[v];
	for (int i = 0; diff != 0; i++) {
		if ((diff & 1))
			u = parent[u][i];
		diff = diff >> 1;
	}
	if (u != v) {
		for (int i = 16; i >= 0; i--) {
			if (parent[u][i] != 0 && parent[u][i] != parent[v][i]) {
				u = parent[u][i];
				v = parent[v][i];
			}
		}
		u = parent[u][0];
	}
	return u;
}

void BFS() {
	int prev = 1;
	for (int next : adj[1]) {
		q.push(next);
	}
	while (!q.empty()) {
		int cur = q.front(); q.pop();
		for (int next : adj[cur]) {
			q.push(next);

		}
		int ac = LCA(cur, prev);
		sum += depth[cur] + depth[prev] - 2 * depth[ac];
		prev = cur;
	}
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	//freopen("input.txt", "r", stdin);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N;
		memset(parent, 0, sizeof(parent));
		memset(depth, -1, sizeof(depth));
		q = queue<int>();
		depth[1] = 0; sum = 0;
		for (int i = 0; i <= N; i++) {
			adj[i].clear();
		}
		for (int i = 2; i <= N; i++) {
			cin >> parent[i][0];
			adj[parent[i][0]].push_back(i);
		}
		make_depth(1);
		connect();
		BFS();
		cout << "#" << test_case << " " << sum << "\n";
	}

	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}