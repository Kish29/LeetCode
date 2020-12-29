//
// Created by 87569 on 2020/12/29.
//

#ifndef LEETCODE_BASIC_HEAP_H
#define LEETCODE_BASIC_HEAP_H

#include "iostream"
#include "memory"

using namespace std;

namespace my_data_structure {

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

        virtual unique_ptr<T[]> sort_u() = 0;

        virtual vector<T> sort_v() = 0;
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
            cout << heap[i] ;
        }
        printf("\n");
    }

    template<class T>
    basic_heap<T>::basic_heap(const basic_heap<T> &other) : heap_len(other.heap_len), index(other.index) {
        this->heap = new T[other.heap_len];
        for (int i = 0; i < this->index; ++i) {
            this->heap[i] = other.heap[i];
        }
    }

    template<class T>
    basic_heap<T>::~basic_heap() {}


    template<class T>
    class min_heap : virtual public basic_heap<T> {
    private:
        void heap_up() override;

        void heap_down() override;

    public:

        explicit min_heap(int len) : basic_heap<T>(len) {}

        min_heap(const min_heap<T> &other) : basic_heap<T>(other) {}

        ~min_heap() override {
            delete[] this->heap;
        }

        void insert(T t) override;

        unique_ptr<T[]> sort_u() override;

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
    unique_ptr<T[]> min_heap<T>::sort_u() {
        unique_ptr<T[]> res(new T[this->index]);
        int len = this->index;
        for (int i = 0; i < len; ++i) {
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

    };
}

#endif //LEETCODE_BASIC_HEAP_H