#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
const int INF = 1000; // 최대 V-1개의 간선을 지나게 됨 -> V * (가중치 최대값)

void floydWarshall(int n, vector<vector<int>> &graph) {  // 플로이드 워셜
    
    for (int k = 1; k <= n; k++) {                       // 중간 정점
    
        for (int i = 1; i <= n; i++) {                   // 출발 정점
        
            for (int j = 1; j <= n; j++) {               // 도착 정점
            
                int cost = graph[i][k] + graph[k][j];   
                graph[i][j] = min(graph[i][j], cost);    // 새로구한 cost를 이용하여 graph[i][j]를 갱신
            }
        }
    }
}

bool checkStudent(int k, int n, vector<vector<int>> &graph){        // k번 학생의 순서가 정해지는지의 여부를 판별하여 반환
    
    for (int i = 1; i <= n; i++) {                        // 1~n을 i로 순회하며
        if (graph[k][i] == INF && graph[i][k] == INF) {   // k와 어떤 i의 대소관계 정보가 없다면
            return false;                                 // k번 학생의 순서를 알 수 없다고 간주. 
        }
    }
    return true;    // 모든 i에 대해 위 조건이 해당하지 않는 경우 순서가 정해지는 경우이므로 true 반환. 
}

int main() {
    
    int n, m, a, b;

    cin >> n >> m;
    
    vector<vector<int>> graph( n + 1, vector<int>(n + 1, INF) );    // 학생들 키의 관계정보를 저장하는 2차원 인접행렬 생성

    for (int i = 1; i <= n; i++) {
        graph[i][i] = 0;
    }
    
    while (m--) {
        cin >> a >> b;               
        graph[a][b] = 1;                // a보다 b가 크다면 인접행렬의 해당 칸에 1 저장
    }

    floydWarshall(n, graph);            // 입력 정보를 이용하여 플로이드워셜 알고리즘 적용
    
    int cnt = 0;
    
    for(int i=1; i<=n; i++){
        if(checkStudent(i, n, graph)){  // i번 학생의 순서를 알 수 있다면
            cnt++;                      // cnt를 증가시킴
        }
    }
    
    cout << cnt;    // 몇 명의 순서를 알 수 있는지 출력

    return 0;
}

