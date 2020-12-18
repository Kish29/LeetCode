//
// Created by 87569 on 2020/12/18.
//

#include "LeetCode.h"

vector<int> intersect(vector<int> &nums1, vector<int> &nums2) {
    // sort(nums1.begin(), nums1.end());
    // sort(nums2.begin(), nums2.end());
    quick_sort(nums1, 0, (int) nums1.size() - 1);
    quick_sort(nums2, 0, (int) nums2.size() - 1);
    auto res = vector<int>();
    int i = 0, j = 0;
    while (i < nums1.size() && j < nums2.size()) {
        if (nums1[i] == nums2[j]) {
            res.push_back(nums1[i]);
            i++, j++;
        } else if (nums1[i] < nums2[j]) {
            i++;
        } else j++;
    }
    return res;
}

void quick_sort(vector<int> &a, int lo, int hi) {
    if (hi < lo)
        return;
    int j = partition(a, lo, hi);
    quick_sort(a, lo, j - 1);
    quick_sort(a, j + 1, hi);
}

int partition(vector<int> &a, int lo, int hi) {
    int i = lo, j = hi + 1;
    auto v = a[lo];
    while (true) {
        while (v > a[++i]) if (i == hi) break;
        while (v < a[--j]) if (j == lo) break;
        if (i >= j) break;
        swap(a, i, j);
    }
    swap(a, lo, j);
    return j;
}

inline void swap(vector<int> &a, int i, int j) {
    auto tmp = a[j];
    a[j] = a[i];
    a[i] = tmp;
}

string longestCommonPrefix(vector<string> &str) {
    if (str.empty())
        return "";
    /* 找到最短字串 */
    string tag = str.back();
    str.pop_back();
    int i, k;
    int len1, len2;
    for (const string &s: str) {
        if (s.empty())
            return "";
        i = k = 0;
        len1 = tag.length(), len2 = s.length();
        while (i < len1 && k < len2 && tag[i] == s[k]) {
            i++, k++;
        }
        tag = tag.substr(0, i);
    }
    return tag;
}

int maxProfit(vector<int> &prices) {
    int len = prices.size();
    /* 持有现金 */
    int prev_cash = 0;
    /* 持有股票*/
    int prev_stock = -prices[0];
    for (int i = 1; i < len; ++i) {
        prev_cash = max(prev_cash, prev_stock + prices[i]);
        prev_stock = max(prev_stock, prev_cash - prices[i]);
    }
    return prev_cash;
}

void rotate(vector<int> &nums, int k) {
    int hi = nums.size();
    /* 这个是关键点！！！ */
    k %= hi;
    reverse(nums, 0, hi - 1);
    reverse(nums, 0, k - 1);
    reverse(nums, k, hi - 1);
}

void reverse(vector<int> &nums, int lo, int hi) {
    while (lo < hi) {
        /* 减少空间的交换算法 */
        // nums[lo] ^= nums[hi];
        // nums[hi] ^= nums[lo];
        // nums[lo] ^= nums[hi];
        /* 更快 */
        auto tmp = nums[hi];
        nums[hi] = nums[lo];
        nums[lo] = tmp;
        lo++, hi--;
    }
}

int removeElement(vector<int> &nums, int val) {
    auto p = nums.begin();
    while (p != nums.end()) {
        while (*p == val) {
            /* 注意最后一个元素的边界问题 */
            if (p + 1 == nums.end()) {
                nums.pop_back();
                return nums.size();
            }
            /* 交换最后一个元素 */
            *p = nums.back();
            nums.pop_back();
            if (nums.empty())
                return 0;
        }
        p++;
    }
    return nums.size();
}

/* 注意全部为重复数组的情况 */
/* 使用双指针 */
int removeDuplicates(vector<int> &nums) {
    if (nums.empty())
        return 0;
    int len = nums.size();
    /* 双指针 */
    int p_first = 0, p_second = p_first + 1;
    for (; p_second < len; ++p_second) {
        while (nums[p_first] == nums[p_second] && p_second < len)
            p_second++;
        /* 如果已经到末尾，说明后面全是重复数字 */
        if (p_second == len)
            return p_first + 1;
        nums[++p_first] = nums[p_second];
    }
    return p_first + 1;
}
