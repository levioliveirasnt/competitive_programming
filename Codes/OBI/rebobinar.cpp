#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, k, q;
    cin >> n >> k >> q;

    vector<pair<int,int>> queries;
    for(int i=0; i<q; i++){
        int l, r;
        cin >> l >> r;

        queries.push_back({l,r});
    }

    int cur = k;
    for(int i=q-1; i>=0; i--){
        auto [l,r] = queries[i];
        
        if(l <= cur and cur <= r){ // Essa operacao nos afetou
            cur = r + l - cur;
        } // else continue -> Nao mudou nada
    }
    cout << cur;
    return 0;
}
