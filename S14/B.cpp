// Algorithm:
// - Let f(u) = how many paths coming out of T(u)
// - At each node u, let:
//     - x = how many paths that connect T(vi) to T(vj)
//     - y = how many paths coming out of T(u) = f(u)
//     - x + y = A(u)
//     - 2*x + y = sum(f(v))
// - So we can calculate all f(u) in O(N).
// NOTE: we must also check that values of x and y are valid.

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

const int MN = 100111;
int n, a[MN];
vector<int> ke[MN];
int f[MN];

void dfs(int u, int fu) {
    // If u is leaf node
    if (SZ(ke[u]) == 1) {
        f[u] = a[u];
        return ;
    }

    int sum = 0;
    int ln = -1;
    for (int v : ke[u]) if (v != fu) {
        dfs(v, u);
        sum += f[v];
        ln = max(ln, f[v]);
    }

    // At subtree(u), there are 2 types of paths:
    // - paths connecting 2 subtree(v1) and subtree(v2): x
    // - paths going up (go out of subtree(u)): y
    // Note that f[u] = y
    //
    // sum(f[v]) = 2*x + y
    // a[u] = x + y
    int x = sum - a[u];
    int y = a[u] - x;
    f[u] = y;

    if (x < 0 || y < 0) throw 1;

    // Can we greedily connect subtrees?
    if (x > sum - ln) throw 1;
}

bool solve() {
    // Let root = any vertex with degree > 1
    // For n = 2, there is no such vertex
    if (n == 2) {
        return a[1] == a[2];
    }
    int root = -1;
    FOR(i,1,n) if (SZ(ke[i]) > 1) root = i;
    assert(root > 0);

    // Calculate f[i] = how many paths go up from i
    try {
        dfs(root, -1);
        return f[root] == 0;
    } catch (...) {
        return false;
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    while (cin >> n) {
        FOR(i,1,n) ke[i].clear();

        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n-1) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }

        cout << (solve() ? "YES" : "NO") << endl;
    }
    return 0;
}

