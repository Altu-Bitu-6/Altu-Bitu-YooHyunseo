#include <iostream>
#include <string>

using namespace std;

void move(int row, int col, int &king_row, int &king_col, int &dol_row, int &dol_col){
    
    // row, col: king이 한 번에 가로, 세로로 움직이는 칸 수 (-1 ~ 1) 
    
    if( (row+king_row)<=0 || (row+king_row)>8       // king이 나갈 경우
        || (col+king_col)<=0 || (col+king_col)>8){
            return;
    }
    
    if( (dol_row==king_row+row) && (dol_col==king_col+col)){    // king과 doll이 같은 위치일 때 
        
        if( (row+dol_row)<=0 || (row+dol_row)>8                 // dol이 나갈 경우 
        || (col+dol_col)<=0 || (col+dol_col)>8){
            return;
        }
        
        dol_row+=row; dol_col+=col;                             // dol이 안 나갈 경우 위치 업데이트
        
    }
    
    king_row+=row; king_col+=col;                   // king이 안 나갈 경우 king 위치 업데이트
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string king_pos, dol_pos;
    int n;
    
    cin >> king_pos >> dol_pos >> n;
    
    int king_row = king_pos.substr(0,1)[0]-'A'+1;               // A~H를 int형 1~8로 변환 
    
    int king_col = stoi(king_pos.substr(1,1));                  // string형 숫자를 int로 변환 
    
    int dol_row = dol_pos.substr(0,1)[0]-'A'+1;
    
    int dol_col = stoi(dol_pos.substr(1,1));
    
    
    while(n--){         // n번의 instruction에서 각 경우 king이 가로, 세로로 얼마만큼 움직일지 입력 
        
        string ins;
        cin >> ins;
        
        if(ins == "R"){
            move(1, 0, king_row, king_col, dol_row, dol_col);
        }
        else if(ins == "L"){
            move(-1, 0, king_row, king_col, dol_row, dol_col);
        }
        else if(ins == "B"){
            move(0, -1, king_row, king_col, dol_row, dol_col);
        }
        else if(ins == "T"){
            move(0, 1, king_row, king_col, dol_row, dol_col);
        }
        else if(ins == "RT"){
            move(1, 1, king_row, king_col, dol_row, dol_col);
        }
        else if(ins == "LT"){
            move(-1, 1, king_row, king_col, dol_row, dol_col);
        }
        else if(ins == "RB"){
            move(1, -1, king_row, king_col, dol_row, dol_col);
        }
        else if(ins == "LB"){
            move(-1, -1, king_row, king_col, dol_row, dol_col);
        }
        
    }
    // 올바른 형식으로 출력 
    cout << (char)(king_row+'A'-1) << king_col << '\n' << (char)(dol_row+'A'-1) << dol_col ; 
    
    
}