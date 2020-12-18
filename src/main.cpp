//
// Created by 87569 on 2020/12/18.
//

#include "LeetCode.h"
#include "iostream"
#include "ctime"

int main(int argc, char **argv) {
    srand(time(nullptr));
    vector<int> v;
    int n;
    for (int i = 0; i < 2; ++i) {
        cin >> n;
        v.push_back(n);
    }
    sort(v.begin(), v.end());
    for (int vi : v) {
        printf("%d-", vi);
    }
    printf("\n");
    int i = removeDuplicates(v);
    for (int j = 0; j < i; ++j) {
        printf("%d-", v[j]);
    }
}
