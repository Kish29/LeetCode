//
// Created by 87569 on 2020/12/18.
//

#ifndef LEETCODE_LEETCODE_H
#define LEETCODE_LEETCODE_H

#include "vector"
#include "algorithm"
#include "string"

using namespace std;

/* 350 */
vector<int> intersect(vector<int> &nums1, vector<int> &nums2);

void quick_sort(vector<int> &a, int lo, int hi);

int partition(vector<int> &a, int lo, int hi);

void swap(vector<int> &a, int i, int j);
/********************************************************/

/* 14 */
string longestCommonPrefix(vector<string> &str);

/* 122 */
int maxProfit(vector<int> &prices);

/* 189 */
void rotate(vector<int> &nums, int k);

void reverse(vector<int> &nums, int lo, int hi);

/* 27 */
/* 注意，元素顺序可以改变！*/
int removeElement(vector<int> &nums, int val);

/* 26 */
int removeDuplicates(vector<int>& nums);

#endif //LEETCODE_LEETCODE_H
