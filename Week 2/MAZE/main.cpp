#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

int n, m, r, c, ans;
bool a[1000][1000];
int min_step[1000][1000];
int r_step[4] = {1, 0, -1, 0};
int c_step[4] = {0, 1, 0, -1};

void solve() {
    priority_queue <pii, vector<pii>, greater<pii> > pq;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            min_step[i][j] = 2 * (n + m);
    min_step[r - 1][c - 1] = 0;
    pq.push(make_pair(0, (r - 1) * m + (c - 1)));

    while(!pq.empty()) {
        pii u = pq.top();
        pq.pop();

        int r_now = u.second / m;
        int c_now = u.second % m;

        if (min_step[r_now][c_now] != u.first)
            continue;

        for (int i = 0; i < 4; i++) {
            int r_next = r_now + r_step[i];
            int c_next = c_now + c_step[i];

            if (r_next < 0 || c_next < 0 || r_next >= n || c_next >= m || a[r_next][c_next] == 1)
                continue;

            if (min_step[r_next][c_next] > min_step[r_now][c_now] + 1) {
                min_step[r_next][c_next] = min_step[r_now][c_now] + 1;
                pq.push(make_pair(min_step[r_next][c_next], r_next * m + c_next));
            }
        }
    }

    ans = 2 * (n + m);

    for (int i = 0; i < m; i++) {
        if (a[0][i] != 1)
            ans = min(ans, min_step[0][i]);
        if (a[n - 1][i] != 1)
            ans = min(ans, min_step[n - 1][i]);
    }

    for (int i = 0; i < n; i++) {
        if (a[i][0] != 1)
            ans = min(ans, min_step[i][0]);
        if (a[i][m - 1] != 1)
            ans = min(ans, min_step[i][m - 1]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> r >> c;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];

    solve();

    cout << ((ans == 2 * (n + m)) ? -1 : (ans + 1));
}

/*
3 3 2 2
0 0 1
0 0 1
1 0 0
*/
