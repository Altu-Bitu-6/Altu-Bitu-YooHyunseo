#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> convertStringToInt(string input){ // 자료형을 string에서 int형의 vector로 바꾸는 함수
    
    vector<int> digits;

    for (char digitChar : input) {
        int digit = digitChar - '0';
        digits.push_back(digit);
    }
    
    return digits;
}

vector<int> convertIndexReverse(vector<int> &arr){ // 0번 인덱스에 가장 작은 자릿수가 오도록 배열을 뒤집는 함수
    
    int length = arr.size();
    vector<int> temp(length);
    
    for(int i=0; i<length; i++){
        temp[i] = arr[length-i];
    }
    
    return temp;
    
}

void addByDigit(vector<int> &num1, vector<int> &num2){ // 각 자리의 숫자를 더하고 다음 자리의 올림 여부를 결정하여 배열에 한 자리씩 저장된 큰 수를 더하는 함수
    
    int len1 = num1.size();
    int len2 = num2.size();
    
    int length = ((len1 > len2) ? len1 : len2) + 1; // result의 길이는 (더해지는 수 중 큰 것) +1 : 올림 발생 대비
    
    vector<int> result(length, 0);
	int carry = 0;

	for (int i = 0; i < length-1; i++) {
		int digit1 = (i < len1) ? (num1[len1 - 1 - i]) : 0; // [len - 1 - i]번 인덱스에서 digit 추출, len보다 큰 상위자릿수에서는 0 저장
		int digit2 = (i < len2) ? (num2[len2 - 1 - i]) : 0;

		int sum = digit1 + digit2 + carry;          // 해당 자리의 합
		carry = sum / 10;                           // sum이 10 이상이면 carry에 1이 저장됨, 다음 자리 sum을 구할 때 사용됨
		result[length - 1 - i] = (sum % 10);        // 일의 자리를 저장
	}

	if (carry > 0) {
		result[0] = carry;                          // carry 발생할 경우 첫째 자리로 올림
	} 
			
	else {
		result.erase(result.begin());               // 아니라면 원소 삭제
	}
    
    for (int digit : result) {                      // 더한 결과 출력
        cout << digit;
    }
    
}

void add2BigInt(string input1, string input2){      //각각의 함수를 사용하여 string을 int배열로 바꾼 후 addByDigit에서 합 연산 및 출력
    
    vector<int> digits1 = convertStringToInt(input1);
    vector<int> digits2 = convertStringToInt(input2);
    
    addByDigit(digits1, digits2);
    
}


int main() {
    string input1, input2;
    cin >> input1 >> input2;                        // 두 수 공백으로 구분하여 입력
    
    add2BigInt(input1, input2);

    return 0;
}
