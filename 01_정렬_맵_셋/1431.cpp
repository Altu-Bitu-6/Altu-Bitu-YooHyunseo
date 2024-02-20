#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

bool compare(const string& n1, const string& n2){
 
    if(n1.length() != n2.length()){ // A와 B의 길이가 다르면 짧은 것이 먼저 온다.
        return n1.length() < n2.length();
    }
    
    else{ // 서로 길이가 같은 경우
    
        int n1_sum=0, n2_sum=0;
        
        for(int i=0; i<n1.length(); i++){
            if( isdigit(n1[i]) ) {
                n1_sum += n1[i]-'0';
            }
        }
        
        for(int i=0; i<n2.length(); i++){
            if( isdigit(n2[i]) ) {
                n2_sum += n2[i]-'0';
            }
        }
        
        if(n1_sum != n2_sum) return n1_sum < n2_sum; // A의 모든 자리수의 합과 B의 모든 자리수의 합을 비교해서 작은 합을 가지는 것이 먼저 온다. (숫자인 것만 더한다)
        
        else return n1 < n2; // 만약 1,2번 둘 조건으로도 비교할 수 없으면 사전순으로 비교
    }
    
    
}

int main()
{
	int n;
	vector<string> serial_num;
	
	cin >> n;
	serial_num.assign(n, {});
	
	for (int i = 0; i < n; i++) { // 각 시리얼 넘버 입력
		cin >> serial_num[i];
	}
	
	// 연산
	sort(serial_num.begin(), serial_num.end(), compare);
	
	// 출력
	for (int i = 0; i < serial_num.size(); i++) {
		cout << serial_num[i] << '\n';
	}
	
	return 0;
}