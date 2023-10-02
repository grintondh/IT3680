#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30;
int n, M, a[MAXN];
int ans_cnt;

void find_solution(int pos, int sum_left) {
    if (pos == n) {
        if (sum_left == 0)
            ans_cnt++;
        return ;
    } else {
        if (sum_left < a[pos])
            return ;

        for (int i = 1; i <= sum_left / a[pos]; i++)
            find_solution(pos + 1, sum_left - a[pos] * i);
        return ;
    }
}

int main() {
    cin >> n >> M;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    find_solution(0, M);

    cout << ans_cnt;
}
