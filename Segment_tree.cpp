#include <iostream>
#include <vector>
#include <bits/stdc++.h>

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

// Main function
int main() {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11};
    int n = arr.size();

    // Calculate the size of the segment tree array
    int segmentTreeSize = 2 * pow(2, ceil(log2(n))) - 1;
    std::vector<int> segmentTree(segmentTreeSize);

    // Build the segment tree
    buildSegmentTree(arr, segmentTree, 0, n - 1, 0);

    // Perform range sum queries
    int qlow = 1;
    int qhigh = 4;
    int sum = rangeSumQuery(segmentTree, qlow, qhigh, 0, n - 1, 0);
    std::cout << "Sum of elements in the range [" << qlow << ", " << qhigh << "]: " << sum << std::endl;

    // Update an element in the array
    int idx = 2;
    int value = 6;
    arr[idx] = value;
    updateSegmentTree(segmentTree, idx, value, 0, n - 1, 0);

    // Perform range sum query after update
    sum = rangeSumQuery(segmentTree, qlow, qhigh, 0, n - 1, 0);
    std::cout << "Sum of elements in the range [" << qlow << ", " << qhigh << "] after update: " << sum << std::endl;

    return 0;
}
