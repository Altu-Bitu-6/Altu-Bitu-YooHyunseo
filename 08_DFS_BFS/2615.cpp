// 2615번 오목: https://www.acmicpc.net/problem/2615

#include <iostream>     // 입출력 스트림 클래스 호출
#include <vector>       // 벡터 컨테이너 사용을 위한 클래스 호출

using namespace std;    // 함수 간편 사용을 위한 이름공간 선언


typedef vector<vector<int>> matrix; // 바둑판과 같은 정수형 이차원 벡터 type definition 
const int SIZE = 20, EMPTY = 0;     // 바둑판 크기에 대한 상수 SIZE와 특정 칸에 바둑돌이 없을 경우에 대한 상수 EMPTY 정의 


// 방향에 따른 좌표 증가량
// 맨 왼쪽 위 돌을 기준으로 검사하기 때문에 오른쪽+아래쪽으로 향하는 방향만 정의
const vector<int> dx = {-1, 0, 1, 1};   // 현재 위치에 대하여 북동, 동, 남동, 남쪽 칸에 위치한 바둑돌의 상대적인 x, y 위치를
const vector<int> dy = {1, 1, 1, 0};    // 각각 dx와 dy의 0,1,2,3 인덱스에 정의


bool isValid(matrix &board, int x, int y, int color) {                          // 전달받은 바둑판과 칸 위치, 돌 색깔
    return (x > 0 && x < SIZE && y > 0 && y < SIZE && board[x][y] == color);    // 바둑판 범위 내에 알맞은 종류의 바둑돌이 놓여있다면 true 반환 
}


bool checkWin(matrix &board, int x, int y) {                // 해당 좌표(x, y)부터 연속적으로 5알이 놓이는지 확인한다.


    int color = board[x][y];                                // (x,y) 좌표에 위치한 돌 종류를 기준 색으로 저장

    for (int idx = 0; idx < 4; idx++) {                     // 인덱스로 네 방향의 바둑돌 순회

        int cnt = 1;                                        // cnt: 같은 방향에 놓인 같은 색 돌의 수
        int prev_x = x - dx[idx], prev_y = y - dy[idx];     // idx번째 방향의 이전 바둑돌 위치 저장
        int next_x = x + dx[idx], next_y = y + dy[idx];     // idx번째 방향의 다음 바둑돌 위치 저장

        
        if (isValid(board, prev_x, prev_y, color)) {        // 같은 방향에서 그 이전에도 같은 색 돌이 있었다면 패스 
            continue;                                       // (-> 여섯 알 이상 놓이는 경우를 제외하기 위함)
        }

        
        while (isValid(board, next_x, next_y, color) && cnt < 6) {  // 연속적으로 놓인 5알이 같은 색인지 확인
            next_x += dx[idx];                                      // 같은 방향의 다음 바둑돌로 X좌표 이동
            next_y += dy[idx];                                      // 같은 방향의 다음 바둑돌로 Y좌표 이동
            cnt++;                                                  // 연속으로 valid한 바둑돌의 개수 count
        }
        
        if (cnt == 5) {         // cnt가 5일 때만 true 리턴 
            return true;        // (-> 다섯 알보다 적거나 다섯 알보다 많이 놓이는 경우를 제외)
        }
    }
    return false;               // 위 조건들에 해당하지 않는 경우 false 리턴 
}

int main() {

    // 입력
    matrix board(SIZE, vector<int>(SIZE, 0));  // 바둑판

    for (int i = 1; i < SIZE; i++)             // 모든 행 순회 (1~19)
        for (int j = 1; j < SIZE; j++)         // 한 행의 각 원소 순회 (1~19)
            cin >> board[i][j];                // 각 칸의 상태 입력


    // 연산 및 출력
    for (int y = 1; y < SIZE; y++) {        // 모든 행 순회 (1~19)
        for (int x = 1; x < SIZE; x++) {    // 한 행의 각 원소 순회 (1~19)
            
            if (board[x][y] == EMPTY) {     // 빈 칸이면
                continue;                   // 패스
            }


                                            // checkWin: 해당 좌표(x, y)부터 연속적으로 5알이 놓였다면 정답 출력
            if (checkWin(board, x, y)) {    // 순회 중인 칸에 대해 checkWin함수 호출하여 true가 반환되면

                cout << board[x][y] << '\n' // 승리한 돌의 종류 출력
                     << x << ' ' << y;      // 빈칸을 사이에 두고 해당 칸의 행과 열의 정보를 출력
                return 0;                   // 프로그램 종료
            }
        }
    }

    cout << 0;      // checkwin이 false를 반환하면 0 출력
    return 0;       //프로그램 종료
}