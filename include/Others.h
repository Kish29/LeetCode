//
// Created by 87569 on 2020/12/29.
//

#ifndef LEETCODE_OTHERS_H
#define LEETCODE_OTHERS_H

#include <cstdio>
#include "cstdlib"
#include "memory"


using std::unique_ptr;

/* 堆石子问题
 * 合并两堆石子的最小花费
 * 贪心算法 */
int stone_pile(int *stones, int stones_num);

/* 整数拆分
 * num是待拆分的整数
 * k表示拆分的次数 */
void integer_divide(int num, int k);

void integer_divide_entry(int num);

void array_print(int *array, int len);


/* 维护一个小顶堆 */
class min_heap {
private:
    int *heap{};

    int heap_len{};

    /* 时钟指向下一个空闲的堆节点 */
    int index{};

    void heap_up() {
        int child = index;
        int parent = (child - 1) / 2;
        int tmp;
        while (child > 0) {
            if (heap[parent] > heap[child]) {
                tmp = heap[child];
                heap[child] = heap[parent];
                heap[parent] = tmp;

                child = parent;
                parent = (parent - 1) / 2;
            } else break;
        }
    }

    void heap_down() {
        int parent = 0;
        int child = 2 * parent + 1;
        int tmp;
        while (child <= index) {
            if (child < index && heap[child + 1] < heap[child]) {
                child++;
            }
            if (heap[parent] > heap[child]) {
                tmp = heap[child];
                heap[child] = heap[parent];
                heap[parent] = tmp;

                parent = child;
                child = 2 * child + 1;
            } else break;
        }
    }

public:
    explicit min_heap(int len) : heap_len(len) {
        this->heap = new int[heap_len];
        this->index = 0;
    }

    ~min_heap() {
        printf("destructor of min_heap\n");
        delete[] heap;
    }

    void insert(int n) {
        if (index == heap_len) {
            if (n <= heap[0])
                return;
            remove_top();
        }
        heap[index] = n;
        heap_up();
        index++;
    }

    int remove_top() {
        if (index <= 0)
            return -1;
        index--;
        int r_node = heap[0];
        heap[0] = heap[index];
        heap_down();
        return r_node;
    }

    bool empty() const {
        return index <= 0;
    }

    void print_elements() const {
        for (int i = 0; i < index; ++i) {
            printf("%d ", heap[i]);
        }
        printf("\n");
    }

    unique_ptr<int[]> sort_i() {
        unique_ptr<int[]> res(new int[index]);
        int len = index;
        for (int i = 0; i < len; ++i) {
            res[i] = remove_top();
        }
        return res;
    }
};

/* 维护一个大顶堆 */
class max_heap {
private:
    int *heap{};

    int heap_len{};

    /* 时钟指向下一个空闲的堆节点 */
    int index{};

    void heap_up() {
        int child = index;
        int parent = (child - 1) / 2;
        int tmp;
        while (child > 0) {
            if (heap[parent] < heap[child]) {
                tmp = heap[child];
                heap[child] = heap[parent];
                heap[parent] = tmp;

                child = parent;
                parent = (parent - 1) / 2;
            } else break;
        }
    }

    void heap_down() {
        int parent = 0;
        int child = 2 * parent + 1;
        int tmp;
        while (child <= index) {
            if (child < index && heap[child + 1] < heap[child]) {
                child++;
            }
            if (heap[parent] < heap[child]) {
                tmp = heap[child];
                heap[child] = heap[parent];
                heap[parent] = tmp;

                parent = child;
                child = 2 * child + 1;
            } else break;
        }
    }

public:
    explicit max_heap(int len) : heap_len(len) {
        this->heap = new int[heap_len];
        this->index = 0;
    }

    ~max_heap() {
        printf("destructor of min_heap\n");
        delete[] heap;
    }

    void insert(int n) {
        if (index == heap_len) {
            if (n <= heap[0])
                return;
            remove_top();
        }
        heap[index] = n;
        heap_up();
        index++;
    }

    int remove_top() {
        if (index <= 0)
            return -1;
        index--;
        int r_node = heap[0];
        heap[0] = heap[index];
        heap_down();
        return r_node;
    }

    bool empty() const {
        return index <= 0;
    }

    void print_elements() const {
        for (int i = 0; i < index; ++i) {
            printf("%d ", heap[i]);
        }
        printf("\n");
    }

    unique_ptr<int[]> sort_i() {
        unique_ptr<int[]> res(new int[index]);
        int len = index;
        for (int i = len - 1; i >= 0; i--) {
            res[i] = remove_top();
        }
        return res;
    }
};


#endif //LEETCODE_OTHERS_H
