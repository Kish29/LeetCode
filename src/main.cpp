//
// Created by 87569 on 2020/12/18.
//

#include <utility>

#include "LeetCode.h"
#include "iostream"
#include "sys/time.h"
//#include "Others.h"
#include "basic_heap.h"

class student {
private:
    string name;
    long long student_id;

public:
    student() : name("default_student"), student_id(0) {}

    student(string &name, long long id) : name(name), student_id(id) {}

    student(string name, long long id) : name(std::move(name)), student_id(id) {}

    friend bool operator<(const student &s1, const student &s2) {
        return s1.student_id < s2.student_id;
    }

    friend bool operator<=(const student &s1, const student &s2) {
        return s1.student_id <= s2.student_id;
    }

    friend bool operator>=(const student &s1, const student &s2) {
        return s1.student_id >= s2.student_id;
    }

    friend bool operator>(const student &s1, const student &s2) {
        return s1.student_id > s2.student_id;
    }

    friend bool operator!=(const student &s1, const student &s2) {
        return s1.student_id != s2.student_id;
    }

    friend bool operator==(const student &s1, const student &s2) {
        return s1.student_id == s2.student_id;
    }

    friend void operator<<(ostream &os, const student &s) {
        os << "{name: " << s.name << ", student_id: " << s.student_id << "}" << endl;
    }

};

using namespace my_data_structure;

int main(int argc, char **argv) {
    srand(time(nullptr));

    int num;
    scanf("%d", &num);
    unique_ptr<min_heap<student>>
            h(new min_heap<student>(num));
    for (int i = 0; i < num; ++i) {
        h->insert(student("tom", i + 1));
    }
    h->print();

    timeval start{}, end{};
    gettimeofday(&start, nullptr);
    gettimeofday(&end, nullptr);
    long time = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("duration time -> %ld ms", time / 1000);
}
