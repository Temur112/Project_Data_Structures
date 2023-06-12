#include <vector>
#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
#include <chrono>

using namespace std::chrono;
using namespace std;

// Function to build the segment tree
void buildSegmentTree(std::vector<int>& arr, std::vector<int>& segmentTree, int low, int high, int pos) {
    if (low == high) {
        segmentTree[pos] = arr[low];
        return;
    }

    int mid = (low + high) / 2;
    buildSegmentTree(arr, segmentTree, low, mid, 2 * pos + 1);
    buildSegmentTree(arr, segmentTree, mid + 1, high, 2 * pos + 2);
    segmentTree[pos] = segmentTree[2 * pos + 1] + segmentTree[2 * pos + 2];
}

// Function to perform a range sum query on the segment tree
int rangeSumQuery(std::vector<int>& segmentTree, int qlow, int qhigh, int low, int high, int pos) {
    // Total overlap
    if (qlow <= low && qhigh >= high) {
        return segmentTree[pos];
    }

    // No overlap
    if (qlow > high || qhigh < low) {
        return 0;
    }

    // Partial overlap
    int mid = (low + high) / 2;
    return rangeSumQuery(segmentTree, qlow, qhigh, low, mid, 2 * pos + 1) +
           rangeSumQuery(segmentTree, qlow, qhigh, mid + 1, high, 2 * pos + 2);
}

// Function to update a value in the segment tree
void updateSegmentTree(std::vector<int>& segmentTree, int idx, int value, int low, int high, int pos) {
    if (idx < low || idx > high) {
        return;
    }

    if (low == high) {
        segmentTree[pos] = value;
        return;
    }

    int mid = (low + high) / 2;
    updateSegmentTree(segmentTree, idx, value, low, mid, 2 * pos + 1);
    updateSegmentTree(segmentTree, idx, value, mid + 1, high, 2 * pos + 2);
    segmentTree[pos] = segmentTree[2 * pos + 1] + segmentTree[2 * pos + 2];
}

std::vector<int> nums(){
    std::vector<int> f;
    ifstream inputFile;
    inputFile.open("hltv_playerStats-complete.csv");

    string line = "";
    while(getline(inputFile, line)){
        string nickName;
        int kills;
        string temps;
        //nick,country,stats_link,teams,maps_played,rounds_played,kd_difference,kd_ratio,rating,total_kills,headshot_percentage,total_deaths,grenade_damage_per_round,kills_per_round,assists_per_round,deaths_per_round,teammate_saved_per_round,saved_by_teammate_per_round,kast,impact
        stringstream inputstring(line);
        getline(inputstring, nickName, ',');
        for(int i = 0; i < 7; i++){
      if(i == 2){
        getline(inputstring, temps, ']');
        getline(inputstring, temps, ',');
        }
        getline(inputstring, temps, ',');
        }
    
    getline(inputstring, temps, ',');
    
    kills = atoi(temps.c_str());
    if(kills != 0){
        f.push_back(kills);
    }
    
    
    }
    return f;
}


// Main function
int main() {
    
    std::vector<int> arr = nums();
    int n = arr.size();

    // Calculate the size of the segment tree array
    int segmentTreeSize = 2 * pow(2, ceil(log2(n))) - 1;
    std::vector<int> segmentTree(segmentTreeSize);

    // Build the segment tree
    buildSegmentTree(arr, segmentTree, 0, n - 1, 0);
    
    // Perform range sum queries
    int qlow = 0;
    int qhigh = 800;
    auto start = high_resolution_clock::now();
    int sum = rangeSumQuery(segmentTree, qlow, qhigh, 0, n - 1, 0);
    
    std::cout << "Sum of elements in the range [" << qlow << ", " << qhigh << "]: " << sum << std::endl;

    // Update an element in the array
    // int idx = 2;
    // int value = 6;
    // arr[idx] = value;
    
    updateSegmentTree(segmentTree, 2, 6, 0, n - 1, 0);
    auto stop = high_resolution_clock::now();

    // Perform range sum query after update
   
    sum = rangeSumQuery(segmentTree, 0, 450, 0, n - 1, 0);
    
    auto duration = duration_cast<microseconds>(stop - start);


    std::cout << "Sum of elements in the range [" << qlow << ", " << qhigh << "] after update: " << sum <<endl;

    cout<<"time taken for overlapping and updating for number of elements: "<<n<<" is "<<duration.count()<<endl;

    return 0;
}
