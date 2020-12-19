//
// Created by 87569 on 2020/12/18.
//

#include "LeetCode.h"

/* 求两个数组的交集
 * 最优的办法：
 * 1->使用最快的排序方法(如果不保证稳定性使用快排，否则插入排序)将两个数组排序
 * 2->使用双指针
 * */
vector<int> intersect(vector<int> &nums1, vector<int> &nums2) {
    if (nums1.empty())
        return nums2;
    if (nums2.empty())
        return nums1;
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
    /* 小于等于！！！ */
    if (hi <= lo)
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

/* 使用双循环 */
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

/* 动态规划
 * 定义两个状态 dp[i][0]和dp[i][1]
 * 分别表示第i天持有现金
 * 第i天持有股票 */
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

/* 反转整个数组，再按照0~k反转两个子数组 */
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

/* O(1)的数组删除
 * 通过要删除的元素不断与最后一个元素交换删除完成 */
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
        /* 请注意，在数组的访问中，此种访问最容易发生数组的越界访问，必须把数组的边界判断放在最前面！ */
        while (p_second < len && nums[p_first] == nums[p_second])
            p_second++;
        /* 如果已经到末尾，说明后面全是重复数字 */
        if (p_second == len)
            return p_first + 1;
        nums[++p_first] = nums[p_second];
    }
    return p_first + 1;
}

vector<int> plusOne(vector<int> &digits) {
    /* 空数组情况 */
    if (digits.empty())
        return digits;
    int len = digits.size();
    /* 考虑99这种数组情况 */
    vector<int> res;
    /* 进位保留位，因为从末位加1，所以初始化为1
     * 1表示普通进位
     * 2表示需要拓展额外数组 */
    int carry = 1;
    /* 从后往前遍历 */
    for (int i = len - 1; i >= 0; i--) {
        if (digits[i] + carry >= 0xa) {
            /* 别忘了处理进位后本位的值 */
            digits[i] = digits[i] + carry - 0xa;
            if (i == 0)
                carry = 2;
            else
                carry = 1;
        } else {
            digits[i] += carry;
            return digits;
        }
    }
    if (carry == 2) {
        res.push_back(1);
        res.insert(res.end(), digits.begin(), digits.end());
    }
    return res;
}

/* 使用hash表 */
vector<int> twoSum(vector<int> &nums, int target) {
    if (nums.empty())
        return nums;
    auto hash_map = unordered_map<int, int>();
    auto p = nums.begin();
    vector<int> res;
    int i = 0;
    while (p != nums.end()) {
        if (hash_map.find(target - *p) != hash_map.end()) {
            res.push_back(hash_map[target - *p]);
            res.push_back(i);
        } else hash_map[*p] = i;
        p++;
        i++;
    }
    return res;
}

/* 使用双指针间隔删除
 * 需要一个d_node_prev记录待删除节点的上一个 */
ListNode *removeNthFromEnd(ListNode *head, int n) {
    if (head == nullptr)
        return nullptr;
    /* 设置哨兵节点 */
    auto *p_senitel = new ListNode;
    p_senitel->next = head;

    /* 待删除节点 */
    auto *d_node = head;
    /* 待删除节点上一个节点 */
    auto *d_node_prev = p_senitel;
    /* 指示指针 */
    auto *p_second = head;

    /* 注意只有一个元素的情况 */
    /* 计数器 */
    int i = 0;
    while (p_second != nullptr) {
        /* 第二个指针先走n 步
         * 即两个指针间隔n 个值 */
        if (i < n) {
            p_second = p_second->next;
            i++;
            continue;
        }
        /* 同时移动 */
        d_node_prev = d_node_prev->next;
        d_node = d_node->next;
        p_second = p_second->next;
    }
    /* 走到末尾了 */
    d_node_prev->next = d_node_prev->next->next;
    return p_senitel->next;
}

/* 使用哨兵节点
 * 它的下一个节点是两个数组的偏小的节点 */
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    /* 首先考虑其中一个为空的情况 */
    if (l1 == nullptr || l2 == nullptr)
        return l1 == nullptr ? l2 : l1;
    auto *p_senitel = new ListNode;
    auto *cur = p_senitel;
    /* p_senitel 每次更新二者较小的节点 */
    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val < l2->val) {
            cur->next = l1;
            l1 = l1->next;
        } else {
            cur->next = l2;
            l2 = l2->next;
        }
        /* 不要忘记更新节点 */
        cur = cur->next;
    }
    /* 判断两个链表的空状况 */
    if (l1 == nullptr)
        cur->next = l2;
    else
        cur->next = l1;
    return p_senitel->next;
}

/* 使用快慢双指针 */
bool hasCycle(ListNode *head) {
    if (head == nullptr)
        return false;
    auto *p_slow = head;
    auto *p_fast = head;
    /* 两种情况
     * 1种相遇
     * 另一种就是走到空指针 */
    while (p_slow != nullptr && p_fast != nullptr) {
        /* 先移动，后判断 */
        if (p_fast->next != nullptr) {
            p_slow = p_slow->next;
            p_fast = p_fast->next->next;
        } else return false;
        if (p_slow == p_fast)
            return true;
    }
    return false;
}

/* 相遇节点和头节点同时再走i步，一定会相遇 */
ListNode *detectCycle(ListNode *head) {
    if (head == nullptr)
        return nullptr;
    auto *p_slow = head;
    auto *p_fast = head;
    /* 目标节点 */
    auto *target = head;
    /* 相遇节点 */
    auto *encounter_node = new ListNode;
    /* 相遇节点和头节点的移动的标志 */
    bool flag = false;
    while (p_slow != nullptr && p_fast != nullptr) {
        if (flag) {
            /* 先判断！！！ */
            if (target == encounter_node) {
                return target;
            }
            target = target->next;
            encounter_node = encounter_node->next;
            continue;
        }
        /* 快慢指针移动 */
        if (p_fast->next != nullptr) {
            p_slow = p_slow->next;
            p_fast = p_fast->next->next;
        } else {
            return nullptr;
        }
        if (p_slow == p_fast) {
            encounter_node = p_slow;
            flag = true;
            continue;
        }
    }
    return nullptr;
}
