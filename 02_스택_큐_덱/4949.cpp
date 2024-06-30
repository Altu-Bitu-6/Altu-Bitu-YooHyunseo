// 입출력 라이브러리 가져오기
#include <iostream>
// 입력으로 주어지는 문장들으르 관리하기 위한 string 라이브러리 가져오기
#include <string>
// 괄호의 균형 여부를 관리하기 위한 stack 라이브러리 가져오기
#include <stack>

// std 클래스에 정의된 함수들을 간편하게 사용하기 위해 선언
using namespace std;

// string 내에서 괄호가 균형을 이루었는지 여부 반환하는 함수  
bool isBalanced(string input) { 
    stack<char> s;                                  //괄호 저장하는 스택 생성

    for (int i = 0; i < input.length(); i++) {      // <string>의 length()함수를 이용하여 문장의 길이만큼 반복하는 for문 생성
        char ch = input[i];                         // 문장에서 한 글자씩 추출하여 캐릭터형 ch 변수에 저장

        switch (ch) {                               // ch의 종류에 따라 분기하는 switch-case문, 
                                                    // 매 반복마다 ch의 종류 판별 후 처리

            case '(': case '[':                     // ch가 여는 괄호, '(' or '[' 일 때
                s.push(ch);                         // 스택 s에 바로 push
                break;                              // case 종료

            case ')':                               // ch가 닫는 소괄호 ')' 일 때
                if (s.empty() || s.top() != '(') {  // 스택 s가 비어있거나, 스택에 가장 최근에 넣은 원소가 여는 소괄호 '('가 아니라면 
                    return false;                   // 함수의 boolean 값으로 false 반환 후 함수 종료
                }
                s.pop();                            // 나머지 경우: 스택에 가장 최근에 넣은 원소가 여는 소괄호 '('일 경우,  해당 원소 pop
                break;                              // case 종료

            case ']':                               // ch가 닫는 대괄호 ']' 일 때
                if (s.empty() || s.top() != '[') {  // 스택 s가 비어있거나, 스택에 가장 최근에 넣은 원소가 여는 대괄호 '['가 아니라면 
                    return false;                   // 함수의 boolean 값으로 false 반환 후 함수 종료
                }
                s.pop();                            // 나머지 경우: 스택에 가장 최근에 넣은 원소가 여는 대괄호 '['일 경우,  해당 원소 pop
                break;                              // case 종료
        }
    }

    return s.empty();                               // for문으로 문장의 모든 문자를 검사한 뒤 stack s가 비어있다면 true 반환
                                                    // stack에 pop되지 못한 원소가 남아있을 경우 false 반환
}

/*
 * [괄호 균형 확인하기]
 * 1. 여는 괄호는 바로 스택에 넣는다.
 * 2. 닫는 괄호가 나오면 가장 최근에 넣었던 여는 괄호와 비교한다.
 * 2-1. 닫는 괄호와 여는 괄호의 종류가 같다면 해당 닫는 괄호가 균형을 이룬다.
 * 2-2. 직전에 나온 여는 괄호가 없거나 그 종류가 다르다면 해당 닫는 괄호가 균형을 이루지 못한다.
 * 3. 모든 닫는 괄호가 여는 괄호와 짝을 이루었더라도 스택에 여는 괄호가 남아있다면 균형을 이루지 못한다.
*/

// 프로그램을 실행하는 main 함수
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    string input;

    while (true) {                  // 조건 이하 무한반복
        //입력
        getline(cin, input);        // 공백도 함께 input에 입력받는 <string>의 getline() 함수 이용

        if (input == ".") {         // 마침표가 등장하여 문장이 끝난다면
            break;                  // while문 종료
        }

        //연산 & 출력
        if (isBalanced(input)) {    // input이 균형잡힌 문장이라면 isBalanced(input)에 true, 아니라면 false 반환
            cout << "yes\n";        // true일 경우 해당 줄에 "yes" 출력
        }
        else {                      // false일 경우
            cout << "no\n";         // 해당 줄에 "no" 출력
        }
    }

    return 0;                       // 프로그램 종료
}