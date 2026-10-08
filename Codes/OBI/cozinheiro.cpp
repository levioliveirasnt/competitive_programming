#include <bits/stdc++.h>
using namespace std;

int main(){
  int n;
  cin >> n;

  vector<int> com;
  vector<int> sem;

  for(int i=1; i<=n; i++){
    int v;
    cin >> v;

    if(v == 0) sem.push_back(i);
    else com.push_back(i);
  }

  cout << sem.size() << "\n";
  for(int i=0; i<sem.size(); i++) cout << sem[i] << [i == sem.size() - 1]" \n";

  cout << com.size() << "\n";
  for(int i=0; i<com.size(); i++) cout << sem[i] << [i == com.size() - 1]" \n";

  return 0;
}
