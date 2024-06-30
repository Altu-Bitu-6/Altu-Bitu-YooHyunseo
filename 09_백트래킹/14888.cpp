/**
 * https://www.acmicpc.net/problem/14888
*/
#include <iostream>         // 입출력스트림 헤더 포함
#include <vector>           // 수열 저장할 벡터 헤더 포함
#include <algorithm>        // 함수 사용을 위한 알고리즘 헤더 포함

using namespace std;

const int INF = 1e9;                            //  식의 범위 정의
const int MAX_N = 11;                           // N의 최대 개수 정의
const int ADD = 0, SUB = 1, MUL = 2, DIV = 3;   // 각 연산자에 인덱스 할당
const int EXP_NUM = 4;                          // 연산자 개수 정의

int n;
int nums[MAX_N];                        // 입력한 수열 저장
int expression[EXP_NUM];                // 입력한 연산자 개수 저장
int max_val = -INF, min_val = INF;      // 식의 최소, 최대 값을 INF로 초기화

/**
 * 연산자를 하나씩, 총 (N-1)개 뽑는다.
 *
 * cnt: 뽑은 연산자의 개수
 * cur_val: 현재 연산 결과
*/
void backtrack(int cnt, int cur_val) {  // 연산자 뽑은 개수인 cnt와 현재 인덱스까지의 누적값 cur_val을 파라미터로 하는 backtrack 

    // (N-1)개의 연산자를 다 뽑은 경우 -> 재귀 호출 종료
    if (cnt == n - 1) {

        // 최댓값, 최솟값 갱신
        max_val = max(max_val, cur_val);    // 현재 값과 max_val 중 큰 값으로 갱신
        min_val = min(min_val, cur_val);    // 현재 값과 min_val 중 큰 값으로 갱신
        return;                             // 백트래킹 종료
    }

    
    for (int i = 0; i < EXP_NUM; i++) {     // i: 연산자 번호, + - * / 를 한 번씩 순회
        
        if (expression[i] == 0) {           // 해당 연산자가 0개면, 사용 불가
            continue;                       // 다음 연산자 확인
        }

        
        expression[i]--;                    // 연산자 사용

        
        switch(i) {                         // 해당 연산자 연산 후, 재귀 호출

            case ADD:                                           // i=0인 경우
                backtrack(cnt + 1, cur_val + nums[cnt + 1]);    // cnt 1 증가, 현재 연산값에 저장된 배열의 다음 수 더한 값으로 backtrack 재귀 호출
                break;                                          // 해당 case 종료

            case SUB:                                           // i=1인 경우
                backtrack(cnt + 1, cur_val - nums[cnt + 1]);    // cnt 1 증가, 현재 연산값에 저장된 배열의 다음 수 뺀 값으로 backtrack 재귀 호출
                break;                                          // 해당 case 종료

            case MUL:                                           // i=2인 경우
                backtrack(cnt + 1, cur_val * nums[cnt + 1]);    // cnt 1 증가, 현재 연산값에 저장된 배열의 다음 수 곱한 값으로 backtrack 재귀 호출
                break;                                          // 해당 case 종료

            case DIV:                                           // i=3인 경우
                backtrack(cnt + 1, cur_val / nums[cnt + 1]);    // cnt 1 증가, 현재 연산값에 저장된 배열의 다음 수 나눈 값으로 backtrack 재귀 호출
                break;                                          // 해당 case 종료
        }

        expression[i]++;                    // 위의 재귀 호출 완료 시, 연산자 반납
    }
}

int main() {
    // 입력
    cin >> n;                           // 피연산자의 개수
    for (int i = 0; i < n; i++) {       // nums의 0~n-1 인덱스에 
        cin >> nums[i];                 // 피연산자 입력
    }
    for (int i = 0; i < EXP_NUM; i++) { // +(i=0), -(i=1), *(i=2), /(i=3)에 대해
        cin >> expression[i];           // 각 연산자의 개수 입력
    }

    // 백트래킹 연산
    backtrack(0, nums[0]);

    // 식의 최솟값과 최댓값을 줄 나눠 출력
    cout << max_val << '\n' << min_val;

    return 0;// 프로그램 종료
}