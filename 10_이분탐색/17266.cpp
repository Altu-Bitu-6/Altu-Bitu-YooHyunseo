#include <iostream>
#include <vector>

using namespace std;

bool isStreetBright(int height, int distance, int lamp_num, const vector<int> &pos) {
    vector<int> street(distance + 1, 0);
    

    for (int i = 0; i < lamp_num; i++) {
        int start = max(0, pos[i] - height);
        int end = min(distance, pos[i] + height - 1);
        
        street[start]++;
        if (end + 1 <= distance){
            street[end + 1]--;
        }
    }
    
    
    int count = 0;
    
    for (int i = 0; i <= distance; i++) {
        count += street[i];
        if (count == 0) {
            return false;
        }
    }
    return true;
}

int binarySearch(int distance, int lamp_num, const vector<int> &pos) {
    int left = 1;
    int right = distance;

    while (left <= right) {
        
        int mid = (left + right) / 2;
        
        if (isStreetBright(mid, distance, lamp_num, pos)==true) {
            right = mid - 1;
        } 
        else {
            left = mid + 1;
        }
    }
    return right+1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<int> pos(m);
    for (int i = 0; i < m; ++i) {
        cin >> pos[i];
    }

    cout << binarySearch(n, m, pos);

    return 0;
}

