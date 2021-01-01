//
// Created by 87569 on 2020/12/18.
//

#include <utility>

//#include "LeetCode.h"
#include "iostream"
#include "sys/time.h"
#include "cstring"
//#include "Others.h"
#include "basic_heap.h"

const char *digits = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

char *random_str(int len);

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
        /* 用printf提升性能！！！*/
        printf("{name: %s, student_id: %d}\n", s.name.c_str(), s.student_id);
//        os << "{name: " << s.name << ", student_id: " << s.student_id << "}" << endl;
    }

};

using namespace my_data_structure;

int main(int argc, char **argv) {
    srand(time(nullptr));

    int num;
    scanf("%d", &num);
    auto *s = new float[num];
    for (int i = 0; i < num; ++i) {
        s[i] = 100 * (rand() / (double) (RAND_MAX));
    }
    printf("before sort\n");
    for (int i = 0; i < num; ++i) {
        printf("%.3f\n", s[i]);
//        cout << s[i];
    }
    timeval start{}, end{};
    gettimeofday(&start, nullptr);
    quick_sort(s, 0, num - 1);
    gettimeofday(&end, nullptr);
    printf("after sort\n");
    for (int i = 0; i < num; ++i) {
        printf("%.3f\n", s[i]);
    }
    long time = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("duration time -> %ld ms", time / 1000);
}


char *random_str(int len) {
    char *str = (char *) malloc(sizeof(char) * len);
    for (int i = 0; i < len; ++i) {
        str[i] = digits[rand() % 52];
    }
    return str;
}
