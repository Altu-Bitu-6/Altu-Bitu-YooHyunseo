#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> ci;
const int INF = 1e5;        // 최대 V-1개의 간선을 지나게 됨 -> V * (가중치 최대값) 

vector<int> dijkstra(int start, int v, vector<vector<ci>> &graph) { // start 노드에서 다른 모든 노드로의 최소시간 경로 반환
    
    vector<int> dist(v + 1, INF);                   // START에서 다른 노드로 향하는 경로
    // 현재 탐색하는 중간 정점까지의 최단 경로
    priority_queue<ci, vector<ci>, greater<>> pq;   // first: 시작점으로부터의 소요 시간, second: 정점

    dist[start] = 0;        // start 마을까지의 시간 = 0
    pq.push({0, start});    // 우선순위 큐에 시작원소 삽입
    
    while (!pq.empty()) {
        
        int w_time = pq.top().first;    // 현재 정점까지의 소요시간
        int node = pq.top().second;     // 현재 탐색하려는 정점
        pq.pop();                       // 저장한 원소는 큐에서 제거

        if (w_time < dist[node]) {      // 이미 더 큰 값으로 기록된 정점 -> CONTINUE
            continue;   
        }

        for (int i = 0; i < graph[node].size(); i++) {
            
            int next_node = graph[node][i].first;    // node에 연결된 정점 순회

            // 시작점으로부터 현재 node를 거쳐 다음 정점까지 가는 소요시간
            int next_w_time = w_time + graph[node][i].second;
            
            if (next_w_time < dist[next_node]) {    // 최소 시간 값이 갱신된다면
                
                dist[next_node] = next_w_time;
                pq.push({next_w_time, next_node});
            }
        }
    }
    return dist;
}

int main() {
    
    int n, m, x, a, b, t;
    
    cin >> n >> m >> x; // n: 마을=학생의 수, m: 도로의 개수, x: 파티하는 마을
    
    vector<vector<ci>> graph(n + 1, vector<ci>(0)); // 도로 정보 저장하는 인접 리스트 선언
    
    while(m--){                     // m개의 도로에 대해(방향 있음)
        cin >> a >> b >> t;         // 각각 도로의 정보 입력받아
        graph[a].push_back({b, t}); // 시작 마을 인덱스의 방향 graph에 저장
    }
    
    vector<int> time_FROM = dijkstra(x, n, graph);      // x 출발하여 -> 각자 마을 도착하는 여려 경로들 중 최소 시간 저장
    
    int max_time = 0;

    for (int i = 1; i <= n; i++) {  // n개의 마을 순회
        
        vector<int> time_TO = dijkstra(i, n, graph);    // 각자 마을(i)에서 -> x에 도착하는 여려 경로들 중 최소 시간 저장
        
        if( (time_TO[x] + time_FROM[i] ) > max_time) {  // (time_TO[x] + time_FROM[i]) : i마을 에서의 최소왕복시간
            
            max_time = time_FROM[i]+time_TO[x];         // 최소왕복시간이 최대인 경우 저장
        }
    }
    
    cout << max_time;   // 왕복하여 가장 오래 걸리는 경우는 몇 시간인지 출력
    
    return 0;
}