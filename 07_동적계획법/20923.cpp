/*******  틀렸지만 우선 커밋해두고 목요일까지 추가제출 하겠습니다    *********/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

short check(short card1, short card2){    
    
    /*
    아무도 종을 안 쳤을 시 0, 
    도도가 종을 쳤을 시 1, 
    수연이가 종을 쳤을시 2를 반환하는 함수 
    */
    
    if(card1==5 || card2==5){
        return 1;
    }
    
    else if( ((card1+card2)==5) && (card1!=0) && (card2!=0) ){
        return 2;
    }
    
    return 0;
}    

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m;
    
    cin >> n >> m;                          // n에는 카드의 개수(~3만), m에는 게임 진행 횟수(~250만)

    vector<short> do_deck(n);               // 각자가 가진 덱(원소 n개)을 저장하는 벡터 생성
    vector<short> su_deck(n);               // stack처럼 FIFO

    for(int i=0; i<n; i++){                 // 작은 인덱스부터 아래에 위치한 카드가 입력
        cin >> do_deck[i] >> su_deck[i];
    }

    vector<short> do_ground;                // 각자가 그라운드에 쌓아놓은 카드를 저장하는 벡터 생성
    vector<short> su_ground;                // 보여지는 카드는 따로 변수에 저장된 back() 원소 뿐이고(ground 벡터의 개별 원소에는 접근 불가), 덱에 다시 쌓을 경우 뒤집는 과정을 거쳐야한다. 


    short do_card = 0, su_card=0;           // 두 그라운드가 비어있는 경우로 초기 설정 
    
    
    for(int i=1; i<=m; i++){                 // m번 게임 진행
        
        /*
        <게임 1회 진행 과정>
        1. 도도-수연 순서로 덱의 카드를 그라운드에 내려놓는다
        2. 그라운드에 있는 숫자를 확인하고 종을 치는 사람이 있는지 확인한다
            2-1. 수연이가 종을 치는 조건: 두 그라운드의 카드 합이 5일 때(단 두 그라운드가 모두 차있어야함)
            2-2. 도도가 종을 치는 조건: 숫자가 5인 카드가 등장할 때 
        3. 종을 쳤다면 원래 덱+ 상대의 그라운드 더미+ 자신의 그라운드 더미(가장 아래) 순으로 쌓는다 
        */
        
        if(i%2!=0){
            do_card = do_deck.back();   // 도도가 덱에서 꺼낸 카드를 그라운드에 펼침 
            do_deck.pop_back();
            do_ground.push_back(do_card);
        }
        
        else{
            su_card = su_deck.back();   // 수연이가 덱에서 꺼낸 카드를 그라운드에 펼침  
            su_deck.pop_back();
            su_ground.push_back(su_card);
        }
        
        short result = check(do_card, su_card);
        
        if(result != 0){   //누군가 종을 쳤다면 
            
            reverse(do_ground.begin(), do_ground.end());         // 덱에 넣기 위해 그라운드의 카드 뒤집기 
            reverse(su_ground.begin(), su_ground.end());
            
            if(result==1){ // 도도가 종을 쳤을 경우 
                do_ground.insert(do_ground.end(), su_ground.begin(), su_ground.end());
                do_ground.insert(do_ground.end(), do_deck.begin(), do_deck.end());
            }
            else if(result==2){    // 수연이가 종을 쳤을 경우 
                su_ground.insert(su_ground.end(), do_ground.begin(), do_ground.end());
                su_ground.insert(su_ground.end(), su_deck.begin(), su_deck.end());
            }
            
            do_ground.clear();
            su_ground.clear();
        }
    }
    
    /*
    for (int i = 0; i <= do_deck.size(); ++i) {
        cout << do_deck[i] << ' ';
    }
    cout << '\n';
    
    for (int i = 0; i <= su_deck.size(); ++i) {
        cout << su_deck[i] << ' ';
    }
    */
    
    
    // m회 진행 후 승리 판별
    
    if(do_deck.size()<su_deck.size()){
        cout << "su\n";
    }
    else if(do_deck.size()>su_deck.size()){
        cout << "do\n";
    }
    else if(do_deck.size()==su_deck.size()){
        cout << "dosu\n";
    }

}
