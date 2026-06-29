#include <bits/stdc++.h>
// A biblioteca bits já inclui a biblioteca algorithm. 
// Sempre use a bits para programacao competitiva :)

using namespace std;

int main() {

    int P, O;
    cin >> P >> O;
    
    // Por padrão, na divisão a/b o C++ já pega o piso.
    cout << min(P/2, O/4);
    return 0;
}
