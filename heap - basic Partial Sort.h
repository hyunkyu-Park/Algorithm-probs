
using namespace std;

struct Node{
	int money;
	int id;
};

Node heap[11];
int heap_idx; //pq에 값이 몇개 들어가있나 확인하는 변수
void init()
{
	for (int i = 0; i < 11; i++) {
		heap[i].id = 0;
		heap[i].money = 0;
	}
	heap_idx = 0;
}
bool priority(Node a, Node b) {
	if (a.money == b.money) { //돈이 같다면 유저 아이디가 높은 게 우선순위를 갖는다.
		return a.id < b.id;
	}
	return a.money > b.money;
}
void adjust(int idx) {
	while (idx/2 > 0 && priority(heap[idx], heap[idx/2])) {//부모 노드가 있고(최상위 노드가 아니고) && 부모노드보다 우선순위가 높은 경우
		Node tmp = heap[idx / 2]; //부모자리의 노드 저장
		heap[idx / 2] = heap[idx]; //부모 노드에 idx(우선순위가 더 높은 자식) 저장
		heap[idx] = tmp; //자식 노드에 원래 부모 노드 값 저장
		idx = idx / 2;
	}
}

Node heap_pop(Node heap[],int _idx){
	Node ret = heap[1]; //heap 첫번째 값
	heap[1] = heap[_idx--]; //힙의 마지막 값을 최상위 노드에 저장
	int cur = 1,child=1;
	while ((cur*2) <= _idx ) {
		if (priority(heap[cur * 2], heap[cur * 2 + 1])) {
			child = cur * 2;
		}
		else 
			child = cur * 2 + 1;
		
		if (priority(heap[child], heap[cur])) {
			Node tmp = heap[cur];
			heap[cur] = heap[child];
			heap[child] = tmp;
			cur = child;
		}
		else break;
	}
	return ret;
}

void addUser(int uID, int income)
{
	
	if (heap_idx < 10) {
		heap[++heap_idx].id = uID;
		heap[heap_idx].money = income;
		adjust(heap_idx);
	}
	else {
		//그냥 마지막 노드 찍으면 안됨. 팝을 했을경우 마지막 노드가 우선순위가 가장 낮은 노드가 아님.
		//우선순위가 가장 낮은 노드 찾기
		int thres = 1e9, thres_id=0,thres_idx = 0;
		for (int i = 1; i <= heap_idx; i++) {
			if (thres >= heap[i].money) {
				if (thres == heap[i].money) {
					if (thres_id > heap[i].id)
						continue;
				}
				thres = heap[i].money;
				thres_id = heap[i].id;
				thres_idx = i;
			}
		}

		//우선순위가 가장낮은 노드가 새로 들어오는 값보다 크다면 아무일 없음
		if (income <= thres)
			return;
		//아니라면 해당 자리에 새로운 값 넣고
		heap[thres_idx].id = uID;
		heap[thres_idx].money = income;
		
		//재정렬
		adjust(thres_idx);
	
	}	

}

int getTop10(int result[10])
{
	int T = heap_idx;
	Node tmp_heap[11] = { 0 };
	for (int i = 1; i <= T; i++) {
		tmp_heap[i] = heap[i];
	}

	for (int i = 0; i < T; i++) {
		Node res = heap_pop(tmp_heap,T-i);
		result[i] = res.id;
	}
	
	return T;
}