#include <bits/stdc++.h>
using namespace std;

int main(){

    const int inf = 1e9;

    int n, m, q, k;
    cin >> n >> m >> q >> k;
    
    vector<vector<int>> balls(m + 1); // Matriz que guarda as operacoes
    vector<pair<int,int>> line(n + 1, {inf, inf}); // Guarda, para cada linha, a menor coluna pintada e sua cor
    
    for(int Q=0; Q<q; Q++){
        char type;
        cin >> type;

        if(type == 'c'){
            int j, cor;
            cin >> j >> cor;

            if(balls[j].size() == n){ 
                // Ja colocamos todas as bolinhas que cabiam
                cout << "-1\n";
            } else{ 
                // Colocamos a bolinha de cor K
                balls[j].push_back(cor);

                // Temos que atualizar a linha que o ultimo ficou.
                int linha = n - (balls[j].size() - 1);
                line[linha] = min(line[linha], {j, cor});
                
                cout << linha << '\n';
            }
        }
        else if(type == 'l'){
            int linha;
            cin >> linha;

            if(line[linha] == make_pair(inf, inf)){
                // Linha esta vazia
                cout << "-1\n";
            } else{
                // Resposta e a cor
                cout << line[linha].first << " " << line[linha].second << '\n';
            }
        } 
        else{
            int i, j;
            cin >> i >> j;

            if(balls[j].size() <= n - i){
                // Nao colocamos bolinhas o suficiente
                cout << "-1\n";
            } else{
                // A linha N tem indice 0, a linha N - 1 tem indice 1. Se k = N - i, a linha i == N - k tem indice K
                int cor = balls[j][n - i];
                cout << cor << '\n';
            }
        }
    }
}
