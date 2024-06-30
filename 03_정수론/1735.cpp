#include <iostream>
#include <algorithm>

using namespace std;

int gcdIter(int a, int b){      // 유클리드 호제법으로 a와 b의 최대공약수를 구하는 함수

    while(b){                   
        a%=b;                   
        swap(a, b);             
    }
    
    return a;                   
}

int main()
{
    int ja1, mo1, ja2, mo2;     // 첫번째, 두번째 수의 분자와 분모를 각각 선언하고 입력받음
    cin >> ja1 >> mo1;
    cin >> ja2 >> mo2;
    
    int ja3, mo3;               // 답을 출력할 세번째 수는 앞선 두 수를 통분하여 더한 것
    ja3 = ja1*mo2+ja2*mo1;      // 세번째 수의 분자 정의
    mo3 = mo1*mo2;              // 세번째 수의 분모 정의
    
    int gcd = gcdIter(ja3, mo3);    //새로 만들어진 분모와 분자가 약분될 가능성을 대비하여 최대공약수 찾기
    
    cout << ja3/gcd << ' ' << mo3/gcd;  // 분자와 분모를 최대공약수로 나눈 후 출력 
}

