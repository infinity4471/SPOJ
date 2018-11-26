#include <cstdio>
#include <set>
#include <map>
#include <string>

using namespace std;

typedef unsigned long long int lli;
typedef pair< lli, lli > int_pair;
typedef set< int_pair > pair_set;
typedef pair_set::iterator pair_set_it;
typedef map< string, int_pair > pair_map;
typedef pair_map::iterator pair_map_it;

pair_set s;
pair_map m;

int main() {
    int M;
    lli S, P, total = 0;
    char N[21];
    char A;

    scanf("%i", &M);

    for (int i = 0; i < M; ++i) {
        scanf("%*c%c %s", &A, N);

        bool has_prev = false;
        bool has_next = false;

        if (A == 'A') {
            scanf("%llu %llu", &S, &P);

            pair< pair_set_it, bool > res = s.insert(make_pair(S, P));
            pair_set_it prev = res.first;
            if (prev != s.begin()) {
                has_prev = true;
                --prev;
            }

            pair_set_it next = res.first;
            ++next;
            if (next != s.end()) {
                has_next = true;
            }

            if (has_prev && has_next) {
                total -= prev->second * next->second;
            }

            m[N] = make_pair(S, P);

            if (has_prev) {
                total += prev->second * P;
            }
            if (has_next) {
                total += next->second * P;
            }
        }
        else {
            pair_map_it mit = m.find(N);
            if (mit != m.end()) {
                S = mit->second.first;
                P = mit->second.second;
                pair_set_it it = s.find(make_pair(S, P));
                pair_set_it prev = it;
                pair_set_it next = it;

                if (prev != s.begin()) {
                    --prev;
                    has_prev = true;
                }
                ++next;
                if (next != s.end()) {
                    has_next = true;
                }

                if (has_prev) {
                    total -= P * prev->second;
                }
                if (has_next) {
                    total -= P * next->second;
                }
                if (has_prev && has_next) {
                    total += prev->second * next->second;
                }

                s.erase(it);
                m.erase(N);
            }
        }
        printf("%llu\n", total);
    }

    return 0;
}
