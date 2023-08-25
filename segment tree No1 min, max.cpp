// Write a program that handles the following two queries from a series a0, a1, ⋯, an-1 (0≤ai≤109) with length n

// •  0 i x    :    change ai to x (0 ≤ i ≤ n - 1, 0 ≤ x ≤ 109)
// •  1 l r    :    print the result of max(al, al+1, ⋯, ar-1) - min(al, al+1, ⋯, ar-1). (0 ≤ l < r ≤ n)
 
// [INPUT]
// The number of Testcase T is given in the first line

// length of the array 'n' and number of queries 'q' are given in the first line of the each testcase
// array a is given in the second line
// queries are given across q lines from the third line.
 

// [OUTPUT]
// For each test case, the result of query 1 is printed by dividing into spaces.

// input
// 2
// 5 5
// 1 2 3 4 5
// 1 0 5
// 1 1 4
// 0 2 9
// 1 0 5
// 1 1 4
// 3 4
// 0 5 10
// 1 0 3
// 0 0 5
// 0 2 5
// 1 0 3

// output
// #1 4 2 8 7
// #2 10 0

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class SegmentTree {
private:
    size_t n;
    std::vector<int> a;
    std::vector<int> max_segtree;
    std::vector<int> min_segtree;

public:
    SegmentTree(const std::vector<int>& input) {
        n = input.size();
        a = input;
        max_segtree.resize(2 * n);
        min_segtree.resize(2 * n);
        init();
    }


    // segment tree starts from index 1. It does not use index 0 in array
    // store the elements of the array at leaf nodes of segment tree
    void init() {
        for (size_t i = 0; i < n; ++i) {
            max_segtree[i + n] = a[i];  //store values in array a at leaf nodes in the segment tree
            min_segtree[i + n] = a[i];
        }

        // fill the un-leaf nodes
        // segment[i] is max or min of left child(i<<1) and right child(i<<1 | 1)
        for (size_t i = n - 1; i != 0; --i) {
            //for example, left child of index 2 is 4 and right child of index 2 is 5
            //index 2 is 10 in binary. 2<<1 is 100 and it is 4 in decimal number
            //at the same time 100 | 1 is 101, which is 5 in decimal number
            max_segtree[i] = std::max(max_segtree[i << 1], max_segtree[i << 1 | 1]);
            min_segtree[i] = std::min(min_segtree[i << 1], min_segtree[i << 1 | 1]);
        }
    }

    // if one elements(leaf node) is changed, 
    // then every range that contains that element(all ancestor of the leaf node) must be updated

    // change the value of index i into x
    void update(size_t i, int x) {

        //update the leaf node that contains the value of index i
        max_segtree[i += n] = x;
        min_segtree[i] = x;

        // Same result as the above codes, but above one is faster
        // max_segtree[i + n] = x;
        // min_segtree[i + n] = x;
        // i += n;

        while (i >>= 1) { //Update all parent nodes up to the root note, moving i by 1 bit to the right
            max_segtree[i] = std::max(max_segtree[i << 1], max_segtree[i << 1 | 1]); //max_segtree[i] is max of left and right child nodes
            min_segtree[i] = std::min(min_segtree[i << 1], min_segtree[i << 1 | 1]); //min_segtree[i] is min of left and right child nodes
        }
    }


    // if node l is the left child(even index), you don't need to compare the value
    // skip this case, because if you compare the parent then you can compare not only left value but also both values

    // However, if the l is right child(odd index),
    // if you do not compare the value and go up, then the value of the left child is compared which is not in the range
    // therefore, just compare the value at l and remove the l in the range

    // r is in the same logic
    int query(size_t l, size_t r) {
        int max_result = 0;
        int min_result = 1e9;

        for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
            if (l & 1) {
                max_result = std::max(max_result, max_segtree[l]);
                min_result = std::min(min_result, min_segtree[l]);
                l++;
            }
            
            if (r & 1) {
                max_result = std::max(max_result, max_segtree[r - 1]);
                min_result = std::min(min_result, min_segtree[r - 1]);
                r--;
            }
        }

        return max_result - min_result;
    }
};

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
	int test_case;
	int T;

	cin>>T;

    int n, q;
    int order, first, second;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> n >> q;
        vector<int> v1(n);
        for(int i=0; i<n; ++i){
            cin >> v1[i];
        }
        SegmentTree seg_tree(v1);

        cout << "#" << test_case <<" ";

        for(int i=0; i<q; ++i){
            cin >> order >> first>> second;
            switch (order)
            {
            case 0:
                seg_tree.update(first, second);
                break;
            
            case 1:
                cout << seg_tree.query(first, second) << " ";
                break;
            default:
                break;
            }
        }
        cout << "\n";

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}