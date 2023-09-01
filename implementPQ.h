#include < algorithm >
#include < cassert >

class MaxHeap {
#define parent (i >> 1)
#define left (i << 1)
#define right (i << 1 | 1)

	static constexpr size_t MAX_N = 100000;

	int data[MAX_N + 1];
	size_t size;

public:
	MaxHeap() = default;

	// x 삽입
	void push(int x) {
		data[++size] = x;
		for (int i = size; parent != 0 && data[parent] < data[i]; i >>= 1) {
			std::swap(data[parent], data[i]);
		}
	}

	// 최대값 리턴
	int top() const {
		assert(size != 0);
		return data[1];
	}

	// 최대값 삭제
	void pop() {
		assert(size != 0);
		data[1] = data[size--];
		for (size_t i = 1; left <= size;) {
			if (left == size || data[left] > data[right]) {
				if (data[i] < data[left]) {
					std::swap(data[i], data[left]);
					i = left;
				} else {
					break;
				}
			} else {
				if (data[i] < data[right]) {
					std::swap(data[i], data[right]);
					i = right;
				} else {
					break;
				}
			}
		}
	}

#undef parent
#undef left
#undef right
};