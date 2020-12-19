//
// Created by 87569 on 2020/12/18.
//

#include "LeetCode.h"
#include "iostream"
#include "sys/time.h"

const int max_n = 1e6;

int main(int argc, char **argv) {
    srand(time(nullptr));
//    vector<int> nums1, nums2;
    timeval start{}, end{};
    auto *head = new ListNode;
    head->val = 1;
    head->next = new ListNode;
    head->next->val = 2;
    head->next->next = head;
    // head->next->next->val = 0;
    // head->next->next->next = new ListNode;
    // head->next->next->next->val = 1;
    // head->next->next->next->next = new ListNode;
    // head->next->next->next->next->val = 4;
    // head->next->next->next->next->next = head->next;
    gettimeofday(&start, nullptr);
    // intersect(nums2, nums2);
//    plusOne(nums1);
    detectCycle(head);
    gettimeofday(&end, nullptr);
    long time = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("duration time -> %ld ms", time / 1000);
}
