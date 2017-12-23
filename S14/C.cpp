// Algorithm:
// - Init f(u) = how many weights we need to scale value u. This is standard problem,
//   in optimal solution, we don't need to use repeated weights.
// - Calculate g(l, r) = minimum cost (C) to find exact value in range [L, R]
// - Figure out that maximum value of C is small (< 77)
// - Use swap state DP: g(l, C) = maximum value of r.

#include "bits/stdc++.h"
using namespace std;

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

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%d", &x); }

int f[10111], cost[555][555], jump[10111][77 + 11], last[10111][77 + 11];

void init() {
    // Available weights
    vector<int> weights;
    for (int w = 1; w <= 10000; w *= 3) {
        weights.push_back(w);
    }

    // f[i] = minimum number of weight to get i-kg.
    queue<int> qu;
    memset(f, -1, sizeof f);
    f[0] = 0;
    qu.push(0);

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        for (int w : weights) {
            int v = u + w;
            if (v <= 10000 && f[v] < 0) {
                f[v] = f[u] + 1;
                qu.push(v);
            }

            // Note that we can put weights on both sides.
            v = u - w;
            if (v >= 0 && f[v] < 0) {
                f[v] = f[u] + 1;
                qu.push(v);
            }
        }
    }

    // For r <= 500:
    // cost[l][r] = minimum cost if we know X is in range [l, r]
    FOR(i,0,505) FOR(j,0,505)
        if (i >= j) {
            cost[i][j] = 0;
        } else {
            cost[i][j] = 1000111;
        }
    FORD(i,500,1) FOR(j,i+1,500) {
        FOR(k,i,j) cost[i][j] = min(cost[i][j], max(cost[i][k-1], cost[k+1][j]) + f[k]);
    }

    // last[r][x] = largest k such that: k <= r and f[k] = x.
    FOR(r,1,10000) {
        FOR(x,1,77) last[r][x] = last[r-1][x];
        last[r][f[r]] = r;
    }

    // For r <= 10000
    // jump[l][x] = if total cost of all scale operations = x, what is largest value of r?
    FORD(i,10000,1) {
        // If we don't scale, can't go anywhere
        jump[i][0] = i;

        FOR(x,1,77) {
            jump[i][x] = i;

            FOR(cur,1,x) { // cur = EXACT cost of the 1st scaling operation
                int r1 = jump[i][x - cur]; // how far we can go with the remaining operations
                if (r1 == 10000) jump[i][x] = r1; // too far
                else {
                    // Ideally we want to use scaling at r1+1. But this is not always possible.
                    // We have to find the largest value k in range [i, r1+1] with f[k] == cur
                    int k = last[r1+1][cur];
                    jump[i][x] = max(jump[i][x], jump[k+1][x - cur]);
                }
            }
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    init();
    int q; GI(q);
    while (q--) {
        int l, r; GI(l); GI(r);
        FOR(res,0,77) if (jump[l][res] >= r) {
            printf("%d\n", res);
            break;
        }
    }
    return 0;
}

