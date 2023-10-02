#include <bits/stdc++.h>
using namespace std;

int n, a[13][13], ans_cnt;

void backtrack(int row, int col, int queen_left) {
    if (row == n) {
        if (queen_left == 0)
            ans_cnt++;
        return ;
    } else {
        if (row + queen_left > n)
            return ;

        if (a[row][col] == 1) {
            if (col < n - 1)
                backtrack(row, col + 1, queen_left);
            else
                backtrack(row + 1, 0, queen_left);
            return ;
        }

        bool have_queen = false;

        for (int i = 0; i < n; i++) {
            if (a[i][col] == 1) {
                have_queen = true;
                break;
            }

            if (a[row][i] == 1) {
                have_queen = true;
                break;
            }
        }

        if (have_queen == false) {
            for (int i = - n; i < n; i++) {
                if (row + i < 0 || col + i < 0 || row + i >= n || col + i >= n)
                    continue;
                if (a[row + i][col + i] == 1)
                    have_queen = true;
            }

            for (int i = - n; i < n; i++) {
                if (row + i < 0 || col - i < 0 || row + i >= n || col - i >= n)
                    continue;
                if (a[row + i][col - i] == 1)
                    have_queen = true;
            }
        }

        if (have_queen == false) {
            a[row][col] = 1;
            if (col < n - 1)
                backtrack(row, col + 1, queen_left - 1);
            else
                backtrack(row + 1, 0, queen_left - 1);
        }

        a[row][col] = 0;
        if (col < n - 1)
            backtrack(row, col + 1, queen_left);
        else
            backtrack(row + 1, 0, queen_left);
    }
}
int main() {
    cin >> n;

    int queen_left = n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            queen_left = queen_left - a[i][j];
        }

    backtrack(0, 0, queen_left);

    cout << ans_cnt;
}
