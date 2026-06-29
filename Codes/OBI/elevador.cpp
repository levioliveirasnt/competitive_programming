#include <bits/stdc++.h>
// A biblioteca bits já inclui a biblioteca cmath. 
// Sempre use a bits para programacao competitiva :)

using namespace std;

int main() {

    int n;
    cin >> n;

    vector<int> a(n);
    for(int i=0; i<n; i++) cin >> a[i];

    int resp = 0; 
    // Contador que guarda o tempo que vai levar pra percorrer os andares.

    for(int i=0; i<=n-2; i++){
        resp += abs(a[i] - a[i+1]);
    }

    cout << resp;
    return 0;
}
