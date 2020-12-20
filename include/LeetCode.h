//
// Created by 87569 on 2020/12/18.
//

#ifndef LEETCODE_LEETCODE_H
#define LEETCODE_LEETCODE_H

#include "vector"
#include "algorithm"
#include "string"
#include "unordered_map"

using namespace std;

/*****************************数组系列****************************************/
/* 350 */
vector<int> intersect(vector<int> &nums1, vector<int> &nums2);

void quick_sort(vector<int> &a, int lo, int hi);

int partition(vector<int> &a, int lo, int hi);

void swap(vector<int> &a, int i, int j);
/************************************************************/

/* 14 */
string longestCommonPrefix(vector<string> &str);
/***********************************************/

/* 122 */
int maxProfit(vector<int> &prices);
/*********************************/

/* 189 */
void rotate(vector<int> &nums, int k);

void reverse(vector<int> &nums, int lo, int hi);
/**********************************************/

/* 27 */
/* 注意，元素顺序可以改变！*/
int removeElement(vector<int> &nums, int val);
/********************************************/

/* 26 */
int removeDuplicates(vector<int> &nums);
/**************************************/

/* 66 */
vector<int> plusOne(vector<int> &digits);
/**************************************/

/* 1 */
vector<int> twoSum(vector<int> &nums, int target);
/**************************************/

/**********************************链表系列**********************************/
/* 19 */
struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    explicit ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *removeNthFromEnd(ListNode *head, int n);
/**************************************/

/* 21 */
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2);
/**************************************/

/* 141 */
bool hasCycle(ListNode *head);
/**************************************/

/* 142 */
ListNode *detectCycle(ListNode *head);
/**************************************/

/***********************************动态规划***********************************/
/* 70 */
int climbStairs(int n);

/* 53 */
int maxSubArray(vector<int> &nums);

/* 300 */
int lengthOfLIS(vector<int> &nums);

/* 120 */
int minimumTotal(vector<vector<int>> &triangle);

/* 64 */
int minPathSum(vector<vector<int>> &grid);

/* 198 */
int rob(vector<int> &nums);

/***********************************字符串系列***********************************/
/* 344 */
void reverseString(vector<char> &s);

/* 387 */
int firstUniqChar(string s);

/***********************************特殊思维***********************************/
/* 231 */
bool isPowerOfTwo(int n);

bool isPowerOfTwo_2(int n);

#endif //LEETCODE_LEETCODE_H
