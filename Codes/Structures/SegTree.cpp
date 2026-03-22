#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define FOR(i, a, b) for(int i=a; i<b; i++)
#define pb push_back
#define fi first
#define se second
#define int long long
#define endl '\n'

using namespace std;
const int maxn = 2*1e5;

int v[maxn], n, q;
int op, a, b;

struct SegTree{
    struct Node {
        int value;

        Node() : value(0) {}
        Node(int c) : value(c) {}    
    };
    Node join(Node a, Node b){
            return Node (a.value + b.value);
    }
    Node tree [4*maxn];

    void build(int node, int l, int r){
        if(l == r){
            tree[node] = v[l];
            return;
        }
        int mid = (l+r) >> 1;

        build(2*node, l, mid);
        build(2*node+1, mid+1, r);

        tree[node] = join(tree[2*node], tree[2*node+1]);
    }
    void update(int node, int l, int r, int val, int pos){
        if(l == r && l == pos){
            tree[node] = val;
            return;
        }

        int mid = (l+r) >> 1;
        
        if(pos <= mid) update(2*node, l, mid, val, pos);
        else           update(2*node+1, mid+1, r, val, pos);

        tree[node] = join(tree[2*node], tree[2*node+1]);
    }
    int querry(int node, int l, int r, int p, int q){
        if(p <= l && r <= q) return tree[node].value;
        if(l > q || r < p) return 0;

        int mid = (l+r) >> 1;

        return querry(2*node, l, mid, p, q) + querry(2*node+1, mid+1, r, p, q);
    }
} baum;

int32_t main(){
    cin >> n >> q;
    for(int i=1; i<=n; i++) cin >> v[i];

    baum.build(1, 1, n);

    while(q--){
        cin >> op >> a >> b;

        if(op == 1) baum.update(1, 1, n, b, a);
        else cout << baum.querry(1, 1, n, a, b) << endl;
    }
}
