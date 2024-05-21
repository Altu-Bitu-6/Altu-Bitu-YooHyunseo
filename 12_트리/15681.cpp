#include <iostream>
#include <map>
#include <vector>

using namespace std;

void dfs(int node, int parent, map<int, vector<int>>& tree, vector<vector<int>>& adj, vector<int>& node_cnt) {
    
    node_cnt[node] = 1;                             // 자기 자신을 포함하므로 리프노드의 서브트리 원소 개수는 1

    for (int neighbor : adj[node]) {                // 인접리스트로 연결된 원소 순회

        if (neighbor == parent) {
            continue;                               
        }
        tree[node].push_back(neighbor);             // 부모 노드가 아니면 자식 노드로 추가 가능

        dfs(neighbor, node, tree, adj, node_cnt);   // 자식 노드로 DFS 재귀 호출
        node_cnt[node] += node_cnt[neighbor];       // 자식 노드의 서브트리 크기를 node_cnt 배열의 node번 인덱스에 더함
                                                    // 자식 노드의 node_cnt 값을 이용해 부모 노드의 node_cnt값 구성 
    }
}



int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
    
    int n, r, q;
    cin >> n >> r >> q;
    
    map<int, vector<int>> tree;         // 정점 n개, 간선 n-1개
    vector<vector<int>> adj(n + 1);     // 인접 리스트 선언
    vector<int> node_cnt(n, 0);         // 배열의 인덱스 번 노드를 루트로 갖는 서브트리의 정점 개수 저장
    
    for(int i=0; i<n-1; i++){           // n-1개의 간선에 대해 무방향 인접리스트 구성 
        
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        
    }
    
    int root = r; 
    dfs(root, -1, tree, adj, node_cnt); // DFS를 통해 r이 루트인 트리 구성, 동시에 다이나믹 프로그래밍으로 node_cnt 갱신
    
    while(q--){
        
        int query_root;
        cin >> root;
        cout<< node_cnt[root] << '\n';  // 배열에 저장된 값 출력 
        
    }
}