//
// Created by 87569 on 2020/12/18.
//

#include "LeetCode.h"
#include "iostream"
#include "sys/time.h"

const int max_n = 1e6;

const string s = "0123456789abcdefghijklmnopqrstuvwxyz";
const int s_len = s.size();

int main(int argc, char **argv) {
    srand(time(nullptr));
    vector<int> nums1, nums2;

    vector<char> chars;
    int num;
    for (int i = 0; i < 1e7; ++i) {
        chars.push_back(s[rand() % s_len]);
    }

    timeval start{}, end{};
    gettimeofday(&start, nullptr);
    // intersect(nums2, nums2);
//    plusOne(nums1);
//    detectCycle(head);
//    lengthOfLIS(nums1);
//    rob(nums1);
    reverseString(chars);
    gettimeofday(&end, nullptr);
    long time = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("duration time -> %ld ms", time / 1000);
}
