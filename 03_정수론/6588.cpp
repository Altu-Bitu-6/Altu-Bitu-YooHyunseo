#include <iostream>                             // 입출력 클래스 포함
#include <vector>                               // 벡터 클래스 포함 
#include <algorithm>                            // 알고리즘 클래스 포함 - max_element() 함수 

using namespace std;                            // std 클래스의 함수 사용을 명시


vector<bool> getPrimes(int n) {                 // 소수 여부 반환 함수: 에라토스테네스의 체 이용

    vector<bool> is_prime(n + 1, true);         // 0부터 n까지의 소수 여부를 저장하는 벡터 is_prime 생성, true로 초기화 
    is_prime[0] = is_prime[1] = false;          // 0과 1은 소수가 아니므로 미리 제거
    
    for (int i = 2; i * i <= n; i++) {          // 2 ~ 제곱근 n까지 검사 
    
        if (!is_prime[i]) {                     // i가 소수가 아니라면 
            continue;                           // 아래 코드 통과 
        }
        for (int j = i * i; j <= n; j += i) {   // i가 소수라면, i의 배수들이 j일때  
            is_prime[j] = false;                // j를 제거 
        }
    }
    return is_prime;                            // 소수 여부가 저장된 is_prime 반환 
}


int goldbach(int n, vector<bool> &is_prime) {   // n = a + b를 만족시키는 a 반환 
    
    for (int a = 3; a <= n / 2; a+= 2) {        // 3부터 n/2보다 작거나 같은 모든 홀수 탐색 
        
        /* 2보다 큰 짝수 소수는 존재하지 않으므로
         a = 3부터 탐색해도 a와 b 모두 홀수여야 한다는 조건 만족 */
        
        if (is_prime[a] && is_prime[n - a]) {   // 벡터 is_prime의 a번 원소와 n-a번 원소가 둘 다 소수임을 만족하는 인덱스 a가 존재한다면
            return a;                           // a를 반환
        }
    }
    
    return 0;                                   // 없으면 0 반환 
}


/* [백준 6588: 골드바흐의 추측]
 * 1. 3보다 크거나 같고 n / 2보다 작거나 같은 소수 a를 오름차순으로 탐색한다.
 * 2. 1에서 찾은 a에 대하여 n - a(=b)도 소수이면 골드바흐의 추측이 성립한다.
 * 3. 골드바흐의 추측이 성립하면 a를, 성립하지 않으면 0을 반환한다.
 */


int main() {
    // 입력
    vector<int> arr;                            // 입력받은 수 저장할 벡터 arr 선언  
    int input;                                  // 입력 시에 사용할 변수 input 선언 
    while(1) {                                  // 0이 입력되기 전까지 while문 반복 
        cin >> input;                           // input에 수 입력받음 
        
        if (input == 0) {                       // input에 0이 입력될 경우 
            break;                              // 입력 종료 
        }
        arr.push_back(input);                   // input에 입력받은 수들이 arr 벡터의 원소로 저장됨 
    }

    // 연산
    int max_num = *max_element(arr.begin(), arr.end());     // arr의 최대 원소를 max_element() 함수로 구하여 max_num에 저장 
    vector<bool> is_prime = getPrimes(max_num);             // max_num까지의 수들의 소수 여부를 getPrimes()로 구하여 벡터 is_prime에 저장 

    for (int i = 0; i < arr.size(); i++) {                  // arr의 원소들을 한 번씩 순회
        int a = goldbach(arr[i], is_prime);                 // arr[i] = a + b 를 만족시키는 가장 작은 홀수인 소수 a를 goldbach()를 통해 구하기 

        // 출력
        if (a != 0) {                                                       // n = a + b를 만족하는 a, b가 존재하면
            cout << arr[i] << " = " << a << " + " << arr[i] - a << "\n";    // n = a + b 형태로 출력 
            
        } else {                                                            // 존재하지 않으면
            cout << "Goldbach's conjecture is wrong.\n";                    // 골드바흐의 추측의 반례에 해당하므로 문장 출력 
        }
    }
    return 0;                                   // 시스템 종료 
}