//
// Created by 87569 on 2020/12/29.
//

#ifndef LEETCODE_BASIC_HEAP_H
#define LEETCODE_BASIC_HEAP_H

#include "iostream"
#include "memory"
#include "vector"

using namespace std;

namespace my_data_structure {

    template<class T>
    void quick_sort(T *, int, int);

    template<class T>
    int partition(T *, int, int);

    template<class T>
    void swap(T *, int, int);

    template<class T>
    class basic_heap {

    protected:
        T *heap{};
        int heap_len{};
        int index;

        explicit basic_heap(int len);

        basic_heap(const basic_heap<T> &other);

        virtual ~basic_heap() = 0;

        virtual void heap_up() = 0;

        virtual void heap_down() = 0;

        T remove_top();

    public:
        virtual void insert(T t) = 0;

        void print();

        virtual unique_ptr<T[]> sort_u(int &size) = 0;

        virtual vector<T> sort_v() = 0;

        int size() {
            return this->index;
        }
    };

    template<class T>
    basic_heap<T>::basic_heap(int len) : heap_len(len) {
        this->heap = new T[len];
        this->index = 0;
    }

    template<class T>
    T basic_heap<T>::remove_top() {
        if (index <= 0)
            return T();
        T r_node = heap[0];
        index--;
        heap[0] = heap[index];
        /* 下沉 */
        heap_down();
        return r_node;
    }

    template<class T>
    void basic_heap<T>::print() {
        for (int i = 0; i < index; ++i) {
            cout << heap[i];
        }
        printf("\n");
    }

    template<class T>
    basic_heap<T>::basic_heap(const basic_heap<T> &other) : heap_len(other.heap_len),
                                                            index(other.index),
                                                            heap(new T[other.heap_len]) {
        /* 深复制 */
        for (int i = 0; i < this->index; ++i) {
            /* 注意这儿不能直接使用等号 */
            this->heap[i] = T(other.heap[i]);
        }
    }

    template<class T>
    basic_heap<T>::~basic_heap() {
        printf("~basic_heap() run\n");
        delete[] this->heap;
    }


    template<class T>
    class min_heap : virtual public basic_heap<T> {
    private:
        void heap_up() override;

        void heap_down() override;

    public:

        explicit min_heap(int len) : basic_heap<T>(len) {}

        min_heap(const min_heap<T> &other) : basic_heap<T>(other) {}

        ~min_heap() override {
//            delete[] this->heap;
        }

        void insert(T t) override;

        unique_ptr<T[]> sort_u(int &size) override;

        vector<T> sort_v() override;
    };

/* 小顶堆求最大的K个数 */
    template<class T>
    void min_heap<T>::insert(T t) {
        if (this->index == this->heap_len) {
            if (t <= this->heap[0]) {
                return;
            }
            this->remove_top();
        }
        this->heap[this->index] = t;
        this->heap_up();
        this->index++;
    }

    template<class T>
    unique_ptr<T[]> min_heap<T>::sort_u(int &size) {
        size = this->index;
        unique_ptr<T[]> res(new T[size]);
        for (int i = 0; i < size; ++i) {
            res[i] = this->remove_top();
        }
        return res;
    }

    template<class T>
    void min_heap<T>::heap_up() {
        int child = this->index;
        int parent = (child - 1) / 2;
        T tmp;
        /* 当parent节点不是根节点时 */
        while (child > 0) {
            /* 小顶堆，父节点大于子节点，下滑 */
            if (this->heap[parent] > this->heap[child]) {
                tmp = this->heap[child];
                this->heap[child] = this->heap[parent];
                this->heap[parent] = tmp;

                child = parent;
                parent = (parent - 1) / 2;
            } else {
                break;
            }
        }
    }

