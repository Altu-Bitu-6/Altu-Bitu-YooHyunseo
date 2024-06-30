#include <iostream>
#include <algorithm>

using namespace std;
const int MAX_N = 7;

int n, m;            // 입력 n개 중 m개 선택하여 수열 생성
int sequence[MAX_N]; // 결과 수열 저장할 배열 
int input[MAX_N];    // n개의 입력 받을 배열

// sequence 출력 함수
void printSequence() {

    for (int i = 0; i < m; i++) {

        cout << sequence[i] << " ";
    }
    cout << "\n";
}

// 백트래킹 함수 - cnt: 한 수열에 들어가는 수를 현재 몇 개 골랐는가 
void backtrack(int cnt) {

    // cnt가 m개가 되면 백트래킹 종료
    if (cnt == m) {
        printSequence();
        return;
    }

    // n개의 입력들 중 선택할 요소를 탐색
    for (int i = 0; i < n; i++) {

        sequence[cnt] = input[i];   // sequence의 cnt번째 요소로 input의 값 순회하며 탐색
        backtrack(cnt + 1);         // cnt를 1 증가시킨 값을 전달하여 backtrack 재귀 호출
    }
}

int main() {

    // 입력
    cin >> n >> m;
    
    // n개의 수를 input 배열에 입력 
    for(int i=0; i<n; i++){
        cin >> input[i];
    }
    
    // 수열이 사전순으로 출력되어야 하므로 수열을 만들기 전 input을 먼저 오름차순으로 정렬
    sort(input, input + n);

    //한 수열에서 숫자는 중복되어도 되지만, 같은 수열이 중복되어 출력될 수는 없으므로 입력 배열을 정리함. 

    // algorithm 헤더의 unique함수 이용 - unique 함수를 통해 input의 중복 요소들이 배열의 맨 뒤로 이동함,
    // 이후 last에는 뒤로 이동한 중복 요소들의 첫 번째 위치에 해당하는 iterator가 반환됨. 
    int* last = unique(input, input + n);

    // input의 크기인 n을 재조정하여 중복된 요소들을 삭제함. 
    n = last - input;
    
    // 백트래킹
    backtrack(0);

    return 0;
}
