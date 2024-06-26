#include <iostream>             // 입출력 스트림 활용을 위한 클래스 포함 
#include <vector>               // 자료형 활용을 위한 벡터 클래스 포함

using namespace std;            // std 이름공간 선언

const int SIZE = 100;           // 좌표 평면 크기 정의 

// 방향: 우(0), 상(1), 좌(2), 하(3)
int dy[4] = { 0, -1, 0, 1 };    // 각 인덱스 방향으로 이동함에 따른 y 변위(세로 방향)
int dx[4] = { 1, 0, -1, 0 };    // 각 인덱스 방향으로 이동함에 따른 x 변위(가로 방향)

int cntSquares(vector<vector<bool>>& plane) {   // 1x1 정사각형의 개수 세는 함수. 
    int ans = 0;                                // 정사각형의 개수 정보 저장하는 변수. 
    for (int i = 0; i < SIZE; i++) {            // 좌표의 모든 세로줄 순회
        for (int j = 0; j < SIZE; j++) {        // 줄 안의 모든 점 순회 
            // 칸을 둘러싸는 네 꼭짓점이 모두 드레곤 커브에 속한 적 있는지 확인 
            if (plane[i][j] && plane[i + 1][j] && plane[i][j + 1] && plane[i + 1][j + 1]) {
                ans++;                          // 위 경우에 해당한다면 ans 1 증가
            }
        }
    }
    return ans;                 // count한 개수를 반환 
}

// 평면에 드래곤 커브를 표시하는 함수. 
void drawDragonCurve(vector<vector<bool>>& plane, int x, int y, int d, int g) { 
// 좌표평면 저장된 배들과 각 드래곤 커브에 대해 입력받은 모든 정보를 전달받음. 

// 최초의 0세대 커브를 그리고 시작. 
// 1세대 커브는 0세대 커브 부분과 0세대 커브가 90도 회전된 부분으로 구성. 
// n세대 커브를 그리기 위해선, n-1세대 커브에 그것을 회전한 커브를 붙이면 됨. 
// 세대가 아무리 높아지더라도, 결국 전체 커브는 방향을 적절하게 변화시킨 0세대 커브들(길이: 1)로 이루어짐. 
// n세대 커브의 고유한 부분을 그리기 위해, n-1세대가 구성요소인 0세대 커브들의 방향을 어떤 순서로 그려뒀는지 direct에 저장 후 이용. 
// 방향과 별개로, 새로운 커브는 항상 마지막으로 그린 위치로부터 시작되므로 해당 좌표 정보를 저장. 


    vector<int> direct;                                 // 방향 저장하는 벡터 direct. 
    // 
    plane[y][x] = plane[y + dy[d]][x + dx[d]] = true;   // 최초의 0세대 커브 그리기. 
    x += dx[d];                                         // 다음 세대의 드래곤커브를 그리기 위한 시작점의 x좌표 갱신. 
    y += dy[d];                                         // 다음 세대의 드래곤커브를 그리기 위한 시작점의 y좌표 갱신. 
    direct.push_back(d);                                // 최초로 그린 0세대 커브의 방향을 벡터에 저장. 
    
    while (g--) {                               // 1 ~ g 세대까지의 부분을 그리는 반복문
        int size_d = direct.size();             // 이전 세대의 0세대커브 개수를 저장.  
        for (int j = size_d - 1; j >= 0; j--) { // 이전 세대에서 그린 0세대커브의 방향들을 순회.  
            int next_d = (direct[j] + 1) % 4;   // 새로 그릴 방향은 이전에 그린 방향을 반시계방향 90도로 회전한 것. 
            x += dx[next_d];                    // 새로운 점으로 이동. 
            y += dy[next_d];                    // 새로운 점으로 이동. 
            plane[y][x] = true;                 // 점을 방문했다고 표시. 
            direct.push_back(next_d);           // 새로 그린 0세대커브의 방향을 direct 벡터에 추가. 
        }
    }
}

/*
* 규칙
* 0 세대: 0
* 1 세대: 0 1
* 2 세대: 0 1 2 1
* 3 세대: 0 1 2 1 2 3 2 1
* ...
* N 세대: concat((N-1세대), ((N-1세대 거꾸로) + 1)%4)
* 평면(좌측 상단이 (0, 0))에 드래곤 커브를 그린 후 정사각형의 개수를 계산
* 드래곤 커브는 평면 밖으로 나가지 않음으로 범위를 확인할 필요 없음
* 1. 0 세대의 드래곤 커브를 먼저 저장 (초기 조건)
* 2. 세대를 거듭하면서 드래곤 커브를 그림 (규칙을 파악하는 것이 중요)
* 3. 드래곤 커브가 그려진 평면 상의 정사각형의 개수 계산 (네 꼭짓점 확인)
*/

int main()  // 메인 프로그램 
{
    int n, x, y, d, g;  // 입력시 필요한 변수 선언. 
    vector<vector<bool>> plane(SIZE + 1, vector<bool>(SIZE + 1, false)); // 드래곤 커브 그릴 좌표평면 생성. 
                                                                         // 각 원소는 해당 좌표가 드래곤 커브에 속하는지의 여부를 표시. 
    
    // 입력
    cin >> n;
    
    // 연산 & 출력
    while (n--) {                           // n개의 드래곤 커브 그리기
        cin >> x >> y >> d >> g;            // 매 드래곤 커브에 대해 시작 좌표, 방향, 세대 정보 입력받음. 
        drawDragonCurve(plane, x, y, d, g); // 입력받은 정보들을 활용하여 드래곤 커브 그리는 함수 호출. 
    }
    
    cout << cntSquares(plane) << '\n';      // 좌표 상 조건에 해당하는 모든 정사각형의 개수 세고 출력하기. 
    return 0;                               // 프로그램 종료. 
}