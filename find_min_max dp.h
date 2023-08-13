//void* memcpy(void* dest, const void* src, size_t n);
// dest: Pointer to the destination memory region where the copied data will be stored.
// src: Pointer to the source memory region containing the data to be copied.
// n: Number of bytes to copy.
// memcpy is commonly used to copy data such as arrays or structures from one memory location to another.
// It works at the byte level, making it suitable for copying data of any size.



#include <cstring>
#include <algorithm>
using namespace std;

int list_[230001]; //init: 30000 + add: (100 * 2000) = 230000
int end_ = 0;
int temp_list_[230001];


int max_dp[230001];
int min_dp[230001];

// Number of calls: 1
void init(int N, int mValue[]){
    end_ = N;
    memcpy(list_, mValue, sizeof(int) * N);

	//Check the value from the back and create max-min dp
	max_dp[N - 1] = mValue[N - 1]; 
	min_dp[N - 1] = mValue[N - 1]; 
	for (int i = N - 2; i >= 0; i--) {
		max_dp[i] = max(max_dp[i + 1], mValue[i]);
		min_dp[i] = min(min_dp[i + 1], mValue[i]);
	}

}

// Number of calls: 2000
void add(int M, int mValue[]){
    memcpy(list_ + end_, mValue, sizeof(int) * M); //add input values at the list_

    // 새로 들어온 값에 대한 DP 테이블 갱신
	// add new inputs into the dp tables
    max_dp[end_ + M - 1] = mValue[M - 1];
	min_dp[end_ + M - 1] = mValue[M - 1];
	for (int i = M - 2; i >= 0; i--) {
		max_dp[end_ + i] = max(max_dp[end_ + i + 1], mValue[i]);
		min_dp[end_ + i] = min(min_dp[end_ + i + 1], mValue[i]);
	} 

	// update max_dp, if the existing DP value is greater than the new value, 
	// no further updates are required (The values on the left are unchanged)
	for (int i = end_ - 1; i >= 0; i--) {
		if (max_dp[i] < max_dp[i + 1]) {
			max_dp[i] = max_dp[i + 1];
		}
		else break;
	} 

	// update min_dp, if the existing DP value is less than the new value, 
	// no further updates are required (The values on the left are unchanged)
	for (int i = end_ - 1; i >= 0; i--) {
		if (min_dp[i] > min_dp[i + 1]) {
			min_dp[i] = min_dp[i + 1];
		}
		else break;
	} 
	end_ += M;
}
// The worst case scenario is when you need to refresh every single elements in the table,
// but in this case, the other tables does not need to be refreshed 
// O(N)

//Number of calls: 500
void erase(int mFrom, int mTo) {
    int size = (end_ - mTo);
	int byte_size = sizeof(int) * size;

	//save the list after mTo at the temp_list_, and add this temp_list_ at the list_ from the mFrom
    memcpy(temp_list_, list_ + mTo, byte_size);
    memcpy(list_ + mFrom - 1, temp_list_, byte_size); //Since memcpy is a block-by-block copy method, it requires temporary arrangement

	int pre_max = max_dp[mFrom - 1]; //Max value of the list after mTo.
	int pre_min = min_dp[mFrom - 1]; //Min value of the list after mTo.

    //update max_dp 
	memcpy(temp_list_, max_dp + mTo, byte_size);
	memcpy(max_dp + mFrom - 1, temp_list_, byte_size);

    //update min_dp
	memcpy(temp_list_, min_dp + mTo, byte_size);
	memcpy(min_dp + mFrom - 1, temp_list_, byte_size);

    //update end
	end_ -= (mTo - mFrom + 1);

	// check if the mTo is the last index of the original index,
	// if so, you need to change the value at [mFrom-1], because index of the dp is not changed
	if (end_ == mFrom - 1) {
		max_dp[mFrom - 1] = -1;
		min_dp[mFrom - 1] = 100000000;
	}

	for (int i = mFrom - 2; i >= 0; i--) { // Update dp from the point where the front part and the back part of the list meet
		max_dp[i] = max(max_dp[i + 1], list_[i]); // Update dp table 
		if (pre_max <= max_dp[i]) break; //max_dp[i] >= pre_max -> it means current list_[i] is max -> it means no further updates are required (The values on the left are unchanged)	
		} //Because the left(front) part of the list is not changed

	for (int i = mFrom - 2; i >= 0; i--) {
		min_dp[i] = min(min_dp[i + 1], list_[i]);
		if (pre_min >= min_dp[i]) break; //min_dp[i] is <= pre_max -> it means current list_[i] is min -> it means no further updates are required (The values on the left are unchanged)
	}

}
//The worst case scenario is when you need to refresh every single elements in the table,
// but in this case, the other tables does not need to be refreshed 
// O(N)


// Number of calls: 30000
int find(int K) {
    return max_dp[end_ - K] - min_dp[end_ - K];
} // O(1)