#include <iostream>
#include <vector>

using namespace std;

void virusSearch(vector<vector<int>>& worm, vector<bool>& visited){ // 1로 시작하여 순회할 수 있는(연결된) 모든 노드를 순회
    
    vector<int> stack;
    
    stack.push_back(1);
    visited[1]= true;
    
    while(!stack.empty()){
        int this_com = stack.back();
        stack.pop_back();
        
        for(int i = 0; i < worm[this_com].size(); i++){
            int connected_com = worm[this_com][i];
            
            if(!visited[connected_com]){
                stack.push_back(connected_com);
                visited[connected_com] = true;
            }
        }
    }
}

int countVisited(vector<bool> visited){ // com1 제외 감염된 컴퓨터의 개수를 반환
    
    int cnt=0;
    
    for(int i=2; i<=visited.size()-1; i++){
    
        if(visited[i]==true){
            cnt++;
        }
    }
    return cnt;
}

int main() {
    int com_num, edge_num;
    cin >> com_num;
    cin >> edge_num;
    
    vector<vector<int>> worm(com_num + 1);
    vector<bool> visited(com_num+1, false);
    
    while(edge_num--){
        int first, second;
        cin >> first >> second;
        worm[first].push_back(second);
        worm[second].push_back(first); 
    }
    
    virusSearch(worm, visited); 
    cout << countVisited(visited) << '\n';
    
    return 0;
}