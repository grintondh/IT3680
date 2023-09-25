#include <bits/stdc++.h>
using namespace std;

struct timeStruct {
    int hr = 0;
    int mn = 0;
    int sd = 0;

    void GetTime (string str) {
        this->hr = ((int) str[0] - 48) * 10 + ((int) str[1] - 48);
        this->mn = ((int) str[3] - 48) * 10 + ((int) str[4] - 48);
        this->sd = ((int) str[6] - 48) * 10 + ((int) str[7] - 48);
    }

    int operator - (timeStruct &A) {
        int ans = this->hr * 3600 + this->mn * 60 + this->sd - A.hr * 3600 - A.mn * 60 - A.sd;
        return ans;
    }
};

struct callStruct {
    string fromPhoneNo, toPhoneNo;
    string date;
    timeStruct fromTime, toTime;

    void SetValue (string callData) {
        string tmpStr = "";
        int statVal = 0;

        callData += ' ';
        for (int i = 0; i < callData.size(); i++) {
            if (callData[i] == ' ') {
                statVal++;

                if (statVal == 2)
                    this->fromPhoneNo = tmpStr;
                else if (statVal == 3)
                    this->toPhoneNo = tmpStr;
                else if (statVal == 4)
                    this->date = tmpStr;
                else if (statVal == 5)
                    this->fromTime.GetTime(tmpStr);
                else if (statVal == 6)
                    this->toTime.GetTime(tmpStr);

                tmpStr = "";
            }
            else
                tmpStr += callData[i];
        }
    }
};

vector< pair<string, int> > calledData;
map<string, pair<int, int> > savedData;

bool checkPhoneNumber;

bool PhoneValidate(string s) {
    for (int i = 0; i < s.size(); i++)
        if (s[i] < '0' || s[i] > '9')
            return false;
    return true;
}

void ProcessData() {
    int cnt = 0, totalTime = 0;
    for (int i = 0; i < calledData.size(); i++) {
        cnt++, totalTime += calledData[i].second;

        if (i == calledData.size() - 1 || calledData[i].first != calledData[i + 1].first) {
            savedData.insert({ calledData[i].first, make_pair(cnt, totalTime) });
            cnt = 0, totalTime = 0;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    string inputStr;
    int stateValue = 1;

    checkPhoneNumber = true;

    while(getline(cin, inputStr)) {
        // State 1: data input; State 2: data query
        if (inputStr == "#") {
            stateValue++;

            if (stateValue == 3)
                break;
            else if (stateValue == 2) {
                sort(calledData.begin(), calledData.end());
                ProcessData();
            }
        }

        if (stateValue == 1) {
            callStruct c;
            c.SetValue(inputStr);

            if (PhoneValidate(c.fromPhoneNo) == false)
                checkPhoneNumber = false;

            calledData.push_back(make_pair(c.fromPhoneNo, c.toTime - c.fromTime));
        } else {
            if (inputStr == "?check_phone_number")
                cout << ((checkPhoneNumber == true) ? 1 : 0) << "\n";
            else if (inputStr == "?number_total_calls")
                cout << calledData.size() << "\n";
            else if (inputStr.substr(0, 18) == "?number_calls_from") {
                string fromPhoneNo = inputStr.erase(0, 19);
                cerr << fromPhoneNo << "\n";
                cout << savedData[fromPhoneNo].first << "\n";
            } else if (inputStr.substr(0, 22) == "?count_time_calls_from") {
                string fromPhoneNo = inputStr.erase(0, 23);
                cout << savedData[fromPhoneNo].second << "\n";
            }
        }
    }
    return 0;
}

/*
call 0912345678 0132465789 2022-07-12 10:30:23 10:32:00
call 0912345678 0945324545 2022-07-13 11:30:10 11:35:11
call 0132465789 0945324545 2022-07-13 11:30:23 11:32:23
call 0945324545 0912345678 2022-07-13 07:30:23 07:48:30
#
?check_phone_number
?number_calls_from 0912345678
?number_total_calls
?count_time_calls_from 0912345678
?count_time_calls_from 0132465789
#
*/
