#include <iostream>
#include <set>

using namespace std;

int main(){
	
    int n, m;
    cin >> n >> m;
    
    set<string> s;
    string input;
    
    for(int i=0; i<n; i++){
        cin >> input;
        s.insert(input);
    }
    
    int check_cnt=0;
    
    for(int i=0; i<m; i++){
        cin >> input;
        if(s.find(input) != s.end()) check_cnt++;
    }
    
    cout << check_cnt << "\n";
    
}