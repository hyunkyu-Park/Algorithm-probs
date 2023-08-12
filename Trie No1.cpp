
#include<iostream>
#include<cstring>
#include<vector>


using namespace std;
string arr;
char ans[26];
bool visited[26];
int num_order =0;
int order = 0;
char real_ans[26];
bool find_ans;

class Trie{
    static constexpr size_t M = 26; //the number of English alphabet characters, which is 26
    static constexpr char OFFSET = 'a'; //represents the ASCII value of 'a' and is used to index characters.
    
    struct TrieNode{ //struct representing a node in the Trie. 
    
        int child[M]; //stores indices of child nodes
        bool is_terminal; //a flag indicating whether the current node marks the end of a word.

        TrieNode(){ // constructor
            memset(child, -1, sizeof(int) * M); //initialized with -1,
            is_terminal = false;
        }
    };

    vector<TrieNode> nodes; //vector stores all nodes of the Trie.

    public:
        Trie() : nodes(1) {}; //The constructor of the Trie class initializes the nodes vector with a size of 1.
        //클래스의 생성자는 nodes 벡터를 크기 1로 초기화

    void init(){
        nodes.resize(1);
        nodes[0] = TrieNode();
    }

	void insert(const std::string& str) {
		int node_id = 0;
		for (const auto& c : str) {
			if (nodes[node_id].child[c - OFFSET] == -1) {
				nodes[node_id].child[c - OFFSET] = nodes.size();
				nodes.emplace_back();
			}
			node_id = nodes[node_id].child[c - OFFSET];
		}
		nodes[node_id].is_terminal = true;
	}

	void remove(const std::string& str) {
		int node_id = 0;
		for (const auto& c : str) {
			if (nodes[node_id].child[c - OFFSET] == -1) {
				return;
			}
			node_id = nodes[node_id].child[c - OFFSET];
		}
		nodes[node_id].is_terminal = false;
	}

	// bool find(const std::string& str) const {
	// 	int node_id = 0;
	// 	for (const auto& c : str) {
	// 		if (nodes[node_id].child[c - OFFSET] == -1) {
	// 			return false;
	// 		}
	// 		node_id = nodes[node_id].child[c - OFFSET];
	// 	}
	// 	return nodes[node_id].is_terminal;
	// }

	void find(int index, int vertex){

		if(find_ans){
			return;
		}
		visited[vertex] = true;
		
		if(nodes[vertex].is_terminal){
			order++;
			if(order == index){
				find_ans = true;
				for(int i=0; i<num_order; ++i){
					real_ans[i] = ans[i];
				}
				
				return;
			}
		}

		
		for(int i=0; i<26; ++i){
			if(nodes[vertex].child[i] != -1 && !visited[nodes[vertex].child[i]]){
				ans[num_order++] = 'a' + i;
				find(index, nodes[vertex].child[i]);
				num_order--;
			}
			auto check = nodes[vertex].child[i];
			auto check1 = visited[nodes[vertex].child[i]];
			
		}
		
	}
};




int main(int argc, char** argv)
{
	int test_case;
	int T;
	

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		memset(ans, 0, sizeof(ans));
		memset(visited, false, sizeof(visited));
		memset(real_ans, 0, sizeof(real_ans));
		order =0;
		num_order =0;
		
		int index;
		cin >> index;

		cin >> arr;
		
		Trie root;
		root.init();
		for (int i = 0; i < arr.length(); i++) {
			root.insert(arr.substr(i));
		}

		
		//If you search for dfs in reverse order(26-0), it comes in dictionary order after insertion
		//다 삽입하고 dfs 검색하면 사전순으로 나온다
		root.find(index, 0);
		cout << "#" << test_case <<" " << real_ans << "\n";

		
		
		
		

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
