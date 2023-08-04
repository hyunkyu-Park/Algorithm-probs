//array를 사용해서 stack이나 queue대신 사용할 수 있다.

struct Node{
	int arr[5];
};

Node node[100];



void dfs_init(int N, int path[100][2])
{
	for(int i=0; i<100; ++i){
        for(int j=0; j<5; ++j){
            node[i].arr[j] = 0;
        }
    }

    for(int i=0; i<N-1; ++i){
        int index=0;
		while(true){
			if(node[path[i][0]].arr[index] <= 0){
				node[path[i][0]].arr[index] = path[i][1];
				index = 0;
				break; 
			}	
			index++;
		}
	}


}

bool is_val(int target, int n){
	if(n>target){
		return true;
	}
}

int dfs(int n)
{
	int target = n;
	int top = -1; //stack 가장 위를 표시
	bool visited[100] = {0};
	int stack[100] = {0};

	stack[++top] = n;
	while(top != -1){
		int cur = stack[top--];
		if(cur>n){
			return cur;
		}
		if(!visited[cur]){
			visited[cur] = true;

			for(int next=4; next>=0; --next){
				if(!visited[node[cur].arr[next]] && node[cur].arr[next] >0){
					stack[++top] = node[cur].arr[next];
				}
			}
		}
	}
	return -1;
}
