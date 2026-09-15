#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;

    vector<int> a(2*n + 1), b(2*n + 1);
    for(int i=1; i<=n; i++){
        cin >> a[i];
        a[i + n] = a[i];
    }
    for(int i=1; i<=n; i++){
        cin >> b[i];
        b[i + n] = b[i];
    }

    vector<long long> pfx(2*n + 1);
    for(int i=1; i<=2*n; i++){
        pfx[i] = pfx[i-1] + b[i];
    }

    /*
    Se comecarmos no cara j, temos que, para derrotar um cara k com j <= k < j + n
        x[j] + (pfx[k-1] - pfx[j-1]) >= a[k]
    assim, temos
        x[j] >= pfx[j-1] + (a[k] - pfx[k - 1]);
    dessa forma, 
        x[j] = pfx[j-1] + max(j <= k < j + n de a[k] - pfx[k - 1])
    -- o segundo termo tem que ser o maior para ele conseguir derrotar todas as pessoas. 
    portanto, que mantamos uma janela de tamanho n que guarda o maior a[k] - pfx[k - 1] entre j e j - n + 1
    conseguimos implementar essa sliding window com deque
    */

    deque<int> dq;
    long long ans = 1e18;

    for(int i=1; i<=2*n; i++){

        // Tirar todos os caras que nao sao mais dessa janela
        while(!dq.empty() and dq.front() <= i - n)
            dq.pop_front();
            
        long long cur = a[i] - pfx[i - 1];
        // manter a janela tal que o topo tem o maior a[k] - pfx[k - 1];
        while(!dq.empty() and a[dq.back()] - pfx[dq.back() - 1] <= cur)
            dq.pop_back();

        dq.push_back(i);

        long long c = a[dq.front()] - pfx[dq.front() - 1];

        if(i >= n){ // se a janela tem tamanho maior que n
            int j = i - n + 1;
            ans = min(ans, pfx[j-1] + c);
        }
    }
    cout << ans;
}
