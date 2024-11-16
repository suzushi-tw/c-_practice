#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

// 計算偏好等級的結構體
struct Puzzle {
    string str;
    int preference;
    int index;
};

// 計算單個字串的偏好等級
int calculatePreference(const string& s, int m, ll k, ll x, ll y) {
    int len = s.length();
    int count = 0;
    
    for (int i = 0; i + m <= len; i++) {
        ll hash = 0;
        ll power = 1;
        
        // 計算第一個窗口的雜湊值
        for (int j = i + m - 1; j >= i; j--) {
            hash = (hash + ((ll)(s[j] - 'a' + 1) * power) % y) % y;
            if (j > i) power = (power * k) % y;
        }
        
        if (hash == x) count++;
    }
    
    return count;
}

// 穩定排序用的比較函數
bool compare(const Puzzle& a, const Puzzle& b) {
    if (a.preference == b.preference)
        return a.index < b.index;
    return a.preference > b.preference;
}

int main() {
    int n, m;
    ll k, x, y;
    cin >> n >> m >> k >> x >> y;
    
    vector<Puzzle> puzzles(n);
    
    // 讀取並計算每個謎題的偏好等級
    for (int i = 0; i < n; i++) {
        cin >> puzzles[i].str;
        puzzles[i].preference = calculatePreference(puzzles[i].str, m, k, x, y);
        puzzles[i].index = i;
    }
    
    // 排序
    stable_sort(puzzles.begin(), puzzles.end(), compare);
    
    // 輸出結果
    for (const auto& p : puzzles) {
        cout << p.str << "\n";
    }
    
    return 0;
}