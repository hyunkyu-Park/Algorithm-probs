
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
    
};


int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}