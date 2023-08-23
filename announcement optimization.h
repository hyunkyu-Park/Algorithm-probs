#include <unordered_map>
#include <cstring>

using namespace std;

struct SEtime{
	int start;
	int end;
};

unordered_map<int, SEtime> my_map; //save start and end time for each mID
int arr[86401]; //Array for storing the number of workers by hour

void init() {
    my_map.clear();
	return;
}
// add an worker works from mStart to mEnd with mID
// Times are given in seconds
// if ID already exist, change the mStart and mEnd
// The removed employee may be added again.

// Parameters
//   mId: worker's ID ( 1 ≤ mId ≤ 1,000,000,000 )
//   mStart: start time ( 0 ≤ mStart < 85,400 )
//   mEnd: end time ( mStart < mEnd < 86,400 )
// Returns
//    the number of employees whose commuting time is registered.
int add(int mId, int mStart, int mEnd) {

	my_map[mId].start = mStart;
	my_map[mId].end = mEnd; 

	return my_map.size();
}

// Delete the commuting time of the employee whose ID is mId.
// An ID of an employee who has already been deleted may be given.

// Parameters
//   mId: worker's ID ( 1 ≤ mId ≤ 1,000,000,000 )

// Returns
//   the number of employees whose commuting time is registered.
int remove(int mId) {
	my_map.erase(mId);
	return my_map.size();
}


// The time of the announcement broadcast is mDuration,
// and the minimum number of people who have to listen to the broadcast is given as M.
// returns the earliest broadcast start time when M or more people can listen to all of the broadcast.
// If there is no possible start time, return -1

// Parameters
//   mDuration: 방송시간 ( 2 ≤ mDuration ≤ 3,600 )
//   M: Minimum number of people to listen to the broadcast ( 2 ≤ M ≤ 2,500 )

// Returns
//   If more than M people can hear the broadcast, it returns the earliest broadcast start time.
//   else return -1
int announce(int mDuration, int M) {
	memset(arr, 0, sizeof(arr));
	for(auto &ele: my_map){
		if (ele.second.end - mDuration >= ele.second.start) {//If the end time - Duration is less than the start time, the worker does not have to be counted
            arr[ele.second.start] += 1; //the worker can listen to the broadcast from start
            arr[ele.second.end - mDuration + 2] -= 1; // but the worker can not listen to the broadcast from end - duration + 2
			//for instance, there is a worker who works from 0 to 4 and the duration time is 2. If the time is 3, the worker can listen 3 and 4(duration 2)
			//but when time is changed to 4, the worker can only listen at 4(duration 1)
			//Likewise, lets say we have same worker(from 0 to 4) and duration time is 3.
			//if time is 2, the worker can listen 2, 3, 4(duration 3)
			//but when time is changed to 3, the worker can only listen 3 and 4(duration 2). 
			//Therefore we do not need to count this worker from 3

        }
	}

	int cur = 0;
    for (int i = 0; i < 86400; ++i) {
        cur += arr[i];
        if (cur >= M) {
            return i;
        }
    }
    return -1;
}

// 1. The init() function is called at the start of each test case.

// 2. In each test case, the number of calls of the add() function is 8,000 or less.

// 3. In each test case, the number of calls of the remove() function is 1,700 or less.

// 4. In each test case, the number of calls of the announce() function is 300 or less.