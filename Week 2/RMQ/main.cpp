#include <iostream>
#include <stdio.h>
using namespace std;

const int maxn = 1000001;

int ans, n, m, l, r, jump;
int rmq[20][maxn], pow_2[21];

int log_2(int x) {
    return 64 - __builtin_clzll(x) - 1;
}

void process() {
    pow_2[0] = 1;
    for (int i = 1; i <= 20; i++)
        pow_2[i] = pow_2[i - 1] * 2;

    for (int j = 1; j <= log_2(n); j++)
        for (int i = 0; i + pow_2[j] <= n; i++)
            if (rmq[j - 1][i] < rmq[j - 1][i + pow_2[j - 1]])
                rmq[j][i] = rmq[j - 1][i];
            else
                rmq[j][i] = rmq[j - 1][i + pow_2[j - 1]];
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &rmq[0][i]);

    process();

    scanf("%d", &m);
    while(m--) {
        scanf("%d%d", &l, &r);
        jump = log_2(r - l + 1);

        if (rmq[jump][l] <= rmq[jump][r - pow_2[jump] + 1])
            ans = ans + rmq[jump][l];
        else
            ans = ans + rmq[jump][r - pow_2[jump] + 1];
    }
    printf("%d", ans);
}

/*
3
1 2 3
2
0 2
1 2
*/
