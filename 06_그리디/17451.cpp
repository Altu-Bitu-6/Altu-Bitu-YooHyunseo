#include <iostream>
#include <vector>

using namespace std;

long long calMinSpeed(vector<int> speed){
    
    int here=0, next=0;      // 다음 행성과 현 행성을 비교 
    long long min_speed = speed.back();
    
    while(!speed.empty()){
        
        here = speed.back();
        long long k = (min_speed + here - 1) / here;
        
        min_speed = here*k;
        
        speed.pop_back();
        
    }
    
    return min_speed;
}

int main()
{
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> speed(n);
    
    for(int i=0; i<n; i++){
        cin >> speed[i];
    }
    
    cout << calMinSpeed(speed);
}