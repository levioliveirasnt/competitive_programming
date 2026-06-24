#include <bits/stdc++.h>
using namespace std;

const int MAXM = 1e3 + 1, INF = 1e9;
int V[MAXM][MAXM];

struct Node{
    int value;

    Node(int m = 0) : value(m) {}

    Node operator + (Node other){
        return Node(max(this->value, other.value));
    }
};

struct SegmentTree2D{
    int n, m;
    vector<vector<Node>> tree;
    vector<vector<int>> arr;

    SegmentTree2D(int N, int M, int A[][MAXM]){
        n = N;
        m = M;

        arr.resize(n + 1);
        for(int i=1; i<=n; i++){
            arr[i].resize(m + 1);
        }

        tree.resize(4 * n + 1);
        for(int i=1; i <= 4 * n; i++){
            tree[i].resize(4 * m + 1);
        }

        buildX(A, 1, 1, n); // construir logo essa bomba de arvore
    }
    
    void buildY(int A[][MAXM], int nodex, int lx, int rx, int nodey, int ly, int ry){
        if(ly == ry){ // se estamos numa folha 
            if(lx == rx){ // matriz 1x1
                tree[nodex][nodey].value = A[lx][ly];
                arr[lx][ly] = A[lx][ly];
            } else{ // tenho que juntar somando em cima
                tree[nodex][nodey] = tree[2*nodex][nodey] + tree[2*nodex + 1][nodey];
            }
            return;
        }

        int midy = (ly + ry) >> 1;
        
        buildY(A, nodex, lx, rx, 2*nodey, ly, midy);
        buildY(A, nodex, lx, rx, 2*nodey + 1, midy + 1, ry);

        tree[nodex][nodey] = tree[nodex][2*nodey] + tree[nodex][2*nodey + 1];
    }
    void buildX(int A[][MAXM], int nodex, int lx, int rx){
        if(lx == rx){ // se estamos numa folha

            buildY(A, nodex, lx, rx, 1, 1, m); // construir minha seg
            return;
        }

        int midx = (lx + rx) >> 1;

        buildX(A, 2*nodex, lx, midx);
        buildX(A, 2*nodex + 1, midx + 1, rx);

        buildY(A, nodex, lx, rx, 1, 1, m);
    }
    void updateY(int nodex, int lx, int rx, int nodey, int ly, int ry, int y, int z){
        
        if(ly == ry){
            if(lx == rx) tree[nodex][nodey].value = z;
            else tree[nodex][nodey] = tree[2*nodex][nodey] + tree[2*nodex + 1][nodey];
            
            return;
        }

        int midy = (ly + ry) >> 1;

        if(y <= midy) updateY(nodex, lx, rx, 2*nodey, ly, midy, y, z);
        else updateY(nodex, lx, rx, 2*nodey+1, midy+1, ry, y, z);

        tree[nodex][nodey] = tree[nodex][2*nodey] + tree[nodex][2*nodey + 1];
    }
    void updateX(int nodex, int lx, int rx, int x, int y, int z){
        if(lx == rx){
            
            updateY(nodex, lx, rx, 1, 1, m, y, z);
            return;
        }

        int midx = (lx + rx) >> 1;

        if(x <= midx) updateX(2*nodex, lx, midx, x, y, z);
        else updateX(2*nodex + 1, midx + 1, rx, x, y, z);

        updateY(nodex, lx, rx, 1, 1, m, y, z);
    }
    Node queryY(int nodex, int nodey, int ly, int ry, int py, int qy){
        if(py > ry or qy < ly) return Node(-INF); // nao ta contando esse bombudo
        if(py <= ly and ry <= qy) return tree[nodex][nodey];

        int midy = (ly + ry) >> 1;

        return queryY(nodex, 2*nodey, ly, midy, py, qy) + queryY(nodex, 2*nodey + 1, midy + 1, ry, py, qy);
    }
    Node queryX(int nodex, int lx, int rx, int px, int qx, int py, int qy){
        if(px > rx or qx < lx) return Node(-INF); // nao ta contando esse bombudo
        if(px <= lx and rx <= qx) return queryY(nodex, 1, 1, m, py, qy);

        int midx = (lx + rx) >> 1;

        return queryX(2*nodex, lx, midx, px, qx, py, qy) + queryX(2*nodex + 1, midx + 1, rx, px, qx, py, qy);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    int n, m, q;
    cin >> n >> m >> q;

    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            cin >> V[i][j];
        }
    }

    SegmentTree2D arbre(n, m, V);

    while(q--){
        int type;
        cin >> type;

        if(type == 1){
            int x, y, z;
            cin >> x >> y >> z;

            arbre.updateX(1, 1, n, x, y, z);
        } else{
            int px, py, qx, qy;
            cin >> px >> py >> qx >> qy;

            cout << arbre.queryX(1, 1, n, px, qx, py, qy).value << '\n';
        }
    }
}