    template<class T>
    void min_heap<T>::heap_down() {
        int parent = 0;
        int child = 2 * parent + 1;
        T tmp;
        /* 当孩子节点不是最后一个节点时 */
        while (child <= this->index) {
            if (child < this->index && this->heap[child + 1] < this->heap[child]) {
                child++;
            }
            /* 小顶堆
             * 大于子节点下滑 */
            if (this->heap[parent] > this->heap[child]) {
                tmp = this->heap[child];
                this->heap[child] = this->heap[parent];
                this->heap[parent] = tmp;

                parent = child;
                child = 2 * child + 1;
            } else {
                break;
            }
        }
    }

    template<class T>
    vector<T> min_heap<T>::sort_v() {
        vector<T> res;
        /* 由于index会变化，所以要将他保存 */
        int len = this->index;
        for (int i = 0; i < len; ++i) {
            res.push_back(this->remove_top());
        }
        return res;
    }

    template<class T>
    class max_heap : virtual public basic_heap<T> {

    private:
        void heap_up() override;

        void heap_down() override;

    public:
        explicit max_heap(int len) : basic_heap<T>(len) {}

        max_heap(const max_heap<T> &other) : basic_heap<T>(other) {}

        ~max_heap() override;

        void insert(T t) override;

        unique_ptr<T[]> sort_u(int &size) override;


        vector<T> sort_v() override;
    };

    template<class T>
    void max_heap<T>::heap_up() {
        /* 大顶堆 */
        int child = this->index;
        int parent = (child - 1) / 2;
        T tmp;
        /* 向上逼近根节点 */
        while (child > 0) {
            /* 大顶堆，父节点小于子节点，交换*/
            if (this->heap[parent] < this->heap[child]) {
                tmp = this->heap[child];
                this->heap[child] = this->heap[parent];
                this->heap[parent] = tmp;

                child = parent;
                parent = (parent - 1) / 2;
            } else break;
        }
    }

    template<class T>
    void max_heap<T>::heap_down() {
        int parent = 0;
        int child = 2 * parent + 1;
        T tmp;
        /* 向下逼近末尾节点 */
        while (child <= this->index) {
            /* 查找左右子树的较大的节点 */
            if (child < this->index && this->heap[child + 1] > this->heap[child]) {
                child++;
            }
            /* 大顶堆，父节点小于子节点，交换 */
            if (this->heap[parent] < this->heap[child]) {
                tmp = this->heap[child];
                this->heap[child] = this->heap[parent];
                this->heap[parent] = tmp;

                parent = child;
                child = 2 * child + 1;
            } else {
                break;
            }
        }
    }

    template<class T>
    void max_heap<T>::insert(T t) {
        /* 大顶堆维护最小的K个数 */
        if (this->index == this->heap_len) {
            if (t >= this->heap[0])
                return;
            this->remove_top();
        }
        this->heap[this->index] = t;
        this->heap_up();
        this->index++;
    }

    template<class T>
    max_heap<T>::~max_heap() {

    }

    /* 逆序的 */
    template<class T>
    unique_ptr<T[]> max_heap<T>::sort_u(int &size) {
        size = this->index;
        unique_ptr<T[]> res(new T[size]);
        for (int i = 0; i < size; ++i) {
            res[i] = this->remove_top();
        }
        return res;
    }

    template<class T>
    vector<T> max_heap<T>::sort_v() {
        vector<T> res;
        int len = this->index;
        for (int i = 0; i < len; ++i) {
            res.push_back(this->remove_top());
        }
        return res;
    }

    template<class T>
    void quick_sort(T *array, int lo, int hi) {
        if (hi <= lo)
            return;
        int j = partition(array, lo, hi);
        quick_sort(array, lo, j - 1);
        quick_sort(array, j + 1, hi);
    }

    template<class T>
    void quick_sort(vector<T> &array) {

    }

    template<class T>
    int partition(T *array, int lo, int hi) {
        int i = lo, j = hi + 1;
        T v = array[lo];
        while (true) {
            while (v > array[++i]) if (i >= hi) break;
            while (v < array[--j]) if (j <= lo) break;
            if (i >= j) break;
            swap(array, i, j);
        }
        swap(array, lo, j);
        return j;
    }

    template<class T>
    inline void swap(T *array, int i, int j) {
        T tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }

}

#endif //LEETCODE_BASIC_HEAP_H