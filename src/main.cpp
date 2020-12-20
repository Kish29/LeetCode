//
// Created by 87569 on 2020/12/18.
//

#include "LeetCode.h"
#include "iostream"
#include "sys/time.h"

const int max_n = 1e6;

int main(int argc, char **argv) {
    srand(time(nullptr));
    vector<int> nums1, nums2;

    int num;
    for (int i = 0; i < 6; ++i) {
        cin >> num;
        nums1.push_back(num);
    }

    timeval start{}, end{};
    gettimeofday(&start, nullptr);
    // intersect(nums2, nums2);
//    plusOne(nums1);
//    detectCycle(head);
    lengthOfLIS(nums1);
    gettimeofday(&end, nullptr);
    long time = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("duration time -> %ld ms", time / 1000);
}
