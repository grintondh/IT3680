#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

const int maxn = 1005;

int n, m, ans = 0;
int d[maxn][maxn];
bool a[maxn][maxn];
stack<pii> st;

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            if (a[i][j] == 1)
                d[i][j] = d[i - 1][j] + 1;
            else
                d[i][j] = 0;


        d[i][m + 1] = 0;
        for (int j = 1; j <= m + 1; j++) {
            if (st.empty() || d[i][j] >= st.top().second)
                st.push(make_pair(j, d[i][j]));
            else {
                int left_bound = j;
                while(!st.empty() && st.top().second > d[i][j]) {
                    ans = max(ans, st.top().second * (j - st.top().first));
                    left_bound = st.top().first;
                    st.pop();
                }
                st.push(make_pair(left_bound, d[i][j]));
            }
        }

        while(!st.empty())
            st.pop();
    }

    cout << ans;
}
