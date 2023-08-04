
// No. 6 기초 Single Linked List 구현 연습

#define MAX_NODE 10000

struct Node {
	int data;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}


//초기화 함수 구현
void init()
{
    //head->next로 작성하면 head 포인터가 nullptr일 경우 segentation fault 발생
	head= nullptr;
    nodeCnt= 0;
}

//맨 앞에 노드 추가
void addNode2Head(int data) 
{
    Node *node = getNode(data);
    if(head == nullptr){
        head = node;
    }
    else{
        node->next= head;
        head = node;
    }
    

}

//맨 뒤에 노드 추가
void addNode2Tail(int data) 
{
	Node *node = getNode(data);
    if (head == nullptr) {
        head = node;
    } else {
        Node* currentNode = head;
        while (currentNode->next != nullptr) {
            currentNode = currentNode->next;
        }
        currentNode->next = node;
    }

}


//지정된 순서(num)에 노드 추가 (1-2-3-4-5-...)
void addNode2Num(int data, int num) 
{
	Node *node = getNode(data);
    Node *prev_ptr = head;
    if(num <=1){
        node->next = head;
        head = node;
        return;
    }
    else{
        for(int i=1; i<num-1; ++i){
            prev_ptr =prev_ptr->next;    
        }
        node->next = prev_ptr->next;
        prev_ptr->next = node;
    }

    
}

//주어진 data 값을 갖는 노드 삭제
void removeNode(int data) 
{
    if (head->data == data) {
        head = head->next;
        return;
    }
	Node* cur_ptr = head;
    while (cur_ptr->next != nullptr && cur_ptr->next->data != data) {
        cur_ptr = cur_ptr->next;
    }

    if (cur_ptr->next != nullptr) {
        cur_ptr->next = cur_ptr->next->next;

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