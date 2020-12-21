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
    // vector<int> nums1, nums2;

    // vector<char> chars;
    // int num;
    // for (int i = 0; i < 1e7; ++i) {
    //     chars.push_back(s[rand() % s_len]);
    // }
    auto *root = new TreeNode;
    root->val = 1;
    root->left = new TreeNode;
    root->left->val = 2;
    root->right = new TreeNode;
    root->right->val = 3;
    root->left->left = new TreeNode;
    root->left->left->val = 4;
    root->left->right = new TreeNode;
    root->left->right->val = 5;

    timeval start{}, end{};
    gettimeofday(&start, nullptr);
    // intersect(nums2, nums2);
//    plusOne(nums1);
//    detectCycle(head);
//    lengthOfLIS(nums1);
//    rob(nums1);
//    reverseString(chars);
    levelOrder(root);
    gettimeofday(&end, nullptr);
    long time = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("duration time -> %ld ms", time / 1000);
}
