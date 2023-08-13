#include < algorithm >
#define BUCKET_MAX_NUM_LENGTH 500
#define INF 999999999

using namespace std;
struct Bucket {
    int len;
    int min_num, max_num;
    int nums[BUCKET_MAX_NUM_LENGTH];
    Bucket *prev, *next;

    void init (Bucket *_prev, Bucket *_next) {
        len = 0;
        prev = _prev;
        next = _next;
        min_num = INF;
        max_num = -INF;
    }
    void push_back (int num) {
        nums[len++] = num;
        min_num = min(min_num, num);
        max_num = max(max_num, num);
    }
    void recalculate () {
        min_num = INF;
        max_num = -INF;
        for (int i = 0; i < len; i++) {
            min_num = min(min_num, nums[i]);
            max_num = max(max_num, nums[i]);
        }
    }
};

int pool_last_idx;
Bucket pool[500];
Bucket bucket_begin, bucket_end;

void add (int mValue_len, int mValue[]) {
    for (int i = 0; i < mValue_len; i++) {
        if (bucket_end.prev->len >= BUCKET_MAX_NUM_LENGTH) {
            pool[++pool_last_idx].init(bucket_end.prev, &bucket_end);
            bucket_end.prev->next = &pool[pool_last_idx];
            bucket_end.prev = &pool[pool_last_idx];
        }
        bucket_end.prev->push_back(mValue[i]);
    }
}

void init (int mValue_len, int mValue[]) {
    pool_last_idx = 0;
    pool[0].init(&bucket_begin, &bucket_end);
    bucket_begin.next = &pool[0];
    bucket_end.prev = &pool[0];

    add(mValue_len, mValue);
}

void erase (int mFrom, int mTo) {
    int skip = mFrom - 1;
    int rest = mTo - mFrom + 1;
    Bucket *bucket = bucket_begin.next;

    while (skip >= bucket->len) {
        skip -= bucket->len;
        bucket = bucket->next;
    }
    while (rest > 0 && bucket->len - skip <= rest) {
        rest -= bucket->len - skip;
        bucket->len = skip;
        bucket->recalculate();

        if (bucket->len == 0) {
            bucket->prev->next = bucket->next;
            bucket->next->prev = bucket->prev;
        }

        bucket = bucket->next;
        skip = 0;
    }
    if (rest > 0) {
        if (
            bucket->prev != &bucket_begin
            && bucket->prev->len + bucket->len - rest <= BUCKET_MAX_NUM_LENGTH
        ) {
            for (int i = 0; i < skip; i++) {
                bucket->prev->push_back(bucket->nums[i]);
            }
            for (int i = skip + rest; i < bucket->len; i++) {
                bucket->prev->push_back(bucket->nums[i]);
            }
            bucket->prev->next = bucket->next;
            bucket->next->prev = bucket->prev;
        }
        else {
            for (int i = skip + rest; i < bucket->len; i++) {
                bucket->nums[i - rest] = bucket->nums[i];
            }
            bucket->len -= rest;
            bucket->recalculate();
        }
    }
}

int find (int m) {
    Bucket *bucket = bucket_end.prev;
    int min_num = INF;
    int max_num = -INF;

    while (m > 0) {
        if (bucket->len >= m) {
            for (int i = bucket->len - m; i < bucket->len; i++) {
                min_num = min(min_num, bucket->nums[i]);
                max_num = max(max_num, bucket->nums[i]);
            }
            m = 0;
        }
        else {
            min_num = min(min_num, bucket->min_num);
            max_num = max(max_num, bucket->max_num);
            m -= bucket->len;
        }
        bucket = bucket->prev;
    }
    return max_num - min_num;
}