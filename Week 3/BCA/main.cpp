#include <bits/stdc++.h>
using namespace std;

int m, n, k, ans = INT_MAX;
vector<int> course[31];
bool conflict_course[31][31];
int course_taught[31], teacher_taught[11];

void TRY(int course_id, int maximal_load) {
    if (course_id == n) {
        ans = min(ans, maximal_load);
        return ;
    } else {
        for (int i = 0; i < course[course_id].size(); i++) {
            int teacher_id = course[course_id][i];

            bool conflict = false;

            for (int j = 0; j < course_id; j++) {
                if (course_taught[j] == teacher_id && conflict_course[course_id][j] == true) {
                    conflict = true;
                    break;
                }
            }

            if (conflict == true)
                continue;

            course_taught[course_id] = teacher_id;
            teacher_taught[teacher_id]++;

            TRY(course_id + 1, max(maximal_load, teacher_taught[teacher_id]));

            teacher_taught[teacher_id]--;
            course_taught[course_id] = 0;
        }
    }
}

int main() {
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        int course_size, course_id;
        cin >> course_size;

        while(course_size--) {
            cin >> course_id;
            course[course_id - 1].push_back(i - 1);
        }
    }

    cin >> k;
    while(k--) {
        int u, v;
        cin >> u >> v;

        conflict_course[u - 1][v - 1] = conflict_course[v - 1][u - 1] = true;
    }

    TRY(0, 0);
    cout << ((ans == INT_MAX) ? (-1) : ans);
}
