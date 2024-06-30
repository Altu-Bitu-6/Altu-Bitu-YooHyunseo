#include <iostream>             // 입출력을 위한 클래스 포함
#include <vector>               // 벡터 자료형 사용하기 위해 클래스 포함
#include <string>               // string 사용하기 위해 클래스 포함
using namespace std;            // std에 정의된 함수를 편리하게 사용하기 위해 선언

vector<string> li;              // 톱니바퀴들이 회전하며 매 톱니마다 가진 자기장의 양상을 갱신하는 string들의 벡터
vector<pair<int, int> > stack;  // 회전에 대한 한 번의 입력에 영향을 받는 톱니바퀴들의 회전 여부를 저장하고, stack과 같이 최근에 들어온 원소부터 빼내며 정보를 갱신하는 벡터
vector<int> visited;            // check_rotation을 재귀적으로 호출할 때 이전에 방문하여 stack에 추가된 톱니바퀴인지의 여부를 저장하는 visited 벡터

void check_rotation(int current_num, int current_dir) {                     // 돌릴 톱니바퀴의 인덱스와 방향을 전달받아 주변의 톱니바퀴들이 영향받아 회전할 경우 그것을 stack에 추가하는 함수
    if (current_num - 1 >= 0 && visited[current_num - 1] == 0) {            // 전달받은 인덱스의 왼쪽 톱니바퀴가 존재하며 아직 방문하지 않은 것인 경우에만 적용
        if (li[current_num][6] != li[current_num - 1][2]) {                 // 현재와 왼쪽 톱니바퀴가 맞닿아 있는 면이 서로 다른 극이라면
            stack.push_back(make_pair(current_num - 1, current_dir * -1));  // 왼쪽 톱니바퀴를 현재와반대로 회전한다는 원소를 stack에 저장
            visited[current_num - 1] = 1;                                   // 왼쪽 톱니바퀴를 방문한 것으로 설정
            check_rotation(current_num - 1, current_dir * -1);              // 왼쪽 톱니바퀴를 반대로 회전할 때 영향받는 톱니바퀴가 더 있는지 재귀적으로 확인
        }
    }
    if (current_num + 1 < li.size() && visited[current_num + 1] == 0) {     // 전달받은 인덱스의 오른쪽 톱니바퀴가 존재하며 아직 방문하지 않은 것인 경우에만 적용
        if (li[current_num][2] != li[current_num + 1][6]) {                 // 현재와 오른쪽 톱니바퀴가 맞닿아 있는 면이 서로 다른 극이라면
            stack.push_back(make_pair(current_num + 1, current_dir * -1));  // 오른쪽 톱니바퀴를 현재와 반대로 회전한다는 원소를 stack에 저장
            visited[current_num + 1] = 1;                                   // 오른쪽 톱니바퀴를 방문한 것으로 설정
            check_rotation(current_num + 1, current_dir * -1);              // 오른쪽 톱니바퀴를 반대로 회전할 때 영향받는 톱니바퀴가 더 있는지 재귀적으로 확인
        }
    }
}

int main() {                        // 프로그램이 실행되는 main 함수 
    int t;                          // 톱니바퀴의 개수 t 선언
    int k;                          // 톱니바퀴 회전 횟수 k 선언

    cin >> t;                       // 톱니바퀴의 개수 T 입력

    li.resize(t);                   // 톱니바퀴 개수만큼 벡터 li를 resize
    for (int i = 0; i < t; ++i)     // t개의 li 원소 순회하며 
        cin >> li[i];               // li[i]에 톱니바퀴의 자기장 상태 string으로 입력

    cin >> k;                                               // 회전 횟수 K 입력
    for (int i = 0; i < k; ++i) {                           // k번의 회전에 대한 각 케이스 시작
        int num, direction;                                 // 금번에 회전시킨 톱니바퀴의 번호, 방향 변수 선언 
        cin >> num >> direction;                            // 회전시킬 톱니바퀴와 회전 방향 입력 (1이면 시계 방항, -1이면 반시계 방향)
        stack.clear();                                      // stack의 원소를 전부 지음
        stack.push_back(make_pair(num - 1, direction));     // stack에 pair<번호,방향> 원소를 삽입함(톱니바퀴를 가리키는 인덱스는 num-1)
        visited.assign(t, 0);                               // visited 벡터에 t개만큼 0을 초기화
        visited[num - 1] = 1;                               // visited의 마지막 원소를 1로 설정
        check_rotation(num - 1, direction);                 // check_rotation 함수를 호출하여 현재 회전에 대한 톱니바퀴들의 변동 정보 갱신

        while (!stack.empty()) {                            // 회전에 영향을 받는 모든 톱니바퀴들의 자기장 정보를 갱신함
            pair<int, int> top = stack.back();              // top에 stack의 가장 마지막 원소 저장
            stack.pop_back();                               // top에 저장한 원소를 pop
            int tmp_num = top.first;                        // 돌려야 할 톱니바퀴의 인덱스를 tmp_num에 저장
            int tmp_dir = top.second;                       // 돌릴 방향(1 혹은 -1)을 tmp_dir에 저장
            if (tmp_dir == 1) {                                                // 시계방향으로 돌려야 할 경우
                li[tmp_num] = li[tmp_num].back() + li[tmp_num].substr(0, 7);   // 가장 뒤에 있던 문자를 앞에다 붙임(10시 방향 톱니를 12시로)
            } else {                                                           // 반시계방향으로 돌려야 할 경우
                li[tmp_num] = li[tmp_num].substr(1) + li[tmp_num][0];          // 가장 앞에 있던 문자를 뒤에다 붙임(12시 방향 톱니를 10시로)
            }
        }
    }

    int cnt = 0;                    // 답을 저장할 cnt를 0으로 선언
    for (int i = 0; i < t; ++i) {   // t개의 톱니바퀴들을 확인
        if (li[i][0] == '1') {      // 12시 방향 톱니가 S극이라면
            cnt++;                  // cnt에 카운팅
        }
    }

    cout << cnt << endl;            // cnt 출력

    return 0;                       // 프로그램 종료
}
