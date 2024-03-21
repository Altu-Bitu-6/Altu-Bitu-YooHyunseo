#include <iostream>
#include <vector>

using namespace std;

void updatePan(vector<char>& pan, int& index, int n, int s, char ch) {
    
    index += s;                         // s만큼 화살표(index: 반시계방향으로 갈수록 증가)를 이동
    
    if(index >= n) {                    //index가 n을 넘어가지 않도록 조정
        index %= n;
    }
    
    if(pan[index] != '?' && pan[index] != ch) { // 화살표가 가리키던 칸에 들어있는 문자가 ? 또는 ch와 같지 않다면
        cout << "!";                    // 프로그램 종료 
        exit(0);
    }
    
    for(int j = 0; j < n; j++) {        
        if(pan[j] == ch) {              // pan에 ch와 같은 문자가 이미 존재하고 
            if(j != index) {            // 그 문자가 화살표가 가리키고 있지 않은 칸에 존재한다면
            
                cout << "!";            // 프로그램 종료 
                exit(0);
            }
        }
    }
    
    pan[index] = ch;                    // 화살표가 가리키는 자리에 입력받은 ch 저장 
}

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<char> pan(n, '?');
    int index = 0;
    
    for(int i = 0; i < k; i++) {            // 각각 s와 ch를 k회 입력 
        int s;
        char ch;
        cin >> s >> ch;
        
        updatePan(pan, index, n, s, ch);    // 매번 입력받은 s와 ch로 만들어진 판을 갱신  
    }
    
    for(int i = 0; i < n; i++) {            // 시계방향으로 출력 
        cout << pan[index];
        index--;
        if(index < 0) index = n - 1;        // index가 음수가 되지 않도록 조정 
    }
    
    return 0;
}
