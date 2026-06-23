#include <bits/stdc++.h>
using namespace std;

struct FenwickTree{

    int n;
    vector<int> BIT;

    FenwickTree(int N){
        n = N;
        BIT.resize(n + 1);
    }

    void update(int i, int value){
        
        for(int j=i; j<=n; j += j & -j){
            BIT[j] += value;
        }
    }

    int sum(int i){
        
        int cur_sum = 0;
        for(int j=i; j > 0; j -= j & -j){
            cur_sum += BIT[j];
        }
        return cur_sum;
    }
};

int main(){

    int n;
    cin >> n;

    FenwickTree bit(n);

    int resp = 0;
    for(int i=0; i<n; i++){
        int x;
        cin >> x;

        resp += bit.sum(x);
        bit.update(x, 1);
    }
    cout << resp;
}
