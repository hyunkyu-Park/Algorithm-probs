//1248. [S/W 문제해결 응용] 3일차 - 공통조상

#include<iostream>
#include<deque>
#include<string.h>

using namespace std;

struct Node{
    int parent = 0;
    int left = 0;
    int right = 0;
};

Node node[10001];
bool check[100001];


int dfs(int n){
	bool visited[100001];
	memset(visited, 0, sizeof(visited));
	deque<int> my_stack;
	my_stack.push_back(n);
	

	int ans = 1;
	while(!my_stack.empty()){
		int cur = my_stack.back();
		visited[cur] = true;
		my_stack.pop_back();

		if(node[cur].left != 0){
			if(!visited[node[cur].left]){
				my_stack.push_back(node[cur].left);
				ans++;
			}
		}
		if(node[cur].right != 0){
			if(!visited[node[cur].right]){
				my_stack.push_back((node[cur].right));
				ans++;
			}
		}
	}
	return ans;
	

}

int main()
{
	int test_case;
	int T;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{

		int V, E, A, B, parent, child;
        cin >> V >> E >> A >> B;
		memset(node,0,sizeof(node));
		memset(check,0,sizeof(check));

		for(int i=0; i<E; ++i){
			cin >> parent >> child;
			node[child].parent = parent;
			if(node[parent].left ==0){
				node[parent].left = child;
			}
			else{
				node[parent].right = child;
			}
		}

		
		int cur = node[A].parent;
		while (true) {
            check[cur] = true;
            // root 노드에 도달한 경우
            if (cur == 1) break;
            // 부모 노드 거슬러 올라가기
            cur = node[cur].parent;
        }

        cur = node[B].parent;
		int common_ancester;
        while (true) {
            // tg1 조상 노드 탐색 과정에서 방문한 곳인 경우
            if (check[cur]) {
                // 처음으로 중복방문 되는 곳이 가장 가까운 공통 조상
                // 해당 노드를 기준으로 서브트리 크기 조사
				common_ancester = cur;
                break;
            }
            cur = node[cur].parent;
        }
		


		int total = dfs(common_ancester);

		printf("#%d %d %d\n", test_case, common_ancester, total);

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}