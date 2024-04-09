#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> relations;  // 인접 리스트
vector<int> chon;               // 인덱스th 사람이 입력받은 사람에서 몇 촌 떨어져 있는지 저장

int calChonSu(int person1, int person2) {
    vector<bool> visited(chon.size(), false);   // 방문 여부 저장 배열
    queue<int> q;                               // 순회 시에 사용할 큐

    q.push(person1);
    visited[person1] = true;

    while (!q.empty()) {

        int cur_p = q.front();                  // cur_p: 현재 확인하는 노드
        q.pop();

        for (int i = 0; i < relations[cur_p].size(); i++) {
            int ilchon = relations[cur_p][i];   // ilchon: cur_p와 1촌 사이에 있는 노드

            if (!visited[ilchon]) {
                chon[ilchon] = chon[cur_p] + 1;
                visited[ilchon] = true;
                q.push(ilchon);

                if (ilchon == person2) {
                    return chon[ilchon];
                }
            }
        }
    }

    return -1;  // person2와 같은 ilchon이 없었다면 -1 반환
}

int main()
{
    int n, person1, person2, m;
    cin >> n;
    cin >> person1 >> person2;
    cin >> m;
    
    relations.resize(n+1);
    chon.resize(n+1,0);
    
    while(m--){
        
        int parent, child;
        
        cin >> parent >> child;
        relations[parent].push_back(child); // 양방향 노드 연결
        relations[child].push_back(parent);
    }
    
    cout << calChonSu(person1, person2);
}