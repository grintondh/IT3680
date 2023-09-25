/// ALICEADD
/// Last modified: 18/9/2023

#include <bits/stdc++.h>
using namespace std;

struct BigNum {
    string val;

    BigNum operator + (BigNum &B) {
        BigNum ans;
        int rem = 0, sum = 0;
        int endA = this->val.size() - 1, endB = B.val.size() - 1;

        ans.val.resize(max(endA + 1, endB + 1));

        for (int i = ans.val.size() - 1; i >= 0; i--) {
            int valA = (endA < 0) ? 0 : ((int) this->val[endA] - 48);
            int valB = (endB < 0) ? 0 : ((int) B.val[endB] - 48);

            sum = valA + valB + rem;
            if (sum / 10 > 0)
                rem = sum / 10;

            ans.val[i] = (char) (sum % 10 + 48);

            endA--, endB--;
        }

        if (rem > 0)
            ans.val = (char) (rem + 48) + ans.val;
        return ans;
    }

    void PrintVal() {
        cout << this->val << "\n";
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int t;
    BigNum alice, bob;

    cin >> t;
    while(t--) {
        cin >> alice.val >> bob.val;
        (alice + bob).PrintVal();
    }
}
