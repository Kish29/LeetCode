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
    auto *p_sentinel = new ListNode;
    p_sentinel->next = head;

    /* 待删除节点 */
    auto *d_node = head;
    /* 待删除节点上一个节点 */
    auto *d_node_prev = p_sentinel;
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
    return p_sentinel->next;
}

/* 使用哨兵节点
 * cur下一个节点是两个数组的偏小的节点 */
ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    /* 首先考虑其中一个为空的情况 */
    if (l1 == nullptr || l2 == nullptr)
        return l1 == nullptr ? l2 : l1;
    auto *p_sentinel = new ListNode;
    auto *cur = p_sentinel;
    /* p_sentinel 每次更新二者较小的节点 */
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
    return p_sentinel->next;
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

int climbStairs(int n) {
    if (n <= 2)
        return n;
    int *dp = new int[n + 1];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; ++i) {
        /* 分别对应走到该阶楼梯
         * 走1步和走2步的情况 */
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

/* 使用dp[i]表示数组以i号结尾的最大数组和 */
int maxSubArray(vector<int> &nums) {
    if (nums.empty())
        return 0;
    int len = nums.size();
    /* 只有一个元素的情况 */
    if (len == 1)
        return nums[0];
    int *dp = new int[len];
    dp[0] = nums[0];
    /* 维护最大值 */
    int res = dp[0];
    res = max(dp[0], res);
    for (int i = 1; i < len; ++i) {
        dp[i] = nums[i];
        dp[i] = max(dp[i - 1] + nums[i], dp[i]);
        res = max(dp[i], res);
    }
    /* 防止内存泄露 */
    delete[] dp;
    dp = nullptr;
    return res;
}

int max_sub_array(vector<int> &nums) {
    if (nums.empty())
        return 0;
    int len = nums.size();
    int cur_sum = nums[0];
    int res = cur_sum;
    for (int i = 1; i < len; ++i) {
        if (cur_sum < 0)
            cur_sum = nums[i];
        else
            cur_sum += nums[i];
        if (res < cur_sum)
            res = cur_sum;
    }
    return res;
}

/* 该方法适用于连续的递增子数列求解 */
/* 同理，用一个dp[i]表示以i号结尾的最长上升子序列的长度 */
// int lengthOfLIS(vector<int> &nums) {
//     if (nums.empty())
//         return 0;
//     if (nums.size() == 1)
//         return 1;
//     int len = nums.size();
//     int *dp = new int[len];
//     dp[0] = 1;
//     /* 维护一个最大长度 */
//     int res = dp[0];
//     for (int i = 1; i < len; ++i) {
//         dp[i] = 1;
//         if (nums[i] > nums[i - 1]) {
//             dp[i] = max(dp[i - 1] + 1, dp[i]);
//             res = max(res, dp[i]);
//         }
//     }
//     return res;
// }

/* 二重循环
 * 时间复杂度为O(n2)*/
// int lengthOfLIS(vector<int> &nums) {
//     if (nums.empty())
//         return 0;
//     if (nums.size() == 1)
//         return 1;
//     int len = nums.size();
//     int *dp = new int[len];
//     /* 维护最大值 */
//     int res = 0;
//     for (int i = 0; i < len; ++i) {
//         /* 注意需要遍历前面的所有数字，并且对nums[j]进行分析 */
//         dp[i] = 1;
//         for (int j = 0; j < i; ++j) {
//             if (nums[j] < nums[i]) {
//                 dp[i] = max(dp[i], dp[j] + 1);
//             }
//         }
//         res = max(res, dp[i]);
//     }
//     return res;
// }

/* 二分查找算法
 * 维护一个上升的序列
 * 通过二分查找找到合适的位置将比nums[i]小的数进行替换
 * 该替换始终替换右边的数
 * 如果nums[i]比上升子序列的最大值大，直接插入即可 */
int lengthOfLIS(vector<int> &nums) {
    if (nums.empty())
        return 0;
    if (nums.size() == 1)
        return 1;
    vector<int> inc_sequence;
    inc_sequence.push_back(nums[0]);
    int left, mid, right;
    int len = nums.size();
    for (int i = 1; i < len; ++i) {
        if (nums[i] > inc_sequence.back()) {
            inc_sequence.push_back(nums[i]);
        } else {
            left = 0, right = (int) inc_sequence.size() - 1;
            /* 二分查找合适的替换位置 */
            while (left < right) {
                mid = (left + right) >> 1;
                if (nums[i] > inc_sequence[mid])
                    left = mid + 1;
                else right = mid;
            }
            inc_sequence[left] = nums[i];
        }
    }
    return inc_sequence.size();
}

/* 方法一，累加第0位 */
bool isPowerOfTwo(int n) {
    if (n < 0)
        return false;
    int bits_len = sizeof(int) * 8;
    int num_of_1 = 0;
    for (int i = 0; i < bits_len; ++i) {
        num_of_1 += (n & 0x00000001);
        n >>= 1;
    }
    return num_of_1 == 1;
}

/* 二者速度在快速的CPU上几乎相同 */

/* 方法二，利用2的幂次方的数的特性 */
bool isPowerOfTwo_2(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

/* 从最下层到最上层进行动态规划求解 */
int minimumTotal(vector<vector<int>> &triangle) {
    if (triangle.empty())
        return 0;
    /* 保存每一层最小值的一维数组，长度为第i层三角树的长度 */
    /* 初始化 */
    vector<int> dp;
    int len = triangle.size();
    dp.insert(dp.end(), triangle[len - 1].begin(), triangle[len - 1].end());
    /* 从倒数第2层开始 */
    int sub_len;
    for (int i = len - 2; i >= 0; i--) {
        sub_len = triangle[i].size();
        for (int j = 0; j < sub_len; ++j) {
            dp[j] = min(triangle[i][j] + dp[j], triangle[i][j] + dp[j + 1]);
        }
    }
    return dp[0];
}

/* 遍历一次二维数组，每次更新最小值 */
int minPathSum(vector<vector<int>> &grid) {
    if (grid.empty())
        return 0;
    int len = grid.size();
    int sub_len;
    for (int i = 0; i < len; ++i) {
        sub_len = grid[i].size();
        for (int j = 0; j < sub_len; ++j) {
            if (j == 0) {   // 表示第0个数字，只能从上面下来，
                if (i > 0) // 不是最左上角数字
                    grid[i][j] += grid[i - 1][j];
            } else {
                if (i > 0)  // 不是第一行数字
                    grid[i][j] = min(grid[i - 1][j] + grid[i][j], grid[i][j - 1] + grid[i][j]);
                else
                    grid[i][j] += grid[i][j - 1];
            }
        }
    }
    return grid[len - 1][sub_len - 1];
}

// int rob(vector<int> &nums) {
//     if (nums.empty())
//         return 0;
//     /* 为防止下标越界，尽心严格检查 */
//     /* 只有一个元素的情况 */
//     if (nums.size() == 1)
//         return nums[0];
//     /* 两个元素 */
//     if (nums.size() == 2)
//         return max(nums[0], nums[1]);
//     int len = nums.size();
//     int *dp = new int[len];
//     dp[0] = nums[0];
//     /* 注意这个地方 */
//     dp[1] = max(nums[0], nums[1]);
//     for (int i = 2; i < len; ++i) {
//         dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
//     }
//     return dp[len - 1];
// }

/* 压缩一下空间 */
int rob(vector<int> &nums) {
    if (nums.empty())
        return 0;
    /* 为防止下标越界，尽心严格检查 */
    /* 只有一个元素的情况 */
    if (nums.size() == 1)
        return nums[0];
    /* 两个元素 */
    if (nums.size() == 2)
        return max(nums[0], nums[1]);
    int len = nums.size();
    /* 注意这个地方 */
    nums[1] = max(nums[0], nums[1]);
    for (int i = 2; i < len; ++i) {
        nums[i] = max(nums[i - 1], nums[i - 2] + nums[i]);
    }
    return nums[len - 1];
}

void reverseString(vector<char> &s) {
    if (s.empty())
        return;
    int left = 0, right = (int) s.size() - 1;
    char tmp;
    while (left < right) {
        /*s[left] ^= s[right];
        s[right] ^= s[left];
        s[left] ^= s[right];*/
        tmp = s[right];
        s[right] = s[left];
        s[left] = tmp;
        left++, right--;
    }
}

/* 垃圾算法 */
// int firstUniqChar(string s) {
//     if (s.empty())
//         return -1;
//     int len = s.length();
//     auto hash = unordered_map<int, int>();
//     for (int i = 0; i < len; ++i) {
//         if (hash.find(s[i] - '0') != hash.end()) {
//             hash[s[i - '0']]++;
//         } else
//             hash[s[i] - '0'] = 1;
//     }
//     for (int i = 0; i < len; ++i) {
//         if (hash[s[i] - '0'] == 1)
//             return -1;
//     }
//     return -1;
// }

/* 优化算法
 * 总的来说，核心思想是遍历两遍字符串，找到第一个次数为1的
 * 返回下标 */
int firstUniqChar(string s) {
    /* 统计每个字符出现的次数 */
    /* 如果是只有英文字符，数组还可以开得更小，26个 */
    int count[256] = {0};
    int len = s.length();
    for (int i = 0; i < len; ++i) {
        count[s[i]]++;
    }
    for (int i = 0; i < len; ++i) {
        if (count[s[i]] == 1)
            return i;
    }
    return -1;
}


/* DFS递归算法，不建议 */
// int maxDepth(TreeNode *root) {
//     if (root == nullptr)
//         return 0;
//     return max(maxDepth(root->left), maxDepth(root->right)) + 1;
// }

/* DFS用栈转化非递归 */
/* 非递归解法，利用两个栈，同时记录节点和曾数 */
int maxDepth(TreeNode *root) {
    /* 空指针判断 */
    if (root == nullptr)
        return 0;
    stack<TreeNode *> t_stack;
    stack<int> level;
    /* 记录当前层数 */
    int cur_level = 1;
    /* 维护最大深度 */
    int max_depth = 0;
    /* 二者同时入栈 */
    t_stack.push(root);
    level.push(cur_level);
    /* 进行DFS */
    TreeNode *p_node;
    while (!t_stack.empty()) {
        /* 同时出栈 */
        p_node = t_stack.top();
        cur_level = level.top();
        t_stack.pop(), level.pop();
        /* 更新最大深度 */
        max_depth = max(max_depth, cur_level);
        /* 先压右子树（前序遍历） */
        if (p_node->right != nullptr) {
            t_stack.push(p_node->right);
            level.push(cur_level + 1);
        }
        if (p_node->left != nullptr) {
            t_stack.push(p_node->left);
            level.push(cur_level + 1);
        }
    }
    return max_depth;
}

/* DFS递归解法 */
vector<vector<int>> levelOrder(TreeNode *root) {
    vector<vector<int>> res;
//    return dfs(root, 0, res);
    return bfs(root);
}

vector<vector<int>> dfs(TreeNode *root, int level, vector<vector<int>> &res) {
    if (root == nullptr)
        return res;
    /* 首先需要进行层数判断 */
    if (res.size() == level) {   // 说明还没有添加本层节点
        vector<int> cur_level;
        cur_level.push_back(root->val);
        res.push_back(cur_level);
    } else {
        res[level].push_back(root->val);
    }
    res = dfs(root->left, level + 1, res);
    res = dfs(root->right, level + 1, res);
    return res;
}

/* BFS解法 */
/* BFS用递归转化非递归 */
vector<vector<int>> bfs(TreeNode *root) {
    vector<vector<int>> res;
    if (root == nullptr)
        return res;
    /* 记录层数 */
    queue<int> levels;
    int tmp;
    queue<TreeNode *> t_queue;
    t_queue.push(root);
    levels.push(0);

    /* BFS遍历 */
    TreeNode *p_node;
    while (!t_queue.empty()) {
        /* 取队列第一个元素 */
        p_node = t_queue.front();
        t_queue.pop();
        tmp = levels.front();
        if (res.size() == tmp) { //说明还没有创建本层遍历结果
            levels.pop();
            vector<int> cur_level;
            cur_level.push_back(p_node->val);
            res.push_back(cur_level);
        } else {
            res[tmp].push_back(p_node->val);
            levels.pop();
        }
        if (p_node->left != nullptr) {
            t_queue.push(p_node->left);
            levels.push(tmp + 1);
        }
        if (p_node->right != nullptr) {
            t_queue.push(p_node->right);
            levels.push(tmp + 1);
        }
    }
    return res;
}

/* 优化BFS算法 */
vector<vector<int>> optimized_bfs(TreeNode *root) {
    vector<vector<int>> res;
    if (root == nullptr)
        return res;
    queue<TreeNode *> t_queue;
    t_queue.push(root);
    int cur_level_size;
    TreeNode *p_node;
    while (!t_queue.empty()) {
        cur_level_size = t_queue.size();
        /* 新建一个空vector*/
        res.emplace_back();
        for (int i = 0; i < cur_level_size; ++i) {
            p_node = t_queue.front();
            res.back().push_back(p_node->val);
            t_queue.pop();
            /* 必须在这里插入队列中 */
            if (p_node->left != nullptr) {
                t_queue.push(p_node->left);
            }
            if (p_node->right != nullptr) {
                t_queue.push(p_node->right);
            }
        }
    }
    return res;
}

/* DFS递归搜索 */
/* 注意重点，对于每个节点
 * 我们必须传递给左子树当前最大值
 * 右子树当前最小值 */
bool isValidBST(TreeNode *root) {
    return isBST(root, INT64_MIN, INT64_MAX);
}

bool isBST(TreeNode *cur, long long min, long long max) {
    if (cur == nullptr)
        return true;
    /* 对于左子树，如果给出的最大值小于了当前的数，说明左子树包含一个数大于之前的父节点的值
     * 同理，对于右子树，如果给出的最小值大于了当前正在遍历的数节点，说明右子树包含一个数小于之前的父节点的值 */
    if (min >= cur->val || max <= cur->val)
        return false;
    return isBST(cur->left, min, cur->val) && isBST(cur->right, cur->val, max);
}

/* DFS递归搜索 */
/* 注意重点，对于每个节点
 * 我们必须传递给左子树当前最大值
 * 右子树当前最小值 */
bool isValidBST_2(TreeNode *root) {
    return isBST_2(root, INT64_MAX, INT64_MIN);
}

bool isBST_2(TreeNode *cur, long long min, long long max) {
    if (cur == nullptr)
        return true;
    /* 或者换一种思维，如果当前值大于了给出的最小值或者小于了给出的最大值，不满足要求 */
    if (cur->val >= min || cur->val <= max)
        return false;
    return isBST_2(cur->left, cur->val, max) && isBST_2(cur->right, min, cur->val);
}

/* 栈的非递归中序遍历
 * 中序遍历为升序！！！ */
bool isValidBST_Inorder(TreeNode *root) {
    stack<TreeNode *> t_stack;
    long long prev_val = INT64_MIN;
    while (!t_stack.empty() || root != nullptr) {
        /* 压入左节点 */
        while (root != nullptr) {
            t_stack.push(root);
            root = root->left;
        }
        /* 取出栈顶 */
        root = t_stack.top();
        t_stack.pop();
        if (root->val <= prev_val)
            return false;
        /* 更新最小值 */
        prev_val = root->val;
        /* 检查右节点 */
        root = root->right;
    }
    return true;
}

/* 前序遍历非递归解法 */
vector<int> preorderTraversal(TreeNode *root) {
    vector<int> res;
    if (root == nullptr)
        return res;
    stack<TreeNode *> t_stack;
    t_stack.push(root);
    while (!t_stack.empty()) {
        root = t_stack.top();
        t_stack.pop();
        res.push_back(root->val);
        /* 右子树先进栈 */
        if (root->right) {
            t_stack.push(root->right);
        }
        if (root->left) {
            t_stack.push(root->left);
        }
    }
    return res;
}

/* 中序遍历非递归解法 */
vector<int> inorderTraversal(TreeNode *root) {
    vector<int> res;
    stack<TreeNode *> t_stack;
    while (!t_stack.empty() || root) {
        /* 所有左子树进栈 */
        while (root) {
            t_stack.push(root);
            root = root->left;
        }
        /* 取出栈顶节点 */
        root = t_stack.top();
        t_stack.pop();
        res.push_back(root->val);
        /* 检查右子树 */
        root = root->right;
    }
    return res;
}

TreeNode *searchBST_recursive(TreeNode *root, int val) {
    if (root == nullptr)
        return nullptr;
    if (val == root->val)
        return root;
    if (val > root->val)
        return searchBST_recursive(root->right, val);
    else
        return searchBST_recursive(root->left, val);
    return nullptr;
}

TreeNode *searchBST(TreeNode *root, int val) {
    while (root != nullptr) {
        if (val == root->val)
            return root;
        if (val > root->val)
            root = root->right;
        else root = root->left;
    }
    return root;
}

/* 后续遍历的巧妙思路，用nullptr作为二次访问标志 */
vector<int> postorderTraversal(TreeNode *root) {
    vector<int> res;
    if (root == nullptr)
        return res;
    stack<TreeNode *> t_stack;
    t_stack.push(root);
    while (!t_stack.empty()) {
        root = t_stack.top();
        t_stack.pop();
        if (root != nullptr) {
            t_stack.push(root);
            /* 压入标志nullptr */
            t_stack.push(nullptr);
            if (root->right)
                t_stack.push(root->right);
            if (root->left)
                t_stack.push(root->left);
        } else {
            root = t_stack.top();
            t_stack.pop();
            res.push_back(root->val);
        }
    }
    return res;
}

/* 优秀！！！哈哈哈！！！ */
/* 优秀你麻痹，都野指针了，还尼玛优秀，傻逼 */
TreeNode *deleteNode(TreeNode *root, int key) {
    if (root == nullptr)
        return nullptr;
    /* 左子树查找 */
    if (key < root->val) {
        root->left = deleteNode(root->left, key);
        return root;
    }
    /* 右子树查找 */
    if (key > root->val) {
        root->right = deleteNode(root->right, key);
        return root;
    }
    /* 此时已经找到了，隐含 key == root->val 的条件 */
    /* 防止内存溢出 */
    TreeNode *tmp;
    /* 左子树为空 */
    if (root->left == nullptr) {
        tmp = root;
        root = root->right;
        delete tmp;
        /* 注意野指针     */
        tmp = nullptr;
        return root;
    }
    /* 右子树为空 */
    if (root->right == nullptr) {
        tmp = root;
        root = root->left;
        delete tmp;
        tmp = nullptr;
        return root;
    }
    /* 左右子树均不为空 */
    /* 查找后继节点 */
    // auto *scs_node = root->right;
    // while (scs_node->left) {
    //     scs_node = scs_node->left;
    // }
    // /* 赋值 */
    // root->val = scs_node->val;
    // /* 从右子树中删除最小的后继节点 */
    // root->right = deleteMinNode(root->right);


    /* 查找前驱节点 */
    auto *prcs_node = root->left;
    while (prcs_node->right) {
        prcs_node = prcs_node->right;
    }
    /* 赋值 */
    root->val = prcs_node->val;
    /* 从左子树中删除最大的前驱节点 */
    root->left = deleteMaxNode(root->left);
    return root;
}

TreeNode *deleteMinNode(TreeNode *root) {
    if (root == nullptr)
        return nullptr;
    /* 不存在左子树的情况 */
    if (root->left == nullptr) {
        /* 删除自身节点 */
        auto *tmp = root;
        root = root->right;
        delete tmp;
        return root;
    }
    root->left = deleteMinNode(root->left);
    return root;
}

/* 从左子树中删除最大前驱节点 */
TreeNode *deleteMaxNode(TreeNode *root) {
    if (root == nullptr)
        return nullptr;
    /* 不存在右子树 */
    if (root->right == nullptr) {
        auto *tmp = root;
        root = root->left;
        delete tmp;
        return root;
    }
    root->right = deleteMaxNode(root->right);
    return root;
}

bool isBalanced(TreeNode *root) {
    /* 空树 */
    if (root == nullptr) {
        return true;
    }
    int gap = depth_of_tree(root->left) - depth_of_tree(root->right);
    if (gap < -1 || gap > 1)
        return false;
    return isBalanced(root->left) && isBalanced(root->right);
}


/* DFS遍历 */
int max_depth_copy(TreeNode *root) {
    if (root == nullptr)
        return 0;
    stack<TreeNode *> t_stack;
    stack<int> levels;
    /* 同时入栈 */
    int cur_level = 1;
    t_stack.push(root);
    levels.push(cur_level);
    /* 维护最大值 */
    int max_depth = 0;
    TreeNode *p_node;
    while (!t_stack.empty()) {
        p_node = t_stack.top();
        cur_level = levels.top();
        t_stack.pop();
        levels.pop();
        max_depth = max(max_depth, cur_level);
        if (p_node->right) {
            t_stack.push(p_node->right);
            levels.push(cur_level + 1);
        }
        if (p_node->left) {
            t_stack.push(p_node->left);
            levels.push(cur_level + 1);
        }
    }
    return max_depth;
}

/* 查找一棵树的最大深度 */
int depth_of_tree(TreeNode *root) {
    if (root == nullptr)
        return 0;
    int left_depth = depth_of_tree(root->left) + 1;
    int right_depth = depth_of_tree(root->right) + 1;
    return max(left_depth, right_depth);
}

/* 满二叉树节点个数m和高度h的关系
 * m = 2^h - 1*/
int countNodes(TreeNode *root) {
    /* 空结点 */
    if (root == nullptr)
        return 0;
    int left_depth = complete_or_full_BT_depth(root->left);
    int right_depth = complete_or_full_BT_depth(root->right);
    if (left_depth == right_depth) {    // 此时左子树一定是满二叉树
        return countNodes(root->right) + (1 << left_depth);
    } else {
        return countNodes(root->left) + (1 << right_depth);
    }
}

int complete_or_full_BT_depth(TreeNode *root) {
    if (root == nullptr)
        return 0;
    int depth = 1;
    while (root->left) {    // 完全二叉树或者满二叉树可以通过该方式计算
        depth++;
        root = root->left;
    }
    return depth;
}

/* 使用后序遍历算法即可 */
TreeNode *pruneTree(TreeNode *root) {
    if (root == nullptr)
        return root;
    stack<TreeNode *> t_stack;
    t_stack.push(root);
    while (!t_stack.empty()) {
        root = t_stack.top();
        t_stack.pop();
        if (root) {
            /* 再次入栈，并压入标志位 */
            t_stack.push(root);
            t_stack.push(nullptr);
            if (root->right)
                t_stack.push(root->right);
            if (root->left)
                t_stack.push(root->left);
        } else {
            root = t_stack.top();
            t_stack.pop();
            /* 由于程序的结构问题，要先进行剪枝！！！ */
            /* 查找已被剪枝的，并将其移除置为空指针 */
            if (root->left && root->left->val == -1) {
                delete root->left;
                root->left = nullptr;
            }
            if (root->right && root->right->val == -1) {
                delete root->right;
                root->right = nullptr;
            }
            if (root->val == 0 && root->left == nullptr && root->right == nullptr) {   // 用-1表示已被剪枝
                // 注意，由于压栈的是另外的复制指针，所以不能通过这两条语句进行剪枝
                /*delete root;
                root = nullptr;*/
                root->val = -1;
            }
        }
    }
    /* 最后检查root根节点是否被剪枝 */
    return root->val == -1 ? nullptr : root;
}

TreeNode *pruneTreeRecursive(TreeNode *root) {
    if (root == nullptr)
        return nullptr;
    root->left = pruneTreeRecursive(root->left);
    root->right = pruneTreeRecursive(root->right);
    if (root->val == 0 && !root->left && !root->right)
        return nullptr;
    return root;
}

vector<int> maxSlidingWindow(vector<int> &nums, int k) {
    vector<int> res;
    if (nums.empty())
        return res;
    /* 使用双端队列保存最大值下标 */
    deque<int> max_index;
    int len = nums.size();
    for (int i = 0; i < len; ++i) {
        /* 保证滑动窗口合法性 */
        if (!max_index.empty() && max_index.front() == i - k) {
            max_index.pop_front();
        }
        /* 维护最大值
         * 该方式能保证队列末尾元素是最小元素 */
        while (!max_index.empty() && nums[max_index.back()] < nums[i]) {
            max_index.pop_back();
        }
        /* 压入本次下标 */
        max_index.push_back(i);
        /* 压入最大值 */
        if (i >= k - 1) {
            res.push_back(nums[max_index.front()]);
        }
    }
    return res;
}


/* 使用first和second构成滑动窗口 */
int lengthOfLongestSubstring(string &s) {
    /* 使用hash数组保存下标 */
    int hash_index[256];
    /* 数组初始化为- 1 */
    memset(hash_index, -1, 256 * sizeof(int));
    int len = s.length();
    int first = 0;
    /* 维护一个最大值 */
    int res = 0;
    int second;
    for (second = 0; second < len; ++second) {
        /* 如果该字母在之前出现过，并且出现的位置在first后面，让cursor重新移动位置 */
        if (hash_index[s[second]] != -1 && hash_index[s[second]] >= first) {
            /* 更新max值 */
            if (second - first > res)
                res = second - first;
            /* 更新cursor，移到出现的下一个元素 */
            first = hash_index[s[second]] + 1;
        }
        /* 插入下标 */
        hash_index[s[second]] = second;
    }
    if (res > second - first)
        return res;
    return second - first;
}

double myPow(double x, int n) {
    if (x == 0 || x == 1)
        return x;
    if (x == -1) {
        if (n % 2 == 0)
            return 1;
        return -1;
    }
    if (n == 0)
        return 1;
    if (n == INT32_MIN || n == INT32_MAX)
        return 0;
    double org = x;
    for (int i = 1; i < abs(n); ++i) {
        x *= org;
    }
    if (n < 0)
        return 1 / x;
    return x;
}

double quick_pow(double x, int n) {
    /* x的特殊边界 */
    if (x == 0 || x == 1)
        return x;
    if (x == -1) {
        if (n % 2 == 0)
            return 1;
        return -1;
    }
    /* n的特殊边界 */
    if (n == 0)
        return 1;
    if (n == INT32_MAX || n == INT32_MIN)
        return 0;
    double res = 1;
    if (n < 0) {
        x = 1 / x;
        n = -n;
    }
    while (n) {
        if (n & 1)
            res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}

int add(int a, int b) {
    return 0;
}

ListNode *reverseList(ListNode *head) {
    if (head == nullptr)
        return nullptr;
    auto *second = head->next;
    /* 先置空
     * 避免两个节点循环 */
    head->next = nullptr;
    ListNode *third;
    while (second) {
        third = second->next;
        second->next = head;
        /* 先移动head */
        head = second;
        second = third;
    }
    return head;
}

void hanota(vector<int> &A, vector<int> &B, vector<int> &C) {
    if (A.empty())
        return;
    int n = A.size();
    move(n, A, B, C);
}

void move(int n, vector<int> &A, vector<int> &B, vector<int> &C) {
    if (n == 1) {
        C.push_back(A.back());
        A.pop_back();
        return;
    }
    move(n - 1, A, C, B);       //最上面n-1个移动到B
    C.push_back(A.back());
    A.pop_back();
    move(n - 1, B, A, C);       // B的n-1个移动到C
}

int maxProfit(int k, vector<int> &prices) {
    vector<int> cash(k + 1, 0);
    vector<int> stock(k + 1, INT_MIN);
    int i;
    for (int &price : prices) {
        for (i = 1; i <= k; i++) {
            stock[i] = max(stock[i], cash[i - 1] - price);
            cash[i] = max(cash[i], stock[i] + price);
        }
    }
    return cash[k];
}

int maxProfit2(vector<int> &prices) {
    /* 同188 */
    return 0;
}

int longestConsecutive(vector<int> &nums) {
    // 空数组情况
    if (nums.empty())
        return 0;
    // hash表
    // 遍历一遍，求出最大值和最小值
    int min_ele = INT_MAX, max_ele = INT_MIN;
    for (int &num : nums) {
        min_ele = min(min_ele, num);
        max_ele = max(max_ele, num);
    }
    int hash_len = max_ele - min_ele + 1;
    bool *hash = new bool[hash_len]{false};
    // 遍历数组
    for (int &num : nums) {
        hash[num - min_ele] = true;
    }
    int cnt = 0, res = 0;
    for (int i = 0; i < hash_len; ++i) {
        if (hash[i]) {
            cnt++;
        } else {
            res = max(res, cnt);
            /* 清零 */
            cnt = 0;
        }
    }
    /* 不要忘记更新 */
    res = max(res, cnt);
    return res;
}

ListNode *deleteNode(ListNode *head, int val) {
    if (head == nullptr)
        return nullptr;
    /* 哨兵节点 */
    auto *sentinel = new ListNode;
    sentinel->next = head;
    /* 如果待删除节点就是头节点 */
    if (head->val == val) {
        sentinel->next = head->next;
        return sentinel->next;
    }
    /* 待删除节点 */
    auto *d_node = head->next;
    /* 待删除的上一个节点 */
    auto *d_node_prev = head;
    while (d_node && d_node->val != val) {
        d_node_prev = d_node;
        d_node = d_node->next;
    }
    /* 说明找到了待删除节点 */
    if (d_node) {
        d_node_prev->next = d_node->next;
    }
    return sentinel->next;
}

void deleteNode(ListNode *node) {
    if (node == nullptr)
        return;
    /* 删除节点的下一个节点 */
    auto *d_node_next = node->next;
    while (d_node_next) {
        /* 复制下一个val */
        node->val = d_node_next->val;
        /* 如果下一个节点的下一个为空时
         * 说明复制已经完成 */
        if (d_node_next->next == nullptr) {
            node->next = nullptr;
            return;
        }
        node = d_node_next;
        d_node_next = d_node_next->next;
    }
}

/* 使用双指针
 * 间隔k - 1个 */
ListNode *getKthFromEnd(ListNode *head, int k) {
    if (head == nullptr)
        return nullptr;
    auto *p_first = head;
    auto *p_second = p_first;
    /* 间隔 k - 1个元素 */
    while (k) {
        p_second = p_second->next;
        k--;
    }
    /* 当p_second为空时
     * 位置完成 */
    while (p_second) {
        p_first = p_first->next;
        p_second = p_second->next;
    }
    return p_first;
}


/* 使用双向队列维护最大值 */
vector<int> maxSlidingWindow2(vector<int> &nums, int k) {
    if (nums.empty())
        return vector<int>();
    deque<int> max_que_index;
    vector<int> res;
    int len = nums.size();
    for (int i = 0; i < len; ++i) {
        /* 维护双向队列的合法性 */
        if (!max_que_index.empty() && max_que_index.front() == i - k)
            max_que_index.pop_front();
        /* 双向队列中的所有比当前num小的都pop掉 */
        while (!max_que_index.empty() && nums[max_que_index.back()] < nums[i])
            max_que_index.pop_back();
        /* 压入当前值 */
        max_que_index.push_back(i);
        if (i >= k - 1) {
            res.push_back(nums[max_que_index.front()]);
        }
    }
    return res;
}

/* 使用二分查找法，查找从1 ~ max(piles[i])之间的正确值 */
int minEatingSpeed(vector<int> &piles, int H) {
    if (piles.empty())
        return 0;
    /* 虽然本题不会非法
     * 但还是要检测 */
    if (H < piles.size())
        return -1;
    /* 一个元素的情况 */
    if (piles.size() == 1) {
        if (piles[0] % H) {
            if (piles[0] < H)
                return 1;
            else
                return 2;
        } else return 1;
    }
    /* 找到最大值 */
    int max_speed = INT_MIN;
    for (int &pile : piles)
        max_speed = max(max_speed, pile);
    int min_speed = 1;
    int mid;
    while (min_speed <= max_speed) {
        /* 一般为了防止内存溢出，需要做加法操作 */
        mid = min_speed + (max_speed - min_speed) / 2;
        int hours = speedValid(piles, mid, H);
        /* 速度过大 */
        if (hours < H) {
            max_speed = mid - 1;
        } else if (hours > H) { // 速度过慢
            min_speed = mid + 1;
        } else {
            return mid;
        }
    }
    return min_speed;
}

inline int speedValid(vector<int> &piles, int speed, int H) {
    int hours = 0;
    for (int pile : piles) {
        if (pile < speed) {
            hours++;
        } else {
            if (pile % speed)
                hours += (pile / speed) + 1;
            else
                hours += (pile / speed);
        }
    }
    return hours;
}

/* 使用基数排序 */
int maximumGap(vector<int> &nums) {
    int len = nums.size();
    if (len < 2) {
        return 0;
    }
    /* 初始化divisor为1 */
    int divisor = 1;
    vector<vector<int>> basic_nums;
    /* 临时数组 */
    vector<int> buf;
    /* 奇数遍历 */
    return 0;
}


/* 排序（以左区间进行排序）
 * 如果当前区间头小于上一个区间尾
 * 因为排序的情况下，当前区间的区间头会最接近上一个区间尾
 * 我们只需要保留覆盖程度最小的区间
 * 所以
 * 移除，保留更小的区间尾
 * 其他情况下更新区间尾部即可 */
int diary_question::eraseOverlapIntervals(vector<vector<int>> &intervals) {
    if (intervals.empty())
        return 0;
    sort(intervals.begin(), intervals.end(), _cmp);
    int cnt = 0;
    int end = intervals[0][1];
    int len = intervals.size();
    for (int i = 1; i < len; ++i) {
        if (intervals[i][0] < end) {
            end = min(end, intervals[i][1]);
            cnt++;
        } else {
            end = intervals[i][1];
        }
    }
    return cnt;
}

static bool diary_question::_cmp(vector<int> &a, vector<int> &b) {
    return a[0] < b[0];
}

/* 使用间隔双指针 */
bool diary_question::canPlaceFlowers(vector<int> &flowerbed, int n) {
    if (n <= 0)
        return true;
    /* 花坛为空的情况 */
    if (flowerbed.empty()) {
        if (n > 0)
            return false;
        if (n <= 0)
            return true;
    }
    /* 三个指针下标 */
    int left, cur, right;
    int len = flowerbed.size();
    left = 0, right = left + 1;
    for (int i = 0; i < len - 1; ++i) {
        /* 如果两边都没有中化，并且当前位置也没有种花 */
        if (flowerbed[left] == 0 && flowerbed[right] == 0) {
            if (flowerbed[i] == 0) {
                /* 不要忘记置1 */
                flowerbed[i] = 1;
                n--;
            }
            if (n == 0)
                return true;
        }
        /* 第一次判断 */
        if (i == 0) {
            right++;
        } else {
            left++;
            right++;
        }
    }
    /* 还要进行最后一次判断 */
    if (flowerbed[right - 1] == 0 && flowerbed[left] == 0)
        n--;
    return n == 0;
}
