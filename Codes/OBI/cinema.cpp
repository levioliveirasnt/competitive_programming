#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, C;
    cin >> N >> M >> C;

    vector<int> T(N), H(M);

    for (int i = 0; i < N; i++)
        cin >> T[i];
    for (int j = 0; j < M; j++)
        cin >> H[j];
  
    vector<int> ans(M, 0);
    // i = ponteiro para a primeira pessoa que ainda não foi alocada
    int i = 0;
    // percorremos as sessões em ordem
    for (int j = 0; j < M; j++) {
        // Enquanto a pessoa puder entrar e ainda houver espaço na sessão
        while (i < N && T[i] <= H[j] && ans[j] < C) {
            ans[j]++;
            i++;
        }
    }
    for (int j = 0; j < M; j++) {
        cout << ans[j] << ' ';
    }
    return 0;
}
