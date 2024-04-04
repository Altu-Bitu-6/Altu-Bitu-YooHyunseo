#include <iostream>                 // 입출력스트림 포함 
#include <vector>                   // 그라운드와 덱의 카드 묶음들을 vector형에 저장
#include <deque>                    // 그라운드와 덱에 있는 카드들를 deque형에 저장

using namespace std;                // std 이름공간의 함수들을 간편하게 사용하기 위해 선언 

typedef vector<deque<int>> cards;   // cards 자료형 정의 - 카드(int)들을 담은 덱(deque)들을 담은 벡터
const int DO = 0, SU = 1;           // 인덱스로 활용할 상수 설정, 0: 도도, 1: 수연

/** 승리 판단하기 */
string judge(cards& deck) {                                     // 게임이 끝난 후 덱의 상태로 결과를 판단하여 출력할 string을 리턴하는 함수
	int do_deck = deck[DO].size(), su_deck = deck[SU].size();   // do_deck과 su_deckdp 각각 덱의 카드 개수를 저장 
	if (do_deck > su_deck) {                                    // 도도의 카드가 더 많다면
		return "do";                                            // do 를 리턴
	}
	else if (do_deck < su_deck) {                               // 수연이의 카드가 더 많다면
		return "su";                                            // su를 리턴
	}
	return "dosu";                                              // 둘의 카드 개수가 같은 경우 무승부로 dosu를 리턴 
}

/** 그라운드에서 덱으로 카드 옮기기 */
void groundToDeck(deque<int>& deck, deque<int>& ground) {   // 그라운드에 있는 카드를 덱으로 옮기는 함수
	while (!ground.empty()) {                               // 그라운드가 빌 때 까지
		deck.push_back(ground.back());                      // 그라운드의 가장 뒤 카드부터 덱에 넣기(뒤집어야 하므로)
		ground.pop_back();                                  // 넣은 카드를 그라운드에서 제거 
	}
}

/** 종을 쳤을 때 */
void ringTheBell(int player, cards& deck, cards& ground) {  // 종을 치는 경우 그라운드에 있는 카드들을 player의 덱으로 가져가도록 처리 
	groundToDeck(deck[player], ground[!player]);            // 카드 가져가기 (상대 그라운드 -> 본인 덱)
	groundToDeck(deck[player], ground[player]);             // 카드 가져가기 (본인 그라운드 -> 본인 덱)
}


/** 종을 울릴 수 있는 사람 판단 */
int whoCanRingTheBell(cards& deck, cards& ground) {             // 카드를 낸 직후 종을 울릴 수 있는지 확인 
	if (!ground[DO].empty() && ground[DO].front() == 5) {       // 도도
		return DO;      // 도도의 카드가 5인 경우 도도의 승리, 상수값 리턴
	}
	else if (!ground[SU].empty() && ground[SU].front() == 5) {  // 도도
		return DO;      // 수연이의 카드가 5인 경우 도도의 승리, 상수값 리턴
	}
	else if (!ground[DO].empty() && !ground[SU].empty() && (ground[DO].front() + ground[SU].front() == 5)) { // 수연
		return SU;      // 도도와 수연이 둘 다 그라운드에 카드가 존재하며 그 합이 5일 경우 수연의 승리, 상수값 리턴 
	}
	return -1;          // 종을 울릴 수 없음, -1 리턴
}

/** 게임 진행 */
string game(int m, cards& deck, cards& ground) {        // 게임을 진행하는 함수
	bool turn = DO;                                     // 도도 먼저
	while (m--) {                                       // m회 동안 반복
		ground[turn].push_front(deck[turn].front());    // 덱의 가장 윗장을 그라운드에 내려놓기(덱 -> 그라운드)
		deck[turn].pop_front();                         // 내려놓은 카드를 덱에서 pop
		if (deck[turn].empty()) {                       // 내려놓은 카드가 마지막 장이었다면 
			break;                                      // 게임 중지 
		}

		int bell = whoCanRingTheBell(deck, ground);     // 종을 울릴 수 있는 사람
		if (bell != -1) {                               // 종을 울린 경우
			ringTheBell(bell, deck, ground);            // 카드를 가져가기 
		}
		turn = !turn;                                   // 차례 바꾸기
	}
	return judge(deck);                                 // m회가 끝난 후 deck의 상태를 judge 
}

/**
 * 도도, 수연이 각각 덱과 그라운드를 가짐
 * 도도->수연->도도->수연... 순으로 차례를 바꿔가며 게임 진행 (game 함수)
 * 1. 카드를 덱에서 한 장 내려놓음
 * 2. 어떤 플레이어가 종을 칠 수 있는지 판단 (whoCanRingTheBell 함수)
 * 3. 종을 친 경우 그라운드의 카드를 덱으로 이동(ringTheBell, groundToDeck 함수)
 * 종료 조건 만족 시 승리한 사람 리턴(judge 함수)
 */

int main() {                        // 프로그램 시작
	int n, m, card1, card2;         // 변수 선언
	cards deck(2), ground(2);       // 0: 도도, 1: 수연 을 인덱스로 하여 cards 형의 deck과 ground 벡터를 생성

	// 입력
	cin >> n >> m;                  // 덱의 카드 개수 n과 카드를 내는 횟수 m 입력
	while (n--) {                   // n회 동안
		cin >> card1 >> card2;      // card1, card2 변수에 숫자 입력
		deck[DO].push_front(card1); // card1을 도도의 덱 맨 앞에 push
		deck[SU].push_front(card2); // card2를 수연이의 덱 가장 앞에 push
	}

	// 출력 & 연산
	cout << game(m, deck, ground);  // 게임 결과를 출력
	
	return 0;                       // 프로그램 종료 
}
