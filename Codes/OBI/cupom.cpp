#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> v(4);
    for(int i=0; i<4; i++) cin >> v[i];

    sort(v.begin(), v.end());

    int k;
    cin >> k;

    int op1 = (v[1] - v[0] <= k) + (v[3] - v[2] <= k);
    int op2 = (v[2] - v[1] <= k);

    cout << max(op1, op2);
    return 0;
}
