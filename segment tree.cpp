#include <iostream>

//segment tree

constexpr size_t n = 5;
//   index: 0   1  2  3   4   5
int a[n] = {5, -1, 3, 2, -8};

int segtree[2 * n];

//                                           1[0, 5)
//                    -1[0, 1)+[3, 5)                               2[1, 3)
//          -6[3, 5)                  5[0, 1)             -1[1, 2)           3[2, 3)
//    2[3,4)        -8[4,5)             

void init() {
    // segment tree starts from index 1. It does not use index 0 in array
    // store the elements of the array at leaf nodes of segment tree
    for (size_t i = 0; i < n; ++i) {  //segtree의 5, 6, 7, 8, 9에(리프노드들) a[n]의 값들을 저장한다
        segtree[i + n] = a[i];
    }

    // fill the un-leaf nodes
    // segment[i] is sum of left child(i<<1) and right child(i<<1 | 1)
    for (size_t i = n - 1; i != 0; --i) {
        //for example, left child of index 2 is 4 and right child of index 2 is 5
        //index 2 is 10 in binary. 2<<1 is 100 and it is 4 in decimal number
        //at the same time 100 | 1 is 101, which is 5 in decimal number
        segtree[i] = segtree[i << 1] + segtree[i << 1 | 1];
    }
}

// 2.4. Point Update
// if one elements(leaf node) is changed, 
// then every range that contains that element(all ancestor of the leaf node) must be updated

// change the value of index i into x
void update(size_t i, int x) {

    //update the leaf node that contains the value of index i
    segtree[i += n] = x;
    
    while (i >>= 1) { //Update all parent nodes up to the root note, moving i by 1 bit to the right
        segtree[i] = segtree[i << 1] + segtree[i << 1 | 1]; //segtree[i] is sum of left and right child nodes
    }

}

// if node l is the left child(even index), you don't need to add the value
// skip this case, because if you add the parent then you can get not only left value but also both values

// However, if the l is right child(odd index),
// if you do not add the value and go up, then the value of the left child is added which is not in the range
// therefore, just add the value at l and remove the l in the range

// r is in the same logic
int query(size_t l, size_t r) {
    int result = 0;
    for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
        if (l & 1) result += segtree[l++];
        if (r & 1) result += segtree[--r];
    }

    return result;
}

int main(){
    init();
    query(0, 3);
}
