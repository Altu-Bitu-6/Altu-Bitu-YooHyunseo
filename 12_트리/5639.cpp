#include <iostream>
#include <queue>

using namespace std;

const int MIN = 0;
const int MAX = 1000000;

typedef struct Node {
    int data;
    struct Node *left, *right;
    Node(int data) : data(data), left(nullptr), right(nullptr) {}
} Node;


void preOrderMakeTree(queue<int>& input, Node*& current, int min, int max) {
    
    if (input.empty()) {    // 입력받은 값을 트리에 모두 삽입함 
        return;
    }
    
    int val = input.front();
    
    if(val < min || val > max){ // val이 current를 루트로 하는 서브트리에 삽입될 수 없음 -> 반환되어 상위트리로 
        return;
    }
    
    current = new Node(val);    // 현재 위치를 가리키는 포인터에 노드 삽입 
    input.pop();                // 새로운 input.first는 current의 자식 노드로 삽입될 값에 해당 
    
    preOrderMakeTree(input, current->left, min, val);   // current->left를 루트로 하는 서브트리의 최댓값을 val로 설정
    preOrderMakeTree(input, current->right, val, max);  // current->right를 루트로 하는 서브트리의 최솟값을 val로 설정
    
}

void printPostOrder(Node* current){ // 후위순회로 출력
    
    if(current == nullptr){     
        return;
    }
    
    printPostOrder(current->left);
    printPostOrder(current->right);
    cout << current->data << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
    queue<int> num;
    int input;
    
    
    while(cin >> input){
        if (cin.fail()){
            break;
        }
        num.push(input);
    }
    
    Node* root = nullptr;   
    preOrderMakeTree(num, root, MIN, MAX);  // num의 가장 첫 원소를 루트로 가지는 트리 생성 
    
    printPostOrder(root);
    
    return 0;
}