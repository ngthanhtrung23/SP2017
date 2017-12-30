#include <sstream>
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
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%d", &x); }

struct Node {
    map<int,Node*> next;
    int f;

    void recalc() {
        int sumxor = 0;
        for(auto it : next) {
            sumxor ^= it.second->f + 1;
        }
        f = sumxor;
    }
};
Node* createNode() {
    Node* res = new Node();
    res->f = 0;
    res->next.clear();
    return res;
}
char s[55];

int l;

void update(Node* root, int i) {
    if (i == l) {
        // No more character to add.
        root->recalc();
        return ;
    }
    
    int c = s[i] - 'a';
    assert(c < 30);

    if (!root->next.count(c)) root->next[c] = createNode();
    update(root->next[c], i+1);

    root->recalc();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; GI(ntest);
    FOR(test,1,ntest) {
        printf("Case %d:\n", test);
        int n; GI(n);
        Node* root = createNode();
        FOR(i,1,n) {
            scanf("%s", &s[0]);
            l = strlen(s);

            update(root, 0);
        }

        int q; GI(q);
        while (q--) {
            scanf("%s", &s[0]);
            l = strlen(s);
            update(root, 0);

            if (root->f == 0) puts("2");
            else puts("1");
        }
    }
}
