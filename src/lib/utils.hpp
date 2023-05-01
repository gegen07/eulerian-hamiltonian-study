#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector> 
#include <set> 
#include <algorithm>

namespace utils {
    void solve(std::vector<int>& arr, int n, std::set<std::vector<int> >& ans, std::vector<int> v, int i){
        if (i >= n) {
            ans.insert(v);
            return;
        }
    
        // Not pick
        solve(arr, n, ans, v, i + 1);
    
        // Pick
        v.push_back(arr[i]);
        solve(arr, n, ans, v, i + 1);
    }

    std::vector<std::vector<int>> getSubsets(std::vector<int> arr, int n){
    
        // Set of vectors to store
        // required unique subsets
        std::set<std::vector<int>> ans;
    
        std::sort(arr.begin(), arr.end());
        std::vector<int> v;
        solve(arr, n, ans, v, 0);
    
        // Vector of vectors to store final result
        std::vector<std::vector<int> > res;
        while (!ans.empty()) {
            res.push_back(*ans.begin());
            ans.erase(ans.begin());
        }
        return res;
    }
}


#endif