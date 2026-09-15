#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    int n;
    cin >> n;

    vector<int> a(n + 1), b(n + 1);
    for(int i=1; i<=n; i++) cin >> a[i];
    for(int i=1; i<=n; i++) cin >> b[i];

    vector<int> nxta(n + 1), nxtb(n + 1);

    vector<pair<int,int>> ao, bo;
    for(int i=2; i<=n; i++){
        ao.push_back({a[i], i});
        bo.push_back({b[i], i});
    }

    a.push_back(1e9 + 10); // sentinelas
    b.push_back(1e9 + 10);

    sort(ao.begin(), ao.end());
    sort(bo.begin(), bo.end());

    int p = 0, cur = 2;
    while(p < n - 1){
        while(p < n - 1 and ao[p].first < b[cur]){
            nxta[ao[p].second] = cur;
            p++;
        }
        cur++;
    }
    p = 0, cur = 2;

    while(p < n - 1){
        while(p < n - 1 and bo[p].first <= a[cur]){
            nxtb[bo[p].second] = cur;
            p++;
        }
        cur++;
    }

    vector<int> pfxa(n + 1), pfxb(n + 1);
    pfxa[2] = a[2];
    pfxb[2] = b[2];

    for(int i=3; i<=n; i++){
        pfxa[i] = max(pfxa[i-1], a[i]);
        pfxb[i] = max(pfxb[i-1], b[i]);
    }

    stack<pair<int,int>> st;
    vector<int> next_a(n + 1), next_b(n + 1);

    st.push({1e9 + 10, n+1});

    for(int i=n; i>=2; i--){

        while(!st.empty() and st.top().first <= a[i]) st.pop();

        if(!st.empty()){
            next_a[i] = st.top().second;
        }

        st.push({a[i], i});
    }
    
    while(!st.empty()) st.pop();
    st.push({1e9 + 10, n+1});

    for(int i=n; i>=2; i--){

        while(!st.empty() and st.top().first <= b[i]) st.pop();

        if(!st.empty()){
            next_b[i] = st.top().second;
        }
        
        st.push({b[i], i});
    }
/*
A logica ta em ver, para cada valor, quantas celula ele vai ser o maximo
*/
    map<int, int> freq;

    for(int i=2; i<=n; i++){
        if(a[i] == pfxa[i] and pfxa[i-1] != a[i]){ // sou um maximo e e minha primeira ocorrencia
            int width = nxta[i] - 2;
            int height = next_a[i] - i;

            int cnt = width * height;
            freq[a[i]] += cnt;
        }
    }

    for(int i=2; i<=n; i++){
        if(b[i] == pfxb[i] and pfxb[i-1] != b[i]){ // sou um maximo e apareci pela primeira vez
            int width = next_b[i] - i;
            int height = nxtb[i] - 2;

            int cnt = width * height;
            freq[b[i]] += cnt;
        }
    }
    for(int i=1; i<=n; i++){
        freq[a[i]]++;
        freq[b[i]]++;

        if(i == 1) freq[a[i]]--;
    }
    
    int amt = 0, val = 0;
    for(auto [valor, vezes]:freq){
        if(vezes > amt){ // se os valores forem diferentes e um tiver mais que o outro
            amt = vezes;
            val = valor;
        } else if(vezes == amt){ // se os valor
            val = max(val, valor);
        }
    }
    cout << val << " " << amt;
}
