// No. 7 기초 Double Linked List 연습

#define MAX_NODE 10000

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

//초기화 함수 구현
void init()
{
    head = nullptr;
    nodeCnt = 0;
}

//맨 앞에 노드 추가
void addNode2Head(int data) 
{
	Node *node = getNode(data);
	if(head != nullptr){
		head->prev = node;
		node->next = head;
	}
	head = node;
}

//맨 뒤에 노드 추가
void addNode2Tail(int data) 
{
	Node *node = getNode(data);
	if(head == nullptr){
		head = node;
	}
	else{
		Node *cur_node = head;
		while(cur_node->next != nullptr){
			cur_node = cur_node->next;
		}
		cur_node->next = node;
		node->prev = cur_node;
	}
}

//지정된 순서(num)에 노드 추가 (1-2-3-4-5-...)
void addNode2Num(int data, int num) 
{
	if(num <= 1){
		addNode2Head(data);
	}
	else{
		Node *new_node = getNode(data);
		Node *pre_node = head;
		for(int i=1; i<num-1; ++i){
			pre_node = pre_node->next;
		}
		new_node->next = pre_node->next;
		new_node->prev = pre_node;
		pre_node->next = new_node;
		if(new_node->next != nullptr){
			new_node->next->prev = new_node;
		}
	}
}

//주어진 data 값을 갖는 노드의 순서 리턴
int findNode(int data) 
{
	Node *check_node = head;
    int count = 1;
    while(check_node != nullptr){
        if(check_node->data == data){
            return count;
        }
        check_node = check_node->next;
        count++;
    }
    return count;
}

//주어진 data 값을 갖는 노드 삭제
void removeNode(int data) 
{
	Node *current = head;
        while (current != nullptr) {
            if (current->data == data) {
                if (current == head) {
                    head = current->next;
                    if (head != nullptr) {
                        head->prev = nullptr;
                    }
                } else {
                    current->prev->next = current->next;
                    if (current->next != nullptr) {
                        current->next->prev = current->prev;
                    }
                }
                return;
            }
            current = current->next;
        }
}

//output 배열에 리스트 노드의 data를 차례대로 넣고, 총 노드 개수를 리턴
int getList(int output[MAX_NODE]) 
{
	Node* currentNode = head;
    int count = 0;

    while (currentNode != nullptr) {
        output[count] = currentNode->data;
        currentNode = currentNode->next;
        count++;
    }

    return count;
}

//output 배열에 리스트 노드의 data를 역순으로 넣고, 총 노드 개수를 리턴
int getReversedList(int output[MAX_NODE]) 
{
	Node* currentNode = head;
    int count = 0;

    while (currentNode != nullptr) {
        output[count] = currentNode->data;
        currentNode = currentNode->next;
        count++;
    }
	int total = count;
	count--;
	currentNode = head;
	while(currentNode != nullptr){
		output[count] = currentNode->data;
		currentNode = currentNode->next;
		count--;
	}
	

    return total;
}