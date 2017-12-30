#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
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

const int MN = 200111;
vector< pair<int,int> > ke[MN];
int f[MN];
map<int,int> id;
int n;

int vertexId(int u) {
    if (u < 1) return -1;
    if (id.count(u)) return id[u];
    id[u] = ++n;
    return id[u];
}

void addEdge(int u, int v, int c) {
    ke[u].emplace_back(v, c);
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int s, t;
    while (cin >> s >> t) {
        id.clear();
        n = 0;
        REP(i,MN) ke[i].clear();

        if (t % s == 0) {
            cout << 0 << endl;
            continue;
        }

        FOR(i,1,10) vertexId(i);
        for (int i = 2; i*i <= t; i++) {
            if (t % i == 0) {
                FOR(x,i-2,i+2) vertexId(x);
                FOR(x,t/i-2,t/i+2) vertexId(x);
            }
        }
        FOR(x,t-3,t+3) vertexId(x);

        for (auto it = id.begin(); it != id.end(); it++) {
            auto it2 = it;
            it2++;
            if (it2 != id.end()) {
                addEdge(it->second, it2->second, llabs(it->first - it2->first));
                addEdge(it2->second, it->second, llabs(it->first - it2->first));
            }

            int u = it->first;
            for (; it2 != id.end(); it2++) {
                int v = it2->first;
                if (v % u == 0 && vertexId(v) > 0) {
                    addEdge(it->second, vertexId(v), 0);
                }
            }
        }

        REP(i,MN) f[i] = 1000111000111LL;

        set< pair<int,int> > all;
        f[vertexId(s)] = 0;
        all.insert(make_pair(0, vertexId(s)));

        while (!all.empty()) {
            int u = all.begin()->second;
            int l = all.begin()->first;
            all.erase(all.begin());
            if (l != f[u]) continue;

            for (auto e : ke[u]) {
                int v = e.first;
                int c = e.second;

                if (f[v] > f[u] + c) {
                    f[v] = f[u] + c;
                    all.insert(make_pair(f[v], v));
                }
            }
        }
        cout << f[vertexId(t)] << endl;
    }
    return 0;
}
