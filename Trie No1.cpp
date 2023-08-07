
#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

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

	bool find(const std::string& str) const {
		int node_id = 0;
		for (const auto& c : str) {
			if (nodes[node_id].child[c - OFFSET] == -1) {
				return false;
			}
			node_id = nodes[node_id].child[c - OFFSET];
		}
		return nodes[node_id].is_terminal;
	}
};




int main(int argc, char** argv)
{
	int test_case;
	int T;
	string arr;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		cin >> arr;
		
		Trie root;
		root.init();
		for (int i = 0; i < arr.length(); i++) {
			root.insert(arr.substr(i));
		}
		//If you search for dfs in reverse order(26-0), it comes in dictionary order after insertion
		//다 삽입하고 역순(26~0)으로 dfs 검색하면 사전순으로 나온다
		bool check1 = root.find("abac");
		bool check2 = root.find("bac");
		bool check3 = root.find("ac");
		bool check4 = root.find("c");
		bool check5 = root.find("ca");
		cout <<1;

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
