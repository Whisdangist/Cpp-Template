#include <bits/stdc++.h>
using namespace std;

#ifdef OFFLINE
#include <windows.h>
#define ASSERT(exp) assert(exp)
#else
#pragma GCC optimize(3)
#define ASSERT(exp) ((void)0)
#endif

#define INF 0x0FFFFFFF
#define IS_POS_INF(num) ((bool)(num > (INF / 2)))
#define IS_NEG_INF(num) ((bool)(num < (-INF / 2)))

typedef long long ll;

#define MAX_N 40000
#define MAX_M 20000

int N, M, K;
struct Node {
    int parent;
    int rank;
} nodes[MAX_N+1];

int Find(int x) {
    if (nodes[x].parent == x) return x;
    return nodes[x].parent = Find(nodes[x].parent);
}

int Union(int x, int y) {
    x = Find(x);
    y = Find(y);
    if (x == y) return 0;

    if (nodes[x].rank > nodes[y].rank) {
        nodes[y].parent = x;
    }
    else if (nodes[x].rank < nodes[y].rank) {
        nodes[x].parent = y;
    }
    else {
        nodes[y].parent = x;
        nodes[x].rank++;
    }
    return -1;
}

void solve() {
    cin >> N >> M;
    vector<pair<int, int> > e0;  //, e1;
    for (int i = 0; i < M; i++) {
        int x, y;
        cin >> x >> y;
        if (x != y)
            e0.push_back(make_pair(x, y));
    }
    cin >> K;
    vector<int> v(K);
    auto e0_s0 = e0, e0_s1 = e0;  // search0 & search1
    vector<pair<int, int> > e1_s0, e1_s1;
    auto comp0 = [](pair<int, int> a, pair<int, int> b){ return a.first < b.first; };
    auto comp1 = [](pair<int, int> a, pair<int, int> b){ return a.second < b.second; };
    sort(e0_s0.begin(), e0_s0.end(), comp0);
    sort(e0_s1.begin(), e0_s1.end(), comp1);
    for (int i = 0; i < K; i++) {
        cin >> v[i];
    }
    vector<int> v1(v);
    sort(v1.begin(), v1.end());
    for (int i = 0; i < K; i++) {
        auto ie0 = lower_bound(e0_s0.begin(), e0_s0.end(), make_pair(v[i], 0), comp0);
        auto ie1 = lower_bound(e0_s1.begin(), e0_s1.end(), make_pair(0, v[i]), comp1);
        while (ie0 != e0_s0.end()) {
            auto e = *ie0;
            if (e.first != v[i]) break;
            e1_s0.push_back(e);
            ie0 = e0_s0.erase(ie0);         
        }
        while (ie1 != e0_s1.end()) {
            auto e = *ie1;
            if (e.second != v[i]) break;
            e1_s1.push_back(e);
            ie1 = e0_s1.erase(ie1);         
        }
        // for (auto ie = e0.begin(); ie != e0.end(); ) {
        //  auto e = *ie;
        //  if (e.first == v[i] || e.second == v[i]) {
        //      e1.push_back(e);
        //      ie = e0.erase(ie);
        //  }
        //  else {
        //      ie++;
        //  }
        // }
    }
    
    int num = 0;
    // init
    for (int i = 0; i < N; i++) {
        nodes[i].parent = -1;
        nodes[i].rank = 0;
    }
    // add nodes
    for (int i = 0, j = 0; j < N; j++) {
        if (i < v1.size() && v1[i] == j) {
            i++;
            continue;
        }
        nodes[j].parent = j;
        num++;
    }
    e0.clear();
    sort(e0_s0.begin(), e0_s0.end());
    sort(e0_s1.begin(), e0_s1.end());
    set_intersection(e0_s0.begin(), e0_s0.end(), e0_s1.begin(), e0_s1.end(), back_inserter(e0));
    // original union
    for (auto &e: e0) {
        num += Union(e.first, e.second);
    }
    // attack
    sort(e1_s0.begin(), e1_s0.end(), comp0);
    sort(e1_s1.begin(), e1_s1.end(), comp1);
    stack<int> s;
    for (int i = K-1; i >= 0 && !(e1_s0.empty() && e1_s1.empty()); i--) {
        s.push(num);
        num++;
        nodes[v[i]].parent = v[i];
        auto ie0 = lower_bound(e1_s0.begin(), e1_s0.end(), make_pair(v[i], 0), comp0);
        auto ie1 = lower_bound(e1_s1.begin(), e1_s1.end(), make_pair(0, v[i]), comp1);
        while (ie0 != e1_s0.end()) {
            auto e = *ie0;
            if (e.first != v[i]) break;
            if (nodes[e.second].parent != -1) {
                num += Union(v[i], e.second);
                ie0 = e1_s0.erase(ie0);
            }
            else {
                ie0++;
            }
        }
        while (ie1 != e1_s1.end()) {
            auto e = *ie1;
            if (e.second != v[i]) break;
            if (nodes[e.first].parent != -1) {
                num += Union(v[i], e.first);
                ie1 = e1_s1.erase(ie1);
            }
            else {
                ie1++;
            }
        }
        // for (auto ie = e1.begin(); ie != e1.end(); ) {
        //  auto e = *ie;
        //  bool flag = true;
        //  if (e.first == v[i] || e.second == v[i]) {
        //      int tmp = e.first == v[i] ? e.second : e.first;
        //      if (nodes[tmp].parent != -1) {
        //          num += Union(v[i], tmp);
        //          flag = false;
        //          e1.erase(ie);
        //      }
        //  }
        //  if (flag) {
        //      ie++;
        //  }
        // }
    }
    // ASSERT(e1_s0.empty() && e1_s1.empty());
    s.push(num);
    while (!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }
}

int main() {
    #ifdef OFFLINE
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
    LARGE_INTEGER _frequency, _start_time, _end_time;
    QueryPerformanceFrequency(&_frequency);
    QueryPerformanceCounter(&_start_time);
    #endif

    ios_base::sync_with_stdio(false);
    solve();

    #ifdef OFFLINE
    QueryPerformanceCounter(&_end_time);
    cout << endl << "The algorithm takes " << (_end_time.QuadPart-_start_time.QuadPart)*1000/_frequency.QuadPart << " ms to complete the run." << endl;
    freopen("CON", "r", stdin);
    system("pause");
    #endif
    return 0;
}
