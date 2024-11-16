#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

struct Puzzle
{
    string str;
    int preference;
    int index;
};

int calculatePreference(const string &s, int m, ll k, ll x, ll y)
{
    int len = s.length();
    if (len < m)
        return 0;

    int count = 0;

  
    vector<ll> k_pows(m + 1);
    k_pows[0] = 1;
    for (int i = 1; i <= m; ++i)
    {
        k_pows[i] = (k_pows[i - 1] * k) % y;
    }
    ll k_m = k_pows[m];

  
    ll H = 0;
    for (int j = 0; j < m; ++j)
    {
        ll ascii_val = s[j];
        H = (H + ascii_val * k_pows[m - j - 1]) % y;
    }
    if (H == x)
        count++;

   
    for (int i = 1; i + m - 1 < len; ++i)
    {
        ll a_i = s[i - 1];
        ll a_i_m = s[i + m - 1];

        H = ((H * k - a_i * k_m % y + y) % y + a_i_m) % y;
        if (H == x)
            count++;
    }
    return count;
}

bool compare(const Puzzle &a, const Puzzle &b)
{
    if (a.preference == b.preference)
        return a.index < b.index;
    return a.preference > b.preference;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    ll k, x, y;
    cin >> n >> m >> k >> x >> y;

    vector<Puzzle> puzzles(n);

    for (int i = 0; i < n; i++)
    {
        cin >> puzzles[i].str;
        puzzles[i].preference = calculatePreference(puzzles[i].str, m, k, x, y);
        puzzles[i].index = i;
    }

    stable_sort(puzzles.begin(), puzzles.end(), compare);

 
    for (const auto &p : puzzles)
    {
        cout << p.str << ":" << p.preference << "\n";
    }

    return 0;
}