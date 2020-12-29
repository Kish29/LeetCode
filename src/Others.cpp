//
// Created by 87569 on 2020/12/29.
//
#include "Others.h"
#include "cstdio"

const int max_n = 1e4;

int bean[max_n]{0};


void integer_divide(int num, int k) {
    if (num > 1e4) {
        printf("integer too large\n");
    }
    int i, left;
    for (i = 1; i <= num; i++) {
        /* 保证不重复拆分 */
        if (i >= bean[k - 1]) {
            bean[k] = i;
            left = num - i;
            if (left == 0) {
                array_print(bean, k + 1);
            } else {
                integer_divide(left, k + 1);
            }
        }
    }
}

inline void array_print(int *array, int len) {
    int i = 1;
    for (; i < len - 1; ++i) {
        printf("%d+", array[i]);
    }
    printf("%d\n", array[i]);
}

void integer_divide_entry(int num) {
    integer_divide(num, 1);
}

int stone_pile(int *stones, int stones_num) {
    if (stones == nullptr || stones_num <= 0)
        return 0;
    int i;
    auto *h = new min_heap(stones_num);
    for (i = 0; i < stones_num; i++) {
        h->insert(stones[i]);
    }
    int res = h->remove_top();
    int sum = 0;
    while (!h->empty()) {
        res += h->remove_top();
        sum += res;
    }
    delete h;
    return sum;
}
