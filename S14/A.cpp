// Algorithm:
// - Divide all objects into 4 groups based on weights.
// - Let xi = how many objects we should select from i-th group
// Brute force x0, x1, x2. We can easily calculate x3.
// In each group, we should select objects with largest values.
// 
// Complexity: O(N^3).

#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) ((S) & TWO(X))

int rand16() {
    return rand() & (TWO(16) - 1);
}
int my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 111;

struct Obj {
    int weight;
    int value;

    void read() {
        cin >> weight >> value;
    }
};
bool operator < (const Obj& a, const Obj& b) {
    return a.value > b.value;
}

Obj all[MN];
int w1;
vector<Obj> a[4];
vector<int> totalValue[4];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int N, W;
    while (cin >> N >> W) {
        FOR(i,1,N) all[i].read();
        w1 = all[1].weight;

        // Divide into 4 groups: a[0] -> a[3] based on weight
        REP(i,4) a[i].clear();
        FOR(i,1,N) {
            int group = all[i].weight - w1;
            a[group].push_back(all[i]);
        }

        // If we take X items from a group, it should be X items with largest value
        // --> sort each group by decreasing value
        // Also precalculate totalValue[X] = total value of first X items.
        REP(i,4) {
            sort(a[i].begin(), a[i].end());

            totalValue[i].resize(SZ(a[i]) + 1);
            totalValue[i][0] = 0;
            FOR(j,1,SZ(a[i])) {
                totalValue[i][j] = totalValue[i][j-1] + a[i][j-1].value;
            }
        }

        int res = 0;
        // Brute force how many objects we should get from the first 3 groups:
        FOR(i0,0,SZ(a[0])) FOR(i1,0,SZ(a[1])) FOR(i2,0,SZ(a[2])) {
            int currentWeight =
                i0 * w1
                + i1 * (w1 + 1)
                + i2 * (w1 + 2);
            if (currentWeight > W) continue;

            int i3 = (W - currentWeight) / (w1 + 3);
            if (i3 > SZ(a[3])) i3 = SZ(a[3]);  // Cannot take more than what we have

            res = max(res,
                    totalValue[0][i0]
                    + totalValue[1][i1]
                    + totalValue[2][i2]
                    + totalValue[3][i3]);
        }
        cout << res << endl;
    }
    return 0;
}

