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

int n, a[MN], c[MN], nc;
int pos[MN][2];
int f[MN][2];

int go(int a, int b, int c) {
    return llabs(b - a) + llabs(c - b);
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        // RR
        nc = n;
        FOR(i,1,n) c[i] = a[i];
        sort(c+1, c+n+1);
        nc = unique(c+1, c+nc+1) - c - 1;

        FOR(i,1,n) a[i] = lower_bound(c+1, c+nc+1, a[i]) - c;

        memset(pos, -1, sizeof pos);
        pos[0][0] = pos[0][1] = 1;
        FOR(i,1,n) {
            int val = a[i];
            if (pos[val][0] < 0) pos[val][0] = pos[val][1] = i;
            else {
                pos[val][0] = min(pos[val][0], i);
                pos[val][1] = max(pos[val][1], i);
            }
        }

        f[0][0] = f[0][1] = 0;
        FOR(i,1,nc) {
            f[i][0] = min(
                    f[i-1][0] + go(pos[i-1][0], pos[i][1], pos[i][0]),
                    f[i-1][1] + go(pos[i-1][1], pos[i][1], pos[i][0]));
            f[i][1] = min(
                    f[i-1][0] + go(pos[i-1][0], pos[i][0], pos[i][1]),
                    f[i-1][1] + go(pos[i-1][1], pos[i][0], pos[i][1]));
        }

        cout << n + min(f[nc][0], f[nc][1]) << endl;
    }
    return 0;
}
