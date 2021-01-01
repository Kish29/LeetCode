//
// Created by 87569 on 2020/12/18.
//

#ifndef LEETCODE_LEETCODE_H
#define LEETCODE_LEETCODE_H

#include "vector"
#include "algorithm"
#include "string"
#include "unordered_map"
#include "stack"
#include "queue"
#include "deque"
#include "cstring"

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

/* 128 */
int longestConsecutive(vector<int> &nums);

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

/* 24 */
ListNode *reverseList(ListNode *head);

/***********************************动态规划***********************************/
/* 70 */
int climbStairs(int n);
/**************************************/

/* 53 */
int maxSubArray(vector<int> &nums);

int max_sub_array(vector<int> &nums);
/**************************************/

/* 300 */
int lengthOfLIS(vector<int> &nums);
/**************************************/

/* 120 */
int minimumTotal(vector<vector<int>> &triangle);
/**************************************/

/* 64 */
int minPathSum(vector<vector<int>> &grid);
/**************************************/

/* 198 */
int rob(vector<int> &nums);
/**************************************/


/* 188 */
int maxProfit(int k, vector<int> &prices);

int maxProfit2(vector<int> &prices);


/***********************************字符串系列***********************************/
/* 344 */
void reverseString(vector<char> &s);
/**************************************/

/* 387 */
int firstUniqChar(string s);
/**************************************/

/***********************************二叉树系列***********************************/
/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/* 104 */
int maxDepth(TreeNode *root);
/**************************************/

/* 102 */
vector<vector<int>> levelOrder(TreeNode *root);

vector<vector<int>> dfs(TreeNode *root, int level, vector<vector<int>> &res);

vector<vector<int>> bfs(TreeNode *root);

vector<vector<int>> optimized_bfs(TreeNode *root);
/**************************************/

/* 98 */
bool isValidBST(TreeNode *root);

bool isValidBST_2(TreeNode *root);

bool isValidBST_Inorder(TreeNode *root);

bool isBST(TreeNode *cur, long long min, long long max);

bool isBST_2(TreeNode *cur, long long min, long long max);
/**************************************/

/* 144 */
/* 二叉树的前序遍历非递归，必须掌握！！！ */
vector<int> preorderTraversal(TreeNode *root);
/**************************************/

/* 94 */
/* 二叉树的中序遍历非递归算法，必须掌握！！！ */
vector<int> inorderTraversal(TreeNode *root);
/**************************************/

/* 145 */
/* 二叉树的后序遍历非递归算法，必须掌握！！！ */
vector<int> postorderTraversal(TreeNode *root);
/**************************************/

/* 700 */
TreeNode *searchBST_recursive(TreeNode *root, int val);

TreeNode *searchBST(TreeNode *root, int val);
/**************************************/

/* 450 */
TreeNode *deleteNode(TreeNode *root, int key);

/* 删除二叉查找树右子树的最小节点 */
TreeNode *deleteMinNode(TreeNode *root);

/* 删除二叉查找树左子树的最大节点 */
TreeNode *deleteMaxNode(TreeNode *root);
/**************************************/

/* 110 */
bool isBalanced(TreeNode *root);

int max_depth_copy(TreeNode *root);

int depth_of_tree(TreeNode *root);
/**************************************/

/* 222 */
int countNodes(TreeNode *root);

int complete_or_full_BT_depth(TreeNode *root);
/**************************************/

/* 814 */
/* 非递归算法 */
TreeNode *pruneTree(TreeNode *root);

/* 递归版本 */
TreeNode *pruneTreeRecursive(TreeNode *root);

/**************************************/

/***********************************滑动窗口系列***********************************/
/* 239 */
vector<int> maxSlidingWindow(vector<int> &nums, int k);

/* 3 */
int lengthOfLongestSubstring(string &s);

/***********************************二分查找法***********************************/
int minEatingSpeed(vector<int> &piles, int H);

int speedValid(vector<int> &piles, int speed, int H);


/***********************************排序方法***********************************/

/* 164 */
int maximumGap(vector<int> &nums);

/***********************************特殊思维***********************************/
/* 231 */
bool isPowerOfTwo(int n);

bool isPowerOfTwo_2(int n);
/**************************************/

/* 50 */
double myPow(double x, int n);

/* 优化，快速幂 */
double quick_pow(double x, int n);
/**************************************/

/* 65 */
int add(int a, int b);
/**************************************/

/* tower of hanoi */
void hanota(vector<int> &A, vector<int> &B, vector<int> &C);

void move(int n, vector<int> &A, vector<int> &B, vector<int> &C);

/***********************************面试算法题***********************************/
/* 18 */
ListNode *deleteNode(ListNode *head, int val);

/* 237 */
void deleteNode(ListNode *node);

/* 剑指offer 22 */
ListNode *getKthFromEnd(ListNode *head, int k);

/* 剑指offer 59 - I */
vector<int> maxSlidingWindow2(vector<int> &nums, int k);

/**************************************************************************/

/***********************************每日一题***********************************/
namespace diary_question {

/***********************************1046***********************************/
    class max_heap {

    private:
        int *heap{};
        int heap_len{};
        int index;

        void heap_up() {
            int child = index;
            int parent = (child - 1) / 2;
            int tmp;
            while (child > 0) {
                if (heap[parent] < heap[child]) {
                    tmp = heap[child];
                    heap[child] = heap[parent];
                    heap[parent] = tmp;

                    child = parent;
                    parent = (parent - 1) / 2;
                } else break;
            }
        }

        void heap_down() {
            int parent = 0;
            int child = 2 * parent + 1;
            int tmp;
            while (child <= index) {
                if (child < index && heap[child + 1] > heap[child]) {
                    child++;
                }
                if (heap[parent] < heap[child]) {
                    tmp = heap[child];
                    heap[child] = heap[parent];
                    heap[parent] = tmp;

                    parent = child;
                    child = 2 * child + 1;
                } else break;
            }
        }

    public:
        explicit max_heap(int len) : heap_len(len), heap(new int[len]), index(0) {}

        ~max_heap() {
            delete[] heap;
        }

        int remove_top() {
            if (index <= 0)
                return -1;
            int r_node = heap[0];
            index--;
            heap[0] = heap[index];
            heap_down();
            return r_node;
        }

        void insert(int n) {
            if (index == heap_len) {
                if (n >= heap[0])
                    return;
                remove_top();
            }
            heap[index] = n;
            heap_up();
            index++;
        }

        int size() {
            return this->index;
        }
    };


    class Solution {
    public:
        int lastStoneWeight(vector<int> &stones) {
            if (stones.empty())
                return 0;
            int len = stones.size();
            auto *h = new max_heap(len);
            for (int stone : stones) {
                h->insert(stone);
            }
            int x, y;
            while (h->size()) {
                x = h->remove_top();
                // 如果此时已经空堆
                if (!h->size())
                    return x;
                else {
                    y = h->remove_top();
                    if (x != y)
                        h->insert(x - y);
                }
            }
            return 0;
        }
    };

    /* 435 */
    int eraseOverlapIntervals(vector<vector<int>> &intervals);

    static bool _cmp(vector<int> &a, vector<int> &b);

    /* 605 */
    bool canPlaceFlowers(vector<int>& flowerbed, int n);


/**************************************************************************/


}

#endif //LEETCODE_LEETCODE_H
