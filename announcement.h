#include <unordered_map>

using namespace std;

unordered_map<int, int> my_map;


// 각 테스트 케이스의 처음에 호출된다.
// 등록된 출퇴근 시각이 없다.
void init() {
    my_map.clear();
	return;
}
// ID가 mId인 사원의 출근 시각 mStart과 퇴근 시각 mEnd을 추가한다.
// 각 시각은 초단위로 주어진다.
// 만약에 이미 존재하는 ID라면, 추가하지 않고 기존의 출퇴근 시각을 변경한다.
// 삭제되었던 사원이 다시 추가될 수도 있다.

// Parameters
//   mId: 사원 ID ( 1 ≤ mId ≤ 1,000,000,000 )
//   mStart: 출근 시각 ( 0 ≤ mStart < 85,400 )
//   mEnd: 퇴근 시각 ( mStart < mEnd < 86,400 )
// Returns
//   출퇴근 시각이 등록된 사원 수를 반환한다.
int add(int mId, int mStart, int mEnd) {
	return 0;
}

// ID가 mId인 사원의 출퇴근 시각을 삭제한다.
// 이미 삭제된 사원의 ID가 주어질 수도 있다.

// Parameters
//   mId: 사원 ID ( 1 ≤ mId ≤ 1,000,000,000 )

// Returns
//   출퇴근 시각이 등록된 사원 수를 반환한다.
int remove(int mId) {
	return 0;
}


// 공지 방송의 시간이 mDuration이고, 방송을 들어야 하는 최소 인원 수가 M명으로 주어진다.
// M명 이상이 방송을 모두 들을 수 있는 가장 빠른 방송 시작 시각을 반환한다.
// 가능한 방송 시작 시각이 없다면 -1을 반환한다.

// Parameters
//   mDuration: 공지 방송 시간 ( 2 ≤ mDuration ≤ 3,600 )
//   M: 방송을 들어야 하는 최소 인원 수 ( 2 ≤ M ≤ 2,500 )

// Returns
//   M명 이상이 방송을 들을 수 있다면, 가장 빠른 방송 시작 시각을 반환한다.
//   그렇지 않을 경우, -1을 반환한다.
int announce(int mDuration, int M) {
	return 0;
}