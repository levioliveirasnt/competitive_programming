#include <bits/stdc++.h>
#define int long long
using namespace std;

struct FenwickTree2D{

    int n, m;
    vector<vector<int>> BIT;

    FenwickTree(int N, int M){
        n = N;
        m = M;

        BIT.resize(n + 1);
        for(int i=1; i<=n; i++){
            BIT[i].resize(m + 1);
        }
    }

    int sum(int x, int y){
        
        int cur_sum = 0;
        for(int i=x; i > 0; i -= i & -i){
            for(int j=y; j > 0; j -= j & -j){
                cur_sum += BIT[i][j];
            }
        }
        return cur_sum;
    }

    void update(int x, int y, int v){

        for(int i=x; i <= n; i += i & -i){
            for(int j=y; j <= n; j += j & -j){
                BIT[i][j] += v;
            }
        }
    }
};
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    FenwickTree2D bit(n, n);
    vector<vector<int>> t(n+1, vector<int>(n + 1));

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin >> t[i][j];
            bit.update(i, j, t[i][j]);
        }
    }

    for(int i=0; i<q; i++){
        int type;
        cin >> type;

        if(type == 1){
            int x, y, v;
            cin >> x >> y >> v;

            bit.update(x, y, v - t[x][y]);
            t[x][y] = v;
            
        } else{
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            cout << bit.sum(x2, y2) + bit.sum(x1-1, y1-1) - bit.sum(x2, y1-1) - bit.sum(x1-1, y2) << "\n";
        }
    }
}
