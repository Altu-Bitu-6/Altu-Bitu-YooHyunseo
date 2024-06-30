#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;
const int NUM_CHARS = 26;

void countFreq(string word, vector<int> &freq) {    // freq 벡터의 0~25번 인덱스에 알파벳의 빈도수 저장하는 함수
    
    for (int i = 0; i < word.length(); i++) {
        
        freq[word[i] - 'A']++; 
    }

}

string getString(vector<int>& freq) {               // freq을 입력받아 원래 string을 반환하는 함수
    string result;
    for (int i = 0; i < freq.size(); ++i) {
        
        if(freq[i]>=2){
            char ch = 'A' + i;                      // 해당 인덱스에 대응하는 알파벳
            result += string(freq[i]/2, ch);  
        }
    }
    return result;
}

bool checkPalindrome(vector<int> freq){             // freq을 보고 Palindrome 가능한지 판단하는 함수 
    
    bool flag = false;
    
    for(auto num:freq){                             // freq에 짝수 홀수 여부를 저장
        num = num%2;
        
        if(num==1){                                 // num이 홀수라면
            
            if(flag==true){                         // 이미 홀수인 수가 있었다면
                return false;                       // palindrome 불가능
            }
            
            flag=true;                              // 첫번째 홀수라면 flag을 전환 
        }
        
    }
    return true;                                    // 반복문을 무사히 빠져나온다면 palindrome 가능 
}

int findOddFreqIndex(vector<int> freq){             // checkPalindrome을 통과한 freq에 대하여 홀수 번 등장하는 알파벳의 인덱스를 반환 
    
    //freq는 팰린드롬 가능한 문자열의 알파벳 빈도 수를 저장한 vector임을 가정
    
    for (int i = 0; i < freq.size(); ++i) {
        
        freq[i] = freq[i]%2;
        
        if (freq[i] == 1) {                         // freq[i]에 홀수가 저장되어있다면
            return i;                               // 인덱스를 리턴 
        }
    }
    
    return -1;                                      // 모든 알파벳이 짝수 번 등장할 경우 -1을 리턴 
}

string reverseString(string& input) {               // 입력된 문자열을 끝에서부터 시작해서 거꾸로 저장

    string reversed;        

    for (int i = input.length() - 1; i >= 0; --i) { // input을 역으로 순회하며
        reversed.push_back(input[i]);               // 현재 인덱스의 문자를 reversed에 push_back
    }
    return reversed;                                // reversed 반환
}

string makePalindrome(vector<int> freq){            // freq을 이용하여 palindrome인 string을 만드는 함수 
    
    int index = findOddFreqIndex(freq);             // 홀수 번 등장하는 알파벳의 인덱스를 저장
    string word = getString(freq);                  // palindrome이 가능한 문자열 중 사전순으로 가장 빠른 것을 word에 저장
    string reverse = reverseString(word);           // word를 뒤집은 문자열을 reverse에 저장 
    
    if(index != -1){                                // 홀수 개인 알파벳이 존재하는 경우 
        char odd_char = (char)(index+'A');          // index에 해당하는 알파벳 odd_char에 저장
        word.push_back(odd_char);                   // odd_char을 word에 이어붙임
    }
    
    return word+reverse;                            // word와 reverse를 이어붙임 
}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    string name;                                    // name 입력
    cin >> name;
    
    vector<int> name_freq(NUM_CHARS, 0);            // name의 freq을 저장하는 벡터 선언 
    countFreq(name, name_freq);
    
    if(!checkPalindrome(name_freq)){                // palindrome 못 만들 경우
        cout << "I'm Sorry Hansoo"<<'\n';           // 메시지 출력 
        return 0;
    }
    
    cout << makePalindrome(name_freq) << '\n';      // palindrome 출력
    
}