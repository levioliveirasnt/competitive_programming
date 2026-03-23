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
int op, a, b, u, k;

struct SegTree{
    struct Node {
        int value, lazy;

        Node() : value(0) {}
        Node(int c) : value(c) {}    
    };
    Node join(Node a, Node b){
            return Node (a.value + b.value);
    }
    Node tree [4*maxn];

    void build(int node, int l, int r){
        if(l == r){
            tree[node].value = v[l];
            tree[node].lazy = 0;
            return;
        }
        int mid = (l+r) >> 1;

        build(2*node, l, mid);
        build(2*node+1, mid+1, r);
    }
    void update(int node, int l, int r, int val, int p, int q){
        if(p <= l && r <= q){
            tree[node].lazy += val;
            return;
        }
        if(l > q || r < p) return;

        int mid = (l+r) >> 1;
        
        update(2*node, l, mid, val, p, q);
        update(2*node+1, mid+1, r, val, p, q);
    }
    void lazyPropagation(int node, int l, int r){
        if(l < r){
            tree[2*node].lazy += tree[node].lazy;
            tree[2*node+1].lazy += tree[node].lazy;

            tree[node].lazy = 0;
        }
        return;
    }
    int querry(int node, int l, int r, int pos){
        if(l == r && l == pos){
            tree[node].value += tree[node].lazy;
            tree[node].lazy = 0;

            return tree[node].value;
        }

        lazyPropagation(node, l, r);

        int mid = (l+r) >> 1;
        if(pos <= mid) return querry(2*node, l, mid, pos);
        else           return querry(2*node+1, mid+1, r, pos);
    }
} baum;

int32_t main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n >> q;
    for(int i=1; i<=n; i++) cin >> v[i];

    baum.build(1, 1, n);

    while(q--){
        cin >> op;

        if(op == 1){
            cin >> a >> b >> u;
            baum.update(1, 1, n, u, a, b);
        }
        else{
            cin >> k;
            cout << baum.querry(1, 1, n, k) << endl;
        }
    }
}
