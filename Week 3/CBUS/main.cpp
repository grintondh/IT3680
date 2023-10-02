#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n, k, c[MAXN][MAXN];
int ans = INT_MAX;

// 0: chua len, 1: dang len, 2: da len
int onbus[MAXN];
int mask[2049][2049];

void update_mask(int mask_id_1, int mask_id_2, int val) {
    if (mask[mask_id_1][mask_id_2] == 0)
        mask[mask_id_1][mask_id_2] = val;
    else
        mask[mask_id_1][mask_id_2] = min(mask[mask_id_1][mask_id_2], val);
}

void find_solution(int pos, int passenger_left, int passenger_onbus, int passenger_onbus_count, int sum_dist) {
    if (passenger_left == 0 && passenger_onbus == 0) {
        ans = min(ans, sum_dist + c[pos][0]);
        update_mask(passenger_left, passenger_onbus, c[pos][0]);
    } else {
        if (sum_dist + mask[passenger_left][passenger_onbus] > ans)
            return ;

        if (passenger_left != 0 && passenger_onbus_count < k) {
            for (int i = 0; i < n; i++)
                if ((passenger_left & (1 << i)) != 0) {
                    if (sum_dist + c[pos][i + 1] < ans) {
                        int new_passenger_left = passenger_left - (1 << i);
                        int new_passenger_onbus = passenger_onbus + (1 << i);

                        find_solution(i + 1, new_passenger_left, new_passenger_onbus, passenger_onbus_count + 1, sum_dist + c[pos][i + 1]);

                        update_mask(passenger_left, passenger_onbus, mask[new_passenger_left][new_passenger_onbus] + c[pos][i + 1]);
                    }
                }
        }

        if (passenger_onbus_count > 0) {
            for (int i = 0; i < n; i++)
                if ((passenger_onbus & (1 << i)) != 0) {
                    if (sum_dist + c[pos][i + n + 1] < ans) {
                        int new_passenger_left = passenger_left;
                        int new_passenger_onbus = passenger_onbus - (1 << i);

                        find_solution(i + n + 1, new_passenger_left, new_passenger_onbus, passenger_onbus_count - 1, sum_dist + c[pos][i + n + 1]);

                        update_mask(passenger_left, passenger_onbus, mask[new_passenger_left][new_passenger_onbus] + c[pos][i + n + 1]);
                    }
                }
        }
    }
}

int main() {
    cin >> n >> k;
    for (int i = 0; i <= 2 * n; i++)
        for (int j = 0; j <= 2 * n; j++)
            cin >> c[i][j];

    find_solution(0, (1 << n) - 1, 0, 0, 0);

    cout << ans;
}
