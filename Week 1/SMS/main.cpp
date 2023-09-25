#include <bits/stdc++.h>
using namespace std;

string key[4], sms;

int main() {
    key[0] = "adgjmptw ";
    key[1] = "behknqux";
    key[2] = "cfilorvy";
    key[3] = "sz";

    int t;
    cin >> t;

    for (int _test = 1; _test <= t; _test++) {
        cin.ignore();
        getline(cin, sms);

        int ans = 0;

        for (int i = 0; i < sms.size(); i++)
            for (int j = 0; j < 4; j++)
                for (int k = 0; k < key[j].size(); k++)
                    if (key[j][k] == sms[i])
                        ans += j + 1;

        cout << "Case #" << _test << ": " << ans << "\n";
    }
}
