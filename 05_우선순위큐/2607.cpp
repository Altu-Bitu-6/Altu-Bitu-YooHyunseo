// 2607: 비슷한 단어 (실버3/구현, 문자열)
#include <iostream>             // 입출력을 위한 클래스 포함
#include <vector>               // 벡터 자료형 사용하기 위해 클래스 포함

using namespace std;            // std에 정의된 함수를 편리하게 사용하기 위해 선언
const int NUM_CHARS = 26;       // 알파벳의 개수를 체크할 배열을 생성하기 위해 배열의 크기 정의

/*
* 원본 단어와의 차이의 개수를 센다.
*/

/*
 * [비슷한 단어]
 *
 * 단어가 같은 구성일 조건
 * 1. 두 개의 단어가 같은 종류의 문자로 이루어짐
 * 2. 같은 문자는 같은 개수만큼 있음
 *
 * 비슷한 단어의 조건
 * 1. 한 단어에서 한 문자를 더하거나, 빼면 같은 구성이 됨
 *    -> 두 단어에서 다른 문자의 개수가 총 1개
 * 2. 한 단어에서 한 문자를 바꾸면 같은 구성이 됨
 *    -> 두 단어에서 다른 문자의 개수가 총 2개
 *    -> !주의! 이때, 두 단어의 길이가 같아야 함 cf) doll | do
 */

// 각 알파벳의 개수 세기
void countFreq(string word, vector<int> &freq) {            // 현재 인덱스에 대응하는 알파벳이 word에 몇 번 나타나는지 freq 벡터를 갱신하는 함수
    for (int i = 0; i < word.length(); i++) {               // word를 이루는 char을 한 번씩 순회
        freq[word[i] - 'A']++;                              // A부터 Z까지의 알파벳이 등장한 횟수를 freq[0]부터 freq[25]까지 저장(발견할 때마다 1 증가)
    }
}

int countDiff(string word, vector<int> original_freq) {     // 첫 번째 단어(original)와 word의 알파벳이 차이나는 정도를 정수로 반환하는 함수
    vector<int> freq(NUM_CHARS, 0);                         // 전달된 word에서 각 알파벳이 등장하는 횟수를 저장할 freq 생성(크기 26 / 0으로 초기화)
    int diff = 0; // 원본 단어와의 차이                      // original_freq에 freq를 비교하여 차이를 count할 변수 diff 선언

    countFreq(word, freq); // 각 알파벳의 개수 세기          // word에서 각 알파벳의 개수를 세서 freq를 갱신
    
    // 원본 단어와 다른 알파벳 개수 구하기
    for (int i = 0; i < NUM_CHARS; i++) {                   // 알파벳 별로 한 번씩 비교하며 순회
        diff += abs(original_freq[i] - freq[i]);            // 각 인덱스에서 original_freq와 freq이 차이나는 정도를 diff에 더하기
    }
    return diff;                                            // diff를 반환
}

int main() {
    int N, ans=0;                                           // 단어의 개수 N, 처음 단어와 비슷한 단어가 몇 개인지 저장하여 출력할 ans 선언
    string original;                                        // 처음으로 입력받을 단어인 original 선언
    // 입력
    cin >> N;                                               // N 입력
    cin >> original;                                        // original 입력
    vector<int> original_freq(NUM_CHARS, 0);                // original에서 각 알파벳이 등장하는 횟수를 저장할 int형 벡터 original_freq 선언, 26개의 원소를 0으로 초기화하며 생성

    // 연산
    countFreq(original, original_freq);                     // original에서 각 알파벳이 등장하는 횟수를 original_freq에 저장

    for (int i = 1; i < N; i++) {                           // N-1개의 서로 다른 단어에 대한 각 case 반복
        string word;                                        // original과 다른 단어인 word 선언
        cin >> word;                                        // word 입력

        int diff = countDiff(word, original_freq);          // 정수형 변수 diff에 word와 original의 알파벳이 몇 개만큼 차이나는지 대입
        // 비슷한 단어 세기
        if (diff == 0 || diff == 1 || diff == 2 && original.length() == word.length()) {   

            /*
            차이나는 정도(diff)가 
            - 0이거나(word가 original과 같은 구성)
            - 1이거나(word에서 한 문자를 더하거나 뺐을 때 original과 같은 구성)
            - 2이면서 original과 word의 길이가 같을 때(word에서 한 문자를 바꿨을 때 original과 같은 구성)
            두 단어는 비슷한 단어가 된다. 
            */

            ans++;                                          // 비슷한 단어라면 ans 1 증가
        }
    }
    // 출력
    cout << ans;                                            // ans 값 출력
    return 0;                                               // 프로그램 종료 
}