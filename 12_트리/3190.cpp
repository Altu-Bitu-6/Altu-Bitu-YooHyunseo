#include <iostream>
#include <vector>
#include <deque>
#include <map>

using namespace std;        // std 이름공간 선언
typedef pair<int, int> ci;  // 정수 페어를 'ci'로 정의

const int EMPTY = 0;    // board에 실제로 저장되어 각 칸의 정보를 나타내는 상수값. 빈 칸인 경우
const int APPLE = 1;    // 사과가 있는 칸일 경우
const int SNAKE = 2;    // 뱀이 차지한 칸일 경우


int playGame(int n, vector<vector<int>> &board, map<int, char> &cmd) {  // 게임을 실행한 후 종료 시간을 반환

    // 동(→), 남(↓), 서(←), 북(↑)
    int dx[4] = {0, -1, 0, 1};  // 동(0), 남(1), 서(2), 북(3) || 각각 방향(인덱스)으로 이동할때의 x 변위
    int dy[4] = {1, 0, -1, 0};  // 동(0), 남(1), 서(2), 북(3) || 각각 방향(인덱스)으로 이동할때의 y 변위

    // 초기화
    deque<ci> snake;            // 뱀의 머리~꼬리 위치 정보를 나타낼 deque(front~back), 안엔 뱀이 차지한 칸들의 위치 정보가 담김
    snake.push_front({1, 1});   // 게임 시작 시점 뱀의 머리가 위치하는 칸 (1,1)
    board[1][1] = SNAKE;        // 보드의 해당 칸은 뱀이 차지함. 

    int time = 0;               // 현재 시간
    int dir = 0;                // 현재 방향

    while (true) {

        // 방향 변환 정보가 있다면
        if (cmd[time] == 'L') {         // 왼쪽 회전
            dir = (dir + 1) % 4;        // 현재 방향을 시계방향으로 전환
        } else if (cmd[time] == 'D') {  // 오른쪽 회전
            dir = (dir + 3) % 4;        // 현재 방향을 반시계방향으로 전환
        }

        // 시간 증가
        time++;

        // 다음에 뱀의 머리가 위치하게 될 칸 좌표 계산
        int nx = snake.front().first + dx[dir];     // 현재 머리의 x좌표 + dir로 1칸 전진할 때의 x변위
        int ny = snake.front().second + dy[dir];    // 현재 머리의 y좌표 + dir로 1칸 전진할 때의 y변위

        if (nx < 1 || nx > n || ny < 1 || ny > n || board[nx][ny] == SNAKE) {   // 해당 칸으로 이동했을 때 게임 지속가능 여부를 판별
            break;                                                              // 벽에 부딪히거나, 자기자신의 몸에 부딪히면 반복문 종료 후 시점 반환
        }

        // 이동
        snake.push_front({nx, ny});                 // 이동할 칸을 snake에 포함

        if (board[nx][ny] != APPLE) {               // 이동한 칸에 사과가 없다면(몸길이가 그대로라면) 

            ci tail = snake.back();                 // tail 변수에 snake의 가장 뒷 칸 정보 일시적으로 저장
            board[tail.first][tail.second] = EMPTY; // tail이 있던 칸의 보드 정보를 업데이트 (EMPTY == 0)
            snake.pop_back();                       // 그 칸은 더 이상 snake에 속하지 않음!
        }
        board[nx][ny] = SNAKE;                      // 이동할 칸의 보드 정보를 업데이트 (SNAKE == 2)
    }

    return time;                                    // 게임이 끝난 시점 정보를 main으로 반환
}


/**
 * [백준 3190: 뱀] https://www.acmicpc.net/problem/3190
 * 뱀의 머리와 꼬리 좌표에 대한 접근 필요 -> deque 사용!
 * 사과가 존재하면 board의 해당 위치를 APPLE(1), 뱀이 존재하면 SNAKE(2), 아무것도 없으면 EMPTY(0)로 설정
 * 1. 초기화 시 뱀의 첫 시작 좌표인 {1, 1} 추가
 * 2. 뱀의 방향이 바뀌면 방향을 업데이트하고, 새로운 뱀의 머리 좌표를 {nx, ny}로 설정
 * 3. 게임 시간 업데이트(time++)
 * 4. 뱀의 머리가 벽이나 몸에 부딪히면 while문 종료
 * 5-1. 새로 이동한 좌표를 deque 앞부분에 추가
 * 5-2. 새로 이동한 좌표에 사과가 없으면 기존 꼬리 좌표 값을 EMPTY(0)로 바꾸고 deque에서 pop
 *   -> 사과가 있으면 몸길이가 1 늘어나지만 사과가 없으면 몸길이가 변하지 않으므로
 * 6. 새로 이동한 좌표를 SNAKE(2)로 표시
*/

int main() {

    int n, k, x, y, l, time;    // 입력 시 필요한 변수 선언
    
    char command;               // 일시적으로 방향 정보를 저장하는 변수
                                // time은 command를 실행할 시점 정보를 저장하는 변수

    //입력
    cin >> n >> k;                                                  // 보드의 크기 n = ( x, y 범위: 1~n ), 사과의 개수 k 입력
    vector<vector<int>> board(n + 1, vector<int>(n + 1, EMPTY));    // 필요한 크기만큼의 이차원 벡터 보드 생성, 초기화 (EMPTY == 0)

    while (k--) {               // k줄 동안
        cin >> x >> y;          // 사과의 x 좌표와 y 좌표를 입력 
        board[x][y] = APPLE;    // 사과의 위치 표시 (APPLE == 1)
    }

    cin >> l;                   // 뱀의 방향 변환 횟수 입력
    map<int, char> cmd;         // 방향 변환 정보를 map에 저장

    while (l--) {               // l줄 동안
        cin >> time >> command; // 뱀의 방향 변환 정보 (시점, 방향) 입력
        cmd[time] = command;    // 뱀의 방향 변환 정보 (시점, 방향) map에 저장
    }

    // 연산 및 출력
    cout << playGame(n, board, cmd);    // (n, board, cmd) 전달을 통한 함수 호출, 시점 정보 반환 후 출력
    return 0;                           // 프로그램 종료

}