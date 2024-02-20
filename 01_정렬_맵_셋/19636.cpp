#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    
    int initial_weight, initial_bmr, threshold, diet_days, diet_energy_intake, diet_amr;


    // 입력 받기
    cin >> initial_weight >> initial_bmr >> threshold;
    cin >> diet_days >> diet_energy_intake >> diet_amr;
    
    
    
    
    // (1) 일일 기초대사량 변화를 고려하지 않는 다이어트의 경우
    
    // 초기화 
    int current_weight = initial_weight;
    int basal_metabolic_rate = initial_bmr;
    int dead_or_not = 1; // 초기값을 1로 설정하여 생사 여부를 나타냄, 1: 생존, 0:사망
    int initial_energy_intake = initial_bmr;
    
    // 다이어트 시뮬레이션
    for (int day = 0; day < diet_days; day++)
    {
        int weight_change = diet_energy_intake - (basal_metabolic_rate + diet_amr); // 체중 증가량 = (일일 에너지 섭취량 - 일일 에너지 소비량) 
        current_weight += weight_change; // 체중 변화

        // 체중이나 일일 기초 대사량이 0 이하일 경우 데시 사망
        if (current_weight <= 0 || basal_metabolic_rate <= 0)
        {
            cout << "Danger Diet" << "\n"; 
            dead_or_not = 0; 
            break; 
        }
    }
    
    // 데시가 생존한 경우 다이어트 후 예상 체중과 일일 기초 대사량 출력
    if(dead_or_not != 0) cout << current_weight << " " << basal_metabolic_rate << "\n";
    
    
    
    
    // (2) 일일 기초대사량 변화를 고려하는 다이어트의 경우
    
    // 초기화 
    current_weight = initial_weight;
    basal_metabolic_rate = initial_bmr;
    dead_or_not = 1; 
    
    // 다이어트 시뮬레이션 
    for (int day = 0; day < diet_days; day++)
    {
        int weight_change = diet_energy_intake - (basal_metabolic_rate + diet_amr); // 체중 증가량 = (일일 에너지 섭취량 - 일일 에너지 소비량) 
        current_weight += weight_change; // 체중 변화
        
        // 체중 증가량의 절댓값이 임계치를 넘으면 BMR 변화
        if (abs(weight_change) > threshold)
                basal_metabolic_rate += floor(weight_change / 2.0); 

        // 체중이나 일일 기초 대사량이 0 이하일 경우 데시 사망
        if (current_weight <= 0 || basal_metabolic_rate <= 0)
        {
            cout << "Danger Diet" << "\n"; 
            dead_or_not = 0; 
            break; 
        }
    }
    
     // 데시가 생존한 경우 다이어트 후 예상 체중과 일일 기초 대사량 출력
    if(dead_or_not != 0) {
        cout << current_weight << " " << basal_metabolic_rate << " ";
        
        // 원래 생활로 돌아간다면 요요가 발생하는지 여부 출력 
        if(basal_metabolic_rate < initial_energy_intake) cout << "YOYO";
        else cout << "NO";
    }

    return 0;
}